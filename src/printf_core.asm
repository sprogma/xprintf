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
F_PREFIX = 0x400 ; '#'
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
    or rdi, F_PREFIX
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
    ; eax is already loaded, but it is char-' '
    movzx eax, byte [r14]
    and eax, -33 ; normalize
    sub eax, 64 ; '@' = 0

    ; now, assume that al is less or equal to 95 - 64 = 31.
    lea rcx, [final_jump_table]
    jmp qword [rcx + rax * 8]

    ; cases
.switch_default: ; %c for now





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
    

.insert_percent:
    mov [rsi], byte '%'
    add rsi, 1 ; update destination buffer
    add r14, 2 ; skip '%'
    jmp .main_loop

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
    cmp rsi, rcx
    jge .padding_done
    add rsi, 32
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
    dq fn_name#.switch_default; 'D'
    dq fn_name#.switch_default; 'E'
    dq fn_name#.switch_default; 'F'
    dq fn_name#.switch_default; 'G'
    dq fn_name#.switch_default; 'H'
    dq fn_name#.switch_default; 'I'
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
    dq fn_name#.switch_default; 'U'
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
