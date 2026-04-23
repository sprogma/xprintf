format ELF64

include 'xprintf_config.asm'

include 'printf_core.asm'

; data
REAL_BUFFER_SIZE = 0

; lookup tables
section '.rodata' align 64

    align 64
xsprintf.blend_mask_table:
    times 32 db 0x00
    times 32 db 0xFF

    align 64
xsprintf.shufA:
    ; X means 0x80 producing zero
    ; 0  => 0 1 2 ... 13 14 15 | 0 1 2 ... 14 15
    ; 1  => 1 2 3 ... 14 15  X | 1 2 3 ... 15 15
    ; 2  => 2 3 .. 14 15  X  X | 2 3 .. 15 15 15
    ; 3  => ...
    ; 16 => X X X ...  X  X  X | 15 ... 15 15 15
    ; 17 => X X X ...  X  X  X | 15 ... 15 15 15
    ; 18 => ...
    repeat 32
        n = % - 1
        repeat 16
            i = % - 1 + n
            if i < 16 
                db i
            else 
                db 0x80 
            end if
        end repeat
        repeat 16
            i = % - 1 + n
            if i < 16 
                db i 
            else 
                db 15 
            end if
        end repeat
    end repeat

    align 64
xsprintf.shufB:
    ; X means 0x80 producing zero
    ; 0  => X X X ... X X X | X X X ... X X X
    ; 1  => X X X ... X X 0 | X X X ... X X X
    ; 2  => X X X ... X 0 1 | X X X ... X X X
    ; 3  => X X ... X 0 1 2 | X X X ... X X X
    ; 4  => ...
    ; 15 => 0 1 .. 13 14 15 | X X X ... X X X
    ; 16 => 1 2 .. 14 15 15 | X X X ... X X X
    ; 17 => 2 3 .. 15 15 15 | X X X ... X X X
    ; 18 => ...
    repeat 32
        n = % - 1
        repeat 16
            if n < 16 ; first type
                i = % - 1
                if i >= (16 - n) 
                    db i - (16 - n) 
                else 
                    db 0x80 
                end if
            else ; 2nd type
                i = % - 1 + (n - 16)
                if i < 16 
                    db i 
                else 
                    db 15 
                end if
            end if
        end repeat
        repeat 16
            db 0x80
        end repeat
    end repeat


section '.data' writable align 64

    printf_core_data xsprintf
    

section '.text' executable writeable

public xsprintf

;
; +inf
; ...
; 9
; 8
; 7
; ret
; 
; ------>
; +inf
; ...
; 9 
; 8
; 7 
; 6 <- rsp + 48 <- real stack beginning
; 5
; 4
; 3
; 2
; 1
; ret <- rsp
; <<-- rsi points on top of destination buffer

; ----------------------------- end of printf

xsprintf.end_printf:

    vzeroupper

    ; add trailing zero
    mov byte [rsi], 0

    ; restore rsp
    mov rax, rbp
    lea rsp, [rsp + LOCAL_VARIABLES_SIZE]
    ; pop all registers
    pop r13
    pop rbx
    pop r14
    pop rbp
    pop rdx
    ; skip 'shadow space'
    add rsp, 3 * 8
    ; restore return address
    mov [rsp], rdx
    ret

xsprintf.fast_return:
    mov byte [rdi], 0
    ret

; -------------------------------------- begin of printf

xsprintf:
    cmp byte [rsi], 0
    je .fast_return
    ; replace first ~6 args to make an array.
    mov rax, [rsp]
    mov [rsp], r9
    push r8
    push rcx
    push rdx
    ; store return address
LOCAL_VARIABLES_SIZE = 8*8
LOCAL_DATA_SIZE = 8 * (1 + 4) + LOCAL_VARIABLES_SIZE ; 1 return address, 4 saved registers
    push rax
    ; store used registers
    push rbp
    push r14
    push rbx
    push r13
    ; local variables
    sub rsp, LOCAL_VARIABLES_SIZE
    test al, al
    jz .skip_float_input
    movsd [rsp], xmm0
    movsd [rsp+8], xmm1
    movsd [rsp+16], xmm2
    movsd [rsp+24], xmm3
    movsd [rsp+32], xmm4
    movsd [rsp+40], xmm5
    movsd [rsp+48], xmm6
    movsd [rsp+56], xmm7
