
macro printf_core_code fn_name {

    ; here r14 points on '%'

    ; r14 = format string position [garanted to be on '%']
    ; rsi = result buffer position
    ; rbx = position in register array. [base at rsp + REAL_BUFFER_SIZE + LOCAL_DATA_SIZE]
    ; r13 = position in float register array [base at rsp + REAL_BUFFER_SIZE]
    
    ; you mustn't change:
    ;     ymm0 [used as internal storage]
    ;     ymm1 [used as internal storage]
    ;     ymm8 = '    ...    ' [spaces]
    ;     ymm9 = '0000...0000' [ascii zeroes]
    ;     rsp [used as base for many accesses]
    ;     rbp = count of bytes written in 'xprintf' [updated automatically]
    ;     r15 [used in xprintf]

    ; if you are writing more than 4KB of text, use flush to be safe if it is 'xprintf'
    ; flush is like this:
    ;     cmp rsi, r15
    ;     jbe @f
    ;     flush_buffer
    ; @@:

    movzx eax, byte [r14 + 1] ; load next character
    cmp eax, '%'
    je .insert_percent

    ; ---- local data: ----

    ; r11 = begin rsi address
    mov r11, rsi
    ; rdi = flags
    ; r8 = width
    ; r9 = precision
    xor rdi, rdi
    xor r8, r8
    vmovdqa ymm15, ymm8 ; enable spaces for filling

F_LONG = 0x1
F_LONG_LONG = 0x2
F_SHORT = 0x4
F_SHORT_SHORT = 0x8
F_CAPITAL = 0x10
F_NEGATIVE = 0x20
F_SIGN = 0x40
F_SPACE = 0x80
F_PRECISION = 0x200
F_ALTERNATE = 0x400 ; '#'
F_ZERO = 0x800
F_SPLITTER = 0x1000

.flag_parse_loop:
    add r14, 1 ; move to first/next format character
    movzx eax, byte [r14] ; load it to eax
    sub eax, ' '
    cmp al, '9' - ' '
    ja .flag_default ; end loop
    lea rcx, [flag_jump_table]
    jmp qword [rcx + rax * 8]

.flag_space:
    or rdi, F_SPACE
    jmp .flag_parse_loop

.flag_precision:
    or rdi, F_PRECISION
    ; read precision
    add r14, 1
    movzx eax, byte [r14]
    cmp eax, '*'
    je .precision_load_from_variable
    xor r9, r9
.read_precision_loop:
    lea edx, [rax - '0']
    cmp edx, 9
    ja .flag_default ; end loop
    lea r9, [r9 + r9 * 4]
    lea r9, [r9 * 2 + rdx]
    add r14, 1
    movzx eax, byte [r14]
    jmp .read_precision_loop
    
.precision_load_from_variable:
    movsxd r9, dword [rbx]
    add rbx, 8 ; move next register
    add r14, 1
    movzx eax, byte [r14]
    if STRICT_GNU
    test r9, r9
    jns .flag_default ; end loop
    and rdi, not F_PRECISION
    end if
    jmp .flag_default ; end loop

.flag_zero_width:
    test r8, r8
    jnz .flag_width
    or rdi, F_ZERO
    vmovdqa ymm15, ymm9 ; enable zeros for filling
    jmp .flag_parse_loop
    
.flag_width:
    lea r8, [r8 + r8 * 4]
    lea r8, [rax + r8 * 2 - ('0' - ' ')]
    jmp .flag_parse_loop

.flag_prefix:
    or rdi, F_ALTERNATE
    jmp .flag_parse_loop

.flag_plus:
    or rdi, F_SIGN
    jmp .flag_parse_loop

.flag_minus:
    or rdi, F_NEGATIVE
    jmp .flag_parse_loop

.flag_splitter:
    or rdi, F_SPLITTER
    jmp .flag_parse_loop

.flag_wildcard:
    ; load next integer register as width
    movsxd r8, dword [rbx]
    add rbx, 8 ; move next register
    jmp .flag_parse_loop


if STRICT_GNU
.update_negative_spec:
    vmovdqa ymm15, ymm8 ; disable zeros for filling
    and rdi, not F_ZERO ; remove zero flag
    neg r8 ; disable width
    jmp .continue_after_update_negative_spec
end if

    ; now, all flags are parsed
.flag_default:

    if STRICT_GNU
        test rdi, F_NEGATIVE
        jnz .update_negative_spec
    .continue_after_update_negative_spec:
    else
        mov rdx, r8
        neg rdx
        test rdi, F_NEGATIVE
        cmovnz r8, rdx
    end if

    ; now
    movzx eax, byte [r14]
    
.update_flag_long_loop:
    cmp al, 'l'
    je .update_flag_long
.update_flag_short_loop:
    cmp al, 'h'
    je .update_flag_short
    
    ; eax is already loaded
    and eax, -33 ; normalize
    sub eax, 64 ; '@' = 0

    ; now, assume that al is less or equal to 95 - 64 = 31.
    lea rcx, [final_jump_table]
    jmp qword [rcx + rax * 8]

.update_flag_long:
    or rdi, F_LONG
    add r14, 1
    movzx eax, byte [r14]
    jmp .update_flag_long_loop

.update_flag_short:
    or rdi, F_SHORT
    add r14, 1
    movzx eax, byte [r14]
    jmp .update_flag_short_loop

    ; cases
.switch_default:
    jmp .main_loop


    ; ------------------------------------------------------ chars ---------------------------------------------------------------
.switch_char:
    if STRICT_GNU = 1
        vmovdqa ymm15, ymm8 ; can't fill with zeros
    end if
    ; pad with spaces
    cmp r8, 0
    jle .skip_width_padding
    lea rcx, [rsi + r8 - 1] ; calculate end position - if rsi >= rcx when all needed data is written
    call .padding_proc
.skip_width_padding:

    ; set character
    mov eax, [rbx] 
    mov [rsi], al
    add rsi, 1 ; update destination buffer
    add r14, 1 ; skip 'c'
    add rbx, 8 ; move registers array forward
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop


    ; ----------------------------------------------------- strings --------------------------------------------------------------
.switch_string:
    if STRICT_GNU = 1
        vmovdqa ymm15, ymm8 ; can't fill with zeros
    end if
    
    mov rdx, [rbx] ; read pointer to string from arguments
    add rbx, 8 ; shift args by one

    ; find number of elements to copy even if there is no zero:
    lea r9, [rdx + r9] ; end of string
    mov rax, 0x3FFFFFFFFFFFFFFF
    test rdi, F_PRECISION
    cmovz r9, rax ; set to int_max
    
    add r14, 1 ; skip 's' character
    
    cmp rdx, r9
    je .strlen_empty
    
    cmp byte [rdx], 0
    je .strlen_empty

    cmp r8, 0
    jle .string_left_or_none_padding

    ; ---------------- find min(precision, strlen(rdx)) -------
    mov rcx, rdx
    and rdx, -32 ; global offset
    and rcx, 31  ; local offset
    neg rcx      ; negative to use LUT
    vmovdqa ymm0, [rdx] ; load data
    lea rax, [fn_name#.blend_mask_table]
    vmovdqu ymm4, [rax + 32 + rcx] ; load blend mask
    vpcmpeqb ymm3, ymm0, ymm1 ; test on zero
    vpand ymm5, ymm4, ymm3 ; apply blend mask to result to remove false-positive behaviour
    vptest ymm5, ymm5 ; check if there is any '\0'
    jz .strlen_search_small_loop
    ; now, we had found symbol, get it's position.
    vpmovmskb eax, ymm5
    jmp .strlen_found
    ; serach for zero
.strlen_search_small_loop:
    add rdx, 32
    cmp rdx, r9 ; if we are at the end?
    jae .strlen_found_small_loop ; if finished
    vmovdqa ymm0, [rdx]
    vpcmpeqb ymm3, ymm0, ymm1
    vptest ymm3, ymm3
    jz .strlen_search_small_loop

.strlen_found_small_loop:
    ; found in loop
    vpmovmskb eax, ymm3
    ; now
    ; eax = mask of characters
    ; r14 = start position of block
.strlen_found:
    ; move exactly to character
    tzcnt eax, eax ; get position of char
    add rdx, rax
    ; take r9 = min(rdx, r9)
    cmp rdx, r9
    cmovb r9, rdx
    ; now, rdx = end of string
    sub r9, [rbx - 8] ; get length of string in rdx
    lea rcx, [rsi + r8] ; get position of segment's end for proc
    sub rcx, r9
    call .padding_proc
    ; now, padding is right, simply memcpy string
    
    mov rdx, [rbx - 8] ; read argument once more
    
    cmp r9, 64 ; if it is less than 64 it is unsafe to align rsi
    jb .memcpy_small_intro

    lea rcx, [rdx + r9] ; find end of segment
    vmovdqu ymm0, [rdx]
    vmovdqu [rsi], ymm0 ; store first block

    mov rax, rsi
    neg rax
    and rax, 31
    add rsi, rax
    add rdx, rax
    sub r9, rax

    ; first copy is safe, becouse r9 - rax >= 32
    xor rax, rax
    lea rcx, [r9 - 32] ; <= this address - it is ok to continue copying
.memcpy_loop:
    vmovdqu ymm0, [rdx + rax]
    vmovdqa [rsi + rax], ymm0
    add rax, 32
    cmp rax, rcx
    jbe .memcpy_loop
    
    add rsi, rax ; update offsets
    add rdx, rax
    
.memcpy_small:
    ; now, r9 < 32, so only 1 copy left
    lea rax, [rdx + 4096]
    and rax, -4096 ; now, rax = begin of next page
    sub rax, 32
    cmp rdx, rax
    jae .memcpy_small_slow ; if rdx is at the end of page, than use slow copy
    ; here, use safe fast copy
    vmovdqu ymm0, [rdx]
    vmovdqu [rsi], ymm0
    add rsi, r9 ; shift rsi
    jmp .main_loop ; return
.memcpy_small_slow:
    test r9, 16
    jz @f
    vmovdqu xmm0, [rdx]
    vmovdqu [rsi], xmm0
    add rdx, 16
    add rsi, 16
@@:
    test r9, 8
    jz @f
    mov rax, [rdx]
    mov [rsi], rax
    add rdx, 8
    add rsi, 8
@@:
    test r9, 4
    jz @f
    mov eax, [rdx]
    mov [rsi], eax
    add rdx, 4
    add rsi, 4
@@:
    test r9, 2
    jz @f
    movzx eax, word [rdx]
    mov [rsi], ax
    add rdx, 2
    add rsi, 2
@@:
    test r9, 1
    jz @f
    movzx eax, byte [rdx]
    mov [rsi], al
    inc rsi
@@:
    jmp .main_loop ; return
    
.memcpy_small_intro:
    cmp r9, 32
    jb .memcpy_small
    vmovdqu ymm0, [rdx]
    vmovdqu [rsi], ymm0
    jmp .memcpy_small



    ; ----------------------- case 2: search for zero and copy all string
    
.string_left_or_none_padding:
    
    if fn_name eq xprintf
        ; use loop from printf.
        ; it is faster, becouse we can safely write down from buffer
    
        mov rcx, rdx
        and rdx, -32 ; global offset
        and rcx, 31  ; local offset
        neg rcx      ; negative to use LUT
        vmovdqa ymm0, [rdx]
        lea rax, [xprintf.blend_mask_table] ; uzhas
        vmovdqu ymm4, [rax + 32 + rcx] ; load blend mask
        vpcmpeqb ymm3, ymm0, ymm1
        vpand ymm5, ymm4, ymm3 ; apply blend mask to result to remove false-positive behaviour

        ; update text at rsi
        vmovdqu ymm6, [rsi + rcx]        ; ! usage of red zone :) [may be negative offset]
        vpblendvb ymm6, ymm6, ymm0, ymm4 ; mix real data and new data
        vmovdqu [rsi + rcx], ymm6        ; store result 

        ; use add becouse rcx = - offset
        ; move rsi forward [becouse in '.found' it will be moved backward]
        lea rsi, [rsi + rcx + 32]

        vptest ymm5, ymm5 ; check if there is any '\0' or '%'
        jz .string_search_small_loop_into
        
        ; now, we had found symbol, get it's position.
        vpmovmskb eax, ymm5
        ; rcx - is shifted, it is ok
        jmp .string_found ; go to found
        
    else
        ; use loop from xsprintf
        ; it is slower, but don't write down from rsi
        mov rcx, rdx
        and rdx, -32 ; global offset
        and rcx, 31  ; local offset
        
        ; load source
        vmovdqa  ymm0, [rdx]

        ; swap hi|low parts
        vperm2i128 ymm3, ymm0, ymm0, 0x11

        ; load masks and shuffles
        ; 4 * 8 = 32 = sizeof(ymm0)
        shl rcx, 2
        lea rax, [xsprintf.shufA]
        vmovdqa ymm4, [rax + rcx * 8]
        vmovdqa ymm5, [rax + rcx * 8 + (xsprintf.shufB - xsprintf.shufA)]

        ; shuffle vectors
        vpshufb ymm0, ymm0, ymm4
        vpshufb ymm3, ymm3, ymm5
        ; join
        vpor ymm7, ymm0, ymm3

        ; test resulting vector on bad symbols
        vpcmpeqb ymm3, ymm7, ymm1
        
        ; store
        vmovdqu [rsi], ymm7

        vptest ymm3, ymm3
        jnz .string_found_in_beginning
        
        ; now, in rsi is located "32 - rcx" right bytes
        add rsi, 32
        shr rcx, 2 ; restore shift from table lookup
        sub rsi, rcx
    end if 

    ; serach for zero
.string_search_small_loop_into:

if UNROLL_STRING_SEARCH_SMALL_LOOP
    lea rax, [rdx + 128]
    cmp rax, r9
    ja .string_search_small_loop
    
    add rdx, 32
    
    ; iterate by 128 at once
    repeat 3
        vmovdqa ymm0, [rdx]
        vmovdqu [rsi], ymm0
        add rsi, 32
        vpcmpeqb ymm3, ymm0, ymm1
        vptest ymm3, ymm3
        jnz .string_found_small_loop
        add rdx, 32
    end repeat
    
    vmovdqa ymm0, [rdx]
    vmovdqu [rsi], ymm0
    add rsi, 32
    vpcmpeqb ymm3, ymm0, ymm1
    vptest ymm3, ymm3
    jz .string_search_small_loop_into
    jmp .string_found_small_loop

end if
    
.string_search_small_loop:
    add rdx, 32
    cmp rdx, r9
    jae .string_found_small_loop
    vmovdqa ymm0, [rdx]
    vmovdqu [rsi], ymm0   ; |- copy data to result buffer
    add rsi, 32           ; |
    vpcmpeqb ymm3, ymm0, ymm1
    vptest ymm3, ymm3
    jz .string_search_small_loop
.string_found_small_loop:
    ; found in loop
    vpmovmskb eax, ymm3
    ; now
    ; eax = mask of characters
    ; rdx = start position of block
.string_found:
    ; move exactly to character
    tzcnt eax, eax ; get position of char
    add rdx, rax
    lea rsi, [rsi + rax - 32] ; step back & move only on rax bytes
    sub r9, [rbx - 8] ; get length...
    add r9, r11 ; now, r9 = position from rsi
    cmp rsi, r9
    cmova rsi, r9
    ; full string content was copied
    cmp r8, 0
    je .main_loop ; return
    ; now, it is 100% negative
    jmp .check_end_padding ; return with padding


    ; ------------ one more subcase
    if fn_name eq xsprintf
    .string_found_in_beginning:
        shr rcx, 2 ; restore shift from table lookup
        add rdx, rcx ; skip this count of chars, becouse them aren't counted in rax
        add rsi, 32
        vpmovmskb eax, ymm3
        jmp  .string_found
    end if
    
    ; ----------------------- case 3: empty string: simply fill it with spaces
.strlen_empty:

    ; abs
    mov rax, r8
    cqo
    xor rax, rdx
    sub rax, rdx
    
    lea rcx, [rsi + rax] ; get width of spaces
    call .padding_proc ; set them
    jmp .main_loop ; return


    ; ----------------------------------------------------- floats --------------------------------------------------------------
.switch_float:
    mov eax, 6
    test rdi, F_PRECISION
    cmovz r9d, eax ; set to base precision
    
    add r14, 1 ; skip f/g/e command

    ; now, extract bytes from float:
    ; r13 = pointer on it in memory
    lea rax, [rsp + REAL_BUFFER_SIZE + LOCAL_VARIABLES_SIZE] ; get end of floats segment
    cmp r13, rax
    jge .float_load_from_rbx ; if all floats from xmm0-7 are read
    mov rdx, [r13] ; load double
    add r13, 8
.float_loaded:

    mov r12, rdx

    ; now, rdx = double
    mov rax, rdx
    shr rdx, 52
    and edx, 0x7FF ; exponent
    and rax, [float_mantiss_base]

    if STRICT_GNU & 0
        test rdx, rdx
        jz .float_zero_exponent
    else
        test rdx, rdx
        jz .float_zero_print
    end if

    or rax, [float_mantiss_bit] ; add 53 bit
    
    if STRICT_GNU
.float_zero_exponent_denormalized:
    end if

    ; now:
    ; rax = mantiss [int]
    ; rdx = exponent [int, biased : from 1 to 0x7FE]

    ; use tables to make integer from mantiss
    lea r10, [float_table_multiplers]
    ; use formula: answer = mantiss * multiple >> 64 * 10^power
    mov rcx, [r10 + 8 * rdx - 8] ; load multipler
    lea r10, [float_table_powers]
    movsx r10, word [r10 + 2 * rdx - 2]
    
    ; now, r10 = power
    ; rcx = multipler
    mul rcx ; apply multipler
    mov rax, rdx

    ; now,
    ; rax = base10 mantiss
    ; r10 = power

    cmp byte [r14 - 1], 'g'
    je .float_g_spec
    cmp byte [r14 - 1], 'e'
    je .float_e_spec
.float_g_spec_resulted_in_f:


    ; width: it is unknown?


    ; print it using slow loop for now

    push r13

    
    mov rcx, rsp

    sub rsp, 512 ; allocate buffer on stack
 

    mov r13, 10
.float_slow_loop:
    xor rdx, rdx
    div r13
    sub rcx, 1
    mov [rcx], dl
    add r10, 1
    cmp r10, 0
    jne .flt_skip_dot1
    sub rcx, 1
    mov byte [rcx], '.' xor '0'
.flt_skip_dot1:
    test rax, rax
    jnz .float_slow_loop


    cmp byte [rcx], '.' xor '0'
    jne .flt_skip_sub1
    sub rcx, 1
    mov byte [rcx], '0' xor '0'
.flt_skip_sub1:

    ; while power is negative, write zeroes
    cmp r10, 0
    jge .flt_skip_zpad
.flt_skip_dot2:
    sub rcx, 1
    mov byte [rcx], '0' xor '0'
    add r10, 1
    cmp r10, 0
    jl .flt_skip_dot2
    sub rcx, 1
    mov byte [rcx], '.' xor '0'
.flt_skip_zpad:


    cmp byte [rcx], '.' xor '0'
    jne .flt_skip_sub12
    sub rcx, 1
    mov byte [rcx], '0' xor '0'
.flt_skip_sub12:

    ; copy it to rsi
    lea rdx, [rsp + 512]
.float_copy_slow:
    mov al, [rcx]
    xor al, '0'
    mov [rsi], al
    sub r10, 1
    add rsi, 1
    add rcx, 1
    cmp rcx, rdx
    jb .float_copy_slow

    mov rsp, rdx

    ; pad with zeros while r10 is ok
.flt_zeros_lop:
    cmp r10, 0
    jle .flt_skip_zeros
    mov byte [rsi], '0'
    add rsi, 1
    sub r10, 1
    jmp .flt_zeros_lop
.flt_skip_zeros:
    
    pop r13

    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop


.float_zero_print:
    ; now, r9 = precision r8 = width
    ; print 0.{N} + paddings

    cmp byte [r14 - 1], 'e'
    je .float_zero_print_e

    test r9, r9
    jz .float_zero_print_zero_precision

    lea rcx, [rsi + r8 - 2] ; minus size of  "0." + "0"*r9
    sub rcx, r9
    cmp rsi, rcx
    jae @f
    call .padding_proc
@@:

    mov word [rsi], '.' * 256 + '0'
    add rsi, 2

    ; pad with zeros needed count
    lea rcx, [rsi + r9]
    vmovdqa ymm0, ymm15
    vmovdqa ymm15, ymm9
    call .padding_proc
    vmovdqa ymm15, ymm0

    ; pad with what there was to end if it was negative sizing
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop
    
.float_zero_print_zero_precision:
    test rdi, F_ALTERNATE
    jnz .float_zero_print_zero_precision_alternate

    cmp r8, 0
    jle @f
    lea rcx, [rsi + r8 - 1]
    call .padding_proc
@@:

    mov byte [rsi], '0'
    add rsi, 1
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop
    
.float_zero_print_zero_precision_alternate:

    cmp r8, 1
    jle @f
    lea rcx, [rsi + r8 - 2]
    call .padding_proc
@@:

    mov word [rsi], '0.'
    add rsi, 2
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop



.float_zero_print_e:
    test r9, r9
    jz .float_zero_print_e_zero_precision

    lea rcx, [rsi + r8 - 2 - 5] ; minus size of  "0." + "0"*r9 + "e+000"
    sub rcx, r9
    cmp rsi, rcx
    jae @f
    call .padding_proc
@@:

    mov word [rsi], '0.'
    add rsi, 2

    ; pad with zeros needed count
    lea rcx, [rsi + r9]
    vmovdqa ymm0, ymm15
    vmovdqa ymm15, ymm9
    call .padding_proc
    vmovdqa ymm15, ymm0

    ; add 'e+000'
    mov dword [rsi], 'e+00'
    mov byte [rsi + 4], '0'
    add rsi, 5

    ; pad with what there was to end if it was negative sizing
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop
    
.float_zero_print_e_zero_precision:
    test rdi, F_ALTERNATE
    jnz .float_zero_print_e_zero_precision_alternate

    cmp r8, 0
    jle @f
    lea rcx, [rsi + r8 - 1 - 5]
    call .padding_proc
@@:

    mov dword [rsi], '0e+0'
    mov word [rsi + 4], '00'
    add rsi, 6
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop
    
.float_zero_print_e_zero_precision_alternate:

    cmp r8, 1
    jle @f
    lea rcx, [rsi + r8 - 2]
    call .padding_proc
@@:

    mov dword [rsi], '0.e+'
    mov dword [rsi + 4], '000'
    add rsi, 7
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop


    
    if STRICT_GNU
.float_zero_exponent:
    test rax, rax
    jz .float_zero_print
    ; denormalized number, set exponent to -1022 = 1
    mov rdx, 1
    jmp .float_zero_exponent_denormalized
    end if

.float_load_from_rbx:
    mov rdx, [rbx]
    add rbx, 8
    jmp .float_loaded

; ------------------------------- %e ----------------------------------
.float_e_spec:
    ; now, 
    ; rax = base10 mantiss
    ; r10 = power

    ; here it is good, becouse length =
    ; length = r9 + 1 + 1 + 1 + 1 + 3
    ;       <prec>+'.'+'d'+'e'+'+'+<exp>

    ; calculate width - length in rdx
    lea rdx, [r8 - 7]
    lea rcx, [r8 - 8] ; if there is sign, decrease width
    cmp r12, 0
    cmovl rdx, rcx ; - 1 if there is sign
    test rdi, F_SIGN
    cmovnz rdx, rcx ; - 1 if there is sign

    ; if r9 == 0 and it isn't F_ALTERNATE, decrease one more
    mov  rcx, rdi
    and  ecx, F_ALTERNATE
    or   rcx, r9
    sub  rcx, 1
    adc  rdx, 0

    ; sub precision
    sub rdx, r9 

    ; rdx = padding width
    
    ; also comparing it
    jle .float_e_skip_forward_padding
    lea rcx, [rsi + rdx]
    call .padding_proc
.float_e_skip_forward_padding:


    ; print sign
    test rdi, F_SIGN
    jnz .float_e_sign_flag_presented
    mov byte [rsi], '-'
    shr r12, 63
    add rsi, r12 ; add 1 if r12 < 0
.float_e_sign_flag_presented_continue:



if COMPRESS_SMALL_PRECISION_E_FLOAT
    cmp r9, 12 ; if precision isn't that much, we will compress digits of number
    jae .float_e_compress_skipping
    ; to compress number we will use simple formula:
    ; power_to_compress = ~log10(rax) - r9 - 1
    
    bsr rcx, rax
    imul rcx, 1233
    shr rcx, 12
    sub rcx, r9
    sub rcx, 1
    cmp rcx, 0
    jle .float_e_compress_skipping

    ; function g([bigint]$x,[bigint]$m, [bigint]$s){$r=($x*$m)-shr64n;$t=(($x-$r)-shr1n) + $r;$t-shr($s-1n)}

    mov r12, rax
    ; now divide result by number on 10^rdx
    lea rdx, [div_10_pow_multiplers]
    mul qword [rdx + rcx * 8 - 8]
    mov rax, r12
    sub rax, rdx
    shr rax, 1
    add rax, rdx
    lea rdx, [div_10_pow_shifts]
    movzx edx, byte [rdx + rcx - 1]
    shrx rax, rax, rdx
    add r10, rcx
    ; now,
    ; rax = base10 mantiss [cutted]
    ; r10 = updated power
.float_e_compress_skipping:
end if

    ; now, print all digits to buffer
    push r13 ; allocate one more register
    mov rcx, 0x28f5c28f5c28f5c3 ; divisor [gained from clang]
    lea r13, [rsi + 32] ; number will 100% fit in 32 digits
.float_e_printloop:
    ; rax = base10 value
    ; r10 = power
    ; rcx = divisor
    ; r13 = destination

    ; /= 100
    mov r12, rax
    shr rax, 0x2
    mul rcx
    mov rax, rdx
    shr rax, 0x2
    imul rdx, rax, 0x64
    sub rdx, r12
    neg rdx
    ; now, rdx = remainder, rax = result

    lea r12, [integer_numbers]
    movzx r12, word [r12 + 2 * rdx]
    
    sub r13, 2
    mov [r13], r12w
    
    test rax, rax
    jnz .float_e_printloop
    
    ; check if we printed leading '0'
    cmp byte [r13], '0'+1
    adc r13, 0


    ; printed power += actually printed count after '.'
    ; => r10 += rsi + 32 - r13 - 1
    lea rax, [rsi + 31]
    sub rax, r13
    lea r10, [r10 + rax]
    

    test rdi, F_ALTERNATE
    jnz .float_e_skip_zero_precision_check
    test r9, r9
    jz .float_e_non_zero_value_zero_precision
.float_e_skip_zero_precision_check:

    ; copy to rsi
    vmovdqu ymm0, [r13]
    vmovdqu [rsi + 1], ymm0
    movzx eax, byte [rsi + 1] ; copy digit
    mov byte [rsi], al
    mov byte [rsi + 1], '.'
    
    ; check if need to pad with zeros
    ; count of current printed = rsi + 32 - r13 - 2   (2 = digit + '.')
    ; => need to pad = r9 - rsi - 30 + r13
    ; => from new rsi = rsi + r9 + 2 - rax
    lea rax, [r9 + r13 - 30]
    sub rax, rsi
    ; cmp rax, 0 is already ready
    jle .float_e_skip_zero_precision_padding
    vmovdqa ymm0, ymm15
    vmovdqa ymm15, ymm9
    mov r12, rsi
    lea rsi, [rsi + r9 + 2]
    push rcx
    mov rcx, rsi
    sub rsi, rax
    call .padding_proc
    pop rcx
    vmovdqa ymm15, ymm0
    mov rsi, r12 ; restore rsi to update futher
.float_e_skip_zero_precision_padding:

    ; printed count = 2 + r9
    lea rsi, [rsi + r9 + 2]
    
    ; add it to number
    mov eax, 'e' + '+'*256
    mov edx, 'e' + '-'*256
    mov r13, r10
    neg r13
    cmp r10, 0
    cmovl eax, edx
    cmovl r10, r13
    mov [rsi], ax
    
    ; now, need to print r10 as 3 digit number
    mov rax, r10
    shr rax, 2
    mul rcx
    mov rax, rdx
    shr rax, 2
    imul rdx, rax, 0x64
    sub rdx, r10
    neg rdx
    ; now rdx = 2 digit number, and rax = left number
    add rax, '0'
    mov [rsi + 2], rax
    lea r12, [integer_numbers]
    movzx ecx, word [r12 + 2 * rdx]
    mov [rsi + 3], cx
    add rsi, 5

    ; restore register
    pop r13

    ; return
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop

.float_e_sign_flag_presented:
    mov ecx, '+'
    mov edx, '-'
    cmp r12, 0
    cmovl ecx, edx
    mov [rsi], cl
    add rsi, 1
    jmp .float_e_sign_flag_presented_continue

.float_e_non_zero_value_zero_precision:

    ; copy one digit
    movzx eax, byte [r13] ; copy digit
    mov [rsi], al
    
    ; add it to number
    mov eax, 'e' + '+'*256
    mov edx, 'e' + '-'*256
    mov r13, r10
    neg r13
    cmp r10, 0
    cmovl eax, edx
    cmovl r10, r13
    mov [rsi + 1], ax
    
    ; now, need to print r10 as 3 digit number
    mov rax, r10
    shr rax, 2
    mul rcx
    mov rax, rdx
    shr rax, 2
    imul rdx, rax, 0x64
    sub rdx, r10
    neg rdx
    ; now rdx = 2 digit number, and rax = left number
    add rax, '0'
    mov [rsi + 3], rax
    lea r12, [integer_numbers]
    movzx ecx, word [r12 + 2 * rdx]
    mov [rsi + 4], cx
    
    add rsi, 6 ; total 6 numbers

    ; restore register
    pop r13

    ; return
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop

; ------------------------------- %g ------------------------------

.float_g_spec:

    mov dword [rsi], 'no%g'
    add rsi, 4
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop


; ---------------------------------------------------------- inegers ---------------------------------------------------------

.switch_integer:
    mov rax, [rbx]
    test rdi, F_LONG
    jnz .integer_int64_from_32
    mov eax, eax
.integer_int64_from_32:

    add r14, 1 ; skip 'd'/'i'
    add rbx, 8 ; move registers array forward

    ; simply allocate buffer and use same technology as in %e
    ; N <=20 digits
    ; N = 3x8 digits = 3 x 32bit
    ; N = 6 x 4 digits = 6 x 16bit
    ; N = 12 x 2 digit = 12 x 8 bit?
    ; to bct + store ...

    ; break by 8 (2 divisions)
    
    mov rcx, rsp
    and rcx, -32 ; get aligned buffer
    
    mov rdx, -6067343680855748867
    mov r12, rax
    mul rdx
    mov r10, rdx ; load hi part
    shr r10, 26 ; r10 = n/1e8
    imul rax, r10, 100000000 ; rax = round(n,1e8)
    mov rdx, r12
    sub rdx, rax ; rdx = remainder
    mov [rcx - 8], rdx ; store hi part
    mov rdx, 368934881475
    mov rax, r10
    mul rdx
    shr edx, 1
    imul rax, rdx, 100000000
    sub r10, rax ; get remainder
    mov rdx, 4153837486827862103
    mov rax, r12
    mul rdx
    mov [rcx - 16], r10 ; store middle part
    shr rdx, 51 ; n / 1e16
    mov [rcx - 24], rdx ; store leftmost part
    xor rdx, rdx
    mov [rcx - 32], rdx ; store zero

    vmovdqa ymm0, [rcx - 32] ; now 3 x 8
    ; divide it on 1e4
    vbroadcastsd ymm3, [div1e4_number_64bit]
    vpmuludq ymm4, ymm0, ymm3 ; ymm4 = ?? ?? AA BB AA BB AA BB | 64 bit
    vpsrlq ymm5, ymm4, 45     ; ymm5 = ?? ?? 00 XX 00 XX 00 XX | 64 bit  XX = 32bit/1e4
    vbroadcastsd ymm3, [mul1e4_number_64bit]
    vpmuludq ymm4, ymm5, ymm3 ; ymm4 = ?? ?? 00 YY 00 YY 00 YY | 64 bit  YY = round(32bit, 1e4)
    vpsubq ymm0, ymm0, ymm4   ; ymm0 = ?? ?? 00 RR 00 RR 00 RR | 64 bit  RR = 32bit%1e4
    vpsllq ymm0, ymm0, 32     ; ymm0 = ?? ?? XX 00 XX 00 XX 00 | 64 bit  XX = 32bit/1e4
    vpor ymm0, ymm0, ymm5     ; ymm0 = ?? ?? XX RR XX RR XX RR | 32 bit, 1e4
    ; divide it on 1e2
    vpsrld ymm4, ymm0, 2      ; divide on 4 : n / 4 / 25 [100 = 4 * 25]
    vbroadcastsd ymm3, [div1e2_number_32bit]

    ; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    vpmulld ymm4, ymm4, ymm3  ; ymm4 = multiplication result | 32 bit

    vpsrld ymm5, ymm4, 17     ; ymm5 = result of division    | 32 bit 16bit/1e2
    vbroadcastsd ymm3, [mul1e2_number_32bit]
    
    ; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    vpmulld ymm4, ymm5, ymm3  ; ymm4 = multiplication result | 32 bit round(16bit, 1e2)
    
    vpsubd ymm0, ymm0, ymm4   ; ymm0 = n - round(n, 1e2)     | 32 bit 16bit%1e2
    vpslld ymm0, ymm0, 16     ; ymm0 = ... X 0 X 0 X 0       | 32 bit, hi16bit = 16bit/1e2
    vpor ymm0, ymm0, ymm5     ; ymm0 = ... X R X R X R       | 16 bit, 1e2
    ; convert them to numbers
    vbroadcastsd ymm3, [div1e1_number_16bit]
    vpmullw ymm4, ymm0, ymm3
    vpsrlw ymm5, ymm4, 11      ; ymm5 = 16bit/10
    vbroadcastsd ymm3, [mul1e1_number_16bit]
    vpmullw ymm4, ymm5, ymm3  ; ymm4 = round(16bit, 10)
    vpsubw ymm0, ymm0, ymm4   ; ymm0 = 16bit%10
    vpsllw ymm0, ymm0, 8      ; ymm0 = high number
    vpor ymm0, ymm0, ymm5
    vbroadcastsd ymm3, [number_print_shift]
    ; get mask of used values
    vpxor ymm4, ymm4, ymm4
    vpcmpeqb ymm5, ymm4, ymm0
    vpmovmskb eax, ymm5
    not eax
    vpaddb ymm0, ymm0, ymm3   ; ymm0 = string
    vmovdqa [rcx - 32], ymm0
    ; get position of first non zero
    tzcnt eax, eax
    ; eax = 32 - length of number
    ; so, calculate padding:
    vmovdqu ymm0, [rcx + rax - 32]
    lea rdx, [r8 + rax - 32] ; rdx = total width
    cmp rdx, 0
    jle .integer_skip_first_padding
    lea rcx, [rsi + rdx]
    call .padding_proc
.integer_skip_first_padding:
    ; now, store to rsi
    vmovdqu [rsi], ymm0
    neg rax ; rax = length - 32
    lea rsi, [rsi + rax + 32]
    
    cmp r8, 0
    jl .check_end_padding
    jmp .main_loop


; --------------------------------------------------------- percent -----------------------------------------------------------

.insert_percent:
    mov [rsi], byte '%'
    add rsi, 1 ; update destination buffer
    add r14, 2 ; skip '%'
    jmp .main_loop

; --------------------------------------------------------- helpers -----------------------------------------------------------

.check_end_padding:
    ; r11 = rsi at beginning
    sub r11, rsi ; now, r11 = - count of chars
    sub r11, r8 ; now, r11 = -count - (-width) = -count + width = width - count
    cmp r11, 0 ; if it is negative, we need to pad it.
    jle .main_loop
    lea rcx, [rsi + r11]        
    
    call .padding_proc
    jmp .main_loop

    ; rsi = destination
    ; rcx = end position [pointer] - this addresss dont guaranted to be set.
    ; ymm15 = filler [prepared by flags loop]
.padding_proc:
    ; moves rsi to rcx.
    vmovdqu [rsi], ymm15
    add rsi, 32
    cmp rsi, rcx
    jge .padding_done
    and rsi, -32 ; align it
    lea rdx, [rsi + 128]
    cmp rdx, rcx
    ja .repeat_small_set
.repeat_set:
    vmovdqa [rdx-128], ymm15
    vmovdqa [rdx-96], ymm15
    vmovdqa [rdx-64], ymm15
    vmovdqa [rdx-32], ymm15
    add rdx, 128
    cmp rdx, rcx
    jbe .repeat_set
    lea rsi, [rdx - 128]
.repeat_small_set:
    vmovdqa [rsi], ymm15
    add rsi, 32
    cmp rsi, rcx
    jb .repeat_small_set
.padding_done:
    mov rsi, rcx
    ret
}