.skip_float_input:
    

; rsi = destination [top of buffer]
; r14 = source [position in string]
; rbx = current argument [pointer] ; first stack arg is at [rsp + BUFFER_SIZE + LOCAL_DATA_SIZE + 8*6]
; rbp = pointer on local variables
    mov r14, rsi
    mov r13, rsp
    mov rsi, rdi
    lea rbx, [rsp + LOCAL_DATA_SIZE]
    mov rbp, rsi
    
; ----- find first "%" in source -------

    ; set registers to zero and to '%'
    vpxor ymm1, ymm1, ymm1
    mov eax, '%'
    vmovd xmm2, eax
    vpbroadcastb ymm2, xmm2
    mov eax, ' '
    vmovd xmm8, eax
    vpbroadcastb ymm8, xmm8
    mov eax, '0'
    vmovd xmm9, eax
    vpbroadcastb ymm9, xmm9

.main_loop:
    if OPTIMIZE_SEQUENCE_FORMATS
        cmp byte [r14], '%'
        je .found_speedly
    end if
    mov rcx, r14
    and r14, -32 ; global offset
    and rcx, 31  ; local offset
    
    ; load source
    vmovdqa  ymm0, [r14]

    ; swap hi|low parts
    vperm2i128 ymm3, ymm0, ymm0, 0x11

    ; load masks and shuffles
    ; 4 * 8 = 32 = sizeof(ymm0)
    lea rdx, [rcx * 4]
    lea rax, [xsprintf.shufA]
    vmovdqa ymm4, [rax + rdx * 8]
    vmovdqa ymm5, [rax + rdx * 8 + (xsprintf.shufB - xsprintf.shufA)]

    ; shuffle vectors
    vpshufb ymm0, ymm0, ymm4
    vpshufb ymm3, ymm3, ymm5
    ; join
    vpor ymm7, ymm0, ymm3

    ; test resulting vector on bad symbols
    vpcmpeqb ymm3, ymm7, ymm1
    vpcmpeqb ymm4, ymm7, ymm2   
    vpor ymm5, ymm3, ymm4 ; join
    
    ; store
    vmovdqu [rsi], ymm7

    vptest ymm5, ymm5
    jnz .found_in_beginning

    ; now, in rsi is located "32 - rcx" right bytes
    add rsi, 32
    sub rsi, rcx
    
    ; serach for zero
.search_small_loop:

    add r14, 32
    vmovdqa ymm0, [r14]
    vpcmpeqb ymm3, ymm0, ymm1
    vpcmpeqb ymm4, ymm0, ymm2
    vmovdqu [rsi], ymm0   ; |- copy data to result buffer
    vpor ymm5, ymm3, ymm4
    add rsi, 32           ; |
    vptest ymm5, ymm5
    jz .search_small_loop
    
    ; found in loop
    vpmovmskb eax, ymm5
    
    ; now
    ; eax = mask of characters
    ; r14 = start position of block
.found:
    ; move exactly to character
    tzcnt eax, eax ; get position of char
    add r14, rax
    lea rsi, [rsi + rax - 32] ; step back & move only on rax bytes


    ; now, r14 points on zero or on '%'. check it
    cmp byte [r14], 0
    jz .end_printf

    ; use prinf core to update from command
    printf_core_code xsprintf

    jmp .main_loop

.found_in_beginning:
    add r14, rcx ; skip this count of chars, becouse them aren't counted in rax
    add rsi, 32
    vpmovmskb eax, ymm5
    jmp  .found

if OPTIMIZE_SEQUENCE_FORMATS
.found_speedly:
    mov eax, -1
    add rsi, 32
    jmp .found
end if