macro printf_core_data fn_name {

div1e4_number_64bit:
    dq 3518437209
mul1e4_number_64bit:
    dq 10000

div1e2_number_32bit:
    dd 5243, 5243
mul1e2_number_32bit:
    dd 100, 100

div1e1_number_16bit:
    dw 205, 205, 205, 205
mul1e1_number_16bit:
    dw 10, 10, 10, 10

number_print_shift:
    db "00000000000000000000000000000000"

float_mantiss_base:
    dq 0x000FFFFFFFFFFFFF

float_mantiss_bit:
    dq 0x0010000000000000

; float tables
include 'float_tables.inc'

powers_of_10:
    p = 1
    repeat 19
        dq p
        p = p * 10
    end repeat

align 64
flag_jump_table:
    dq fn_name#.flag_space; ' '
    dq fn_name#.flag_default; '!'
    dq fn_name#.flag_default; '"'
    dq fn_name#.flag_prefix; '#'
    dq fn_name#.flag_default; '$'
    dq fn_name#.flag_default; '%'
    dq fn_name#.flag_default; '&'
    dq fn_name#.flag_splitter; '''
    dq fn_name#.flag_default; '('
    dq fn_name#.flag_default; ')'
    dq fn_name#.flag_wildcard; '*'
    dq fn_name#.flag_plus; '+'
    dq fn_name#.flag_default; ','
    dq fn_name#.flag_minus; '-'
    dq fn_name#.flag_precision; '.'
    dq fn_name#.flag_default; '/'
    dq fn_name#.flag_zero_width; '0'
    dq fn_name#.flag_width; '1'
    dq fn_name#.flag_width; '2'
    dq fn_name#.flag_width; '3'
    dq fn_name#.flag_width; '4'
    dq fn_name#.flag_width; '5'
    dq fn_name#.flag_width; '6'
    dq fn_name#.flag_width; '7'
    dq fn_name#.flag_width; '8'
    dq fn_name#.flag_width; '9'

align 64
final_jump_table:
    dq fn_name#.switch_default; '@'
    dq fn_name#.switch_default; 'A'
    dq fn_name#.switch_default; 'B'
    dq fn_name#.switch_char; 'C'
    dq fn_name#.switch_integer; 'D'
    dq fn_name#.switch_float; 'E'
    dq fn_name#.switch_float; 'F'
    dq fn_name#.switch_float; 'G'
    dq fn_name#.switch_default; 'H'
    dq fn_name#.switch_integer; 'I'
    dq fn_name#.switch_default; 'J'
    dq fn_name#.switch_default; 'K'
    dq fn_name#.switch_default; 'L'
    dq fn_name#.switch_default; 'M'
    dq fn_name#.switch_default; 'N'
    dq fn_name#.switch_default; 'O'
    dq fn_name#.switch_default; 'P'
    dq fn_name#.switch_default; 'Q'
    dq fn_name#.switch_default; 'R'
    dq fn_name#.switch_string; 'S'
    dq fn_name#.switch_default; 'T'
    dq fn_name#.switch_integer; 'U'
    dq fn_name#.switch_default; 'V'
    dq fn_name#.switch_default; 'W'
    dq fn_name#.switch_default; 'X'
    dq fn_name#.switch_default; 'Y'
    dq fn_name#.switch_default; 'Z'
    dq fn_name#.switch_default; '['
    dq fn_name#.switch_default; '\'
    dq fn_name#.switch_default; ']'
    dq fn_name#.switch_default; '^'
    dq fn_name#.switch_default; '_'
}
