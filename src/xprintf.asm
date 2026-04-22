format ELF64

include 'printf_core.inc'

; configs

BUFFER_SIZE = 10*1024

; --- data ---

REAL_BUFFER_SIZE = BUFFER_SIZE + 4*1024


; mask to use it in blend
section '.rodata' align 32
xprintf.blend_mask_table:
    times 32 db 0x00
    times 32 db 0xFF


section '.text' executable

public xprintf

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
; <-- output [BUFFER_SIZE + 4kb buffer]
; <<-- real buffer size is BUFFER_SIZE, so, if you write less than
; <<-- 4kb of data, you may check buffer only once in begining
; <<-- rsi points on top of this buffer

; pollutes rax, rdx, rcx, rdi, rsi, r11
macro flush_buffer {
    mov eax, 1
    mov edi, 1
    mov rdx, rsi
    mov rsi, rsp
    sub rdx, rsi
    add rbp, rdx
    syscall
    mov rsi, rsp
}

; ----------------------------- end of printf

xprintf.end_printf:

    ; flush buffer
    flush_buffer
    
    vzeroupper

    ; restore rsp
    mov rax, rbp
    lea rsp, [rsp + REAL_BUFFER_SIZE + LOCAL_VARIABLES_SIZE]
    ; pop all registers
    pop rbx
    pop r15
    pop r14
    pop rbp
    pop rdx
    ; skip 'shadow space'
    add rsp, 4 * 8
    ; restore return address
    mov [rsp], rdx
    ret

; -------------------------------------- begin of printf

xprintf:
    ; replace first ~6 args to make an array.
    mov rax, [rsp]
    mov [rsp], r9
    push r8
    push rcx
    push rdx
    push rsi
    ; store return address
LOCAL_VARIABLES_SIZE = 0
LOCAL_DATA_SIZE = 8 * (1 + 4) + LOCAL_VARIABLES_SIZE ; 1 return address, 4 saved registers
    push rax
    ; store used registers
    push rbp
    push r14
    push r15
    push rbx
    ; local variables
    ; <empty>
    

; rsi = destination [top of buffer]
; r15 = max top of buffer [to compare with]
; r14 = source [position in string]
; rbx = current argument [pointer] ; first stack arg is at [rsp + BUFFER_SIZE + LOCAL_DATA_SIZE + 8*6]
; rbp = pointer on local variables
    mov r14, rdi
    lea rbx, [rsp + LOCAL_DATA_SIZE]
    sub rsp, REAL_BUFFER_SIZE ; allocate data
    mov rsi, rsp
    lea r15, [rsp + BUFFER_SIZE]
    xor ebp, ebp
    
.main_loop:

; ----- find first "%" in source -------

    ; set registers to zero and to '%'
    vpxor ymm1, ymm1, ymm1
    mov eax, '%'
    vmovd xmm2, eax
    vpbroadcastb ymm2, xmm2
    
.search_loop:

    ; before searching check owerflow
    cmp rsi, r15
    jb @f
    flush_buffer
@@:

; search unaligned part
    
    mov rcx, r14
    and r14, -32 ; global offset
    
    and rcx, 31  ; local offset
    neg rcx      ; negative to use LUT

    vmovdqa ymm0, [r14]
    lea rax, [xprintf.blend_mask_table] ; uzhas
    vmovdqu ymm6, [rax + 32 + rcx] ; load blend mask
    vpcmpeqb ymm3, ymm0, ymm1
    vpcmpeqb ymm4, ymm0, ymm2
    vpor ymm5, ymm3, ymm4
    vpand ymm7, ymm6, ymm5 ; apply blend mask to result to remove false-positive behaviour

    ; update text at rsi
    vmovdqu ymm8, [rsi + rcx]        ; ! usage of red zone :) [may be negative offset]
    vpblendvb ymm8, ymm8, ymm0, ymm6 ; mix real data and new data
    vmovdqu [rsi + rcx], ymm8        ; store result 

    ; use add becouse rcx = - offset
    ; move rsi forward [becouse in '.found' it will be moved backward]
    lea rsi, [rsi + rcx + 32]

    vptest ymm7, ymm7 ; check if there is any '\0' or '%'
    jz .search_small_loop
    
    ; now, we had found symbol, get it's position.
    vpmovmskb eax, ymm7
    ; rcx - is shifted, it is ok
    jmp .found ; go to found
    
    ; serach for zero
.search_small_loop:

    repeat 4
        add r14, 32
        vmovdqa ymm0, [r14]
        vmovdqu [rsi], ymm0   ; |- copy data to result buffer
        add rsi, 32           ; |
        vpcmpeqb ymm3, ymm0, ymm1
        vpcmpeqb ymm4, ymm0, ymm2
        vpor ymm5, ymm3, ymm4
        vptest ymm5, ymm5
        jnz .found_in_small_loop
    end repeat
    
    ; check if owerflow occured
    cmp rsi, r15
    jb @f
    flush_buffer ; pollutes rcx, but it is unused futher.
@@:
    
    jmp .search_small_loop

.found_in_small_loop:
    
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
    printf_core xprintf

    ; now, r14 100% points on '%'.
    ; for now, support only %c

    ; cmp byte [r14 + 1], 'c' it is always so
    
    cmp rsi, r15
    jbe @f
    flush_buffer
@@:
    ; take next argument and print it to buffer
    mov al, [rbx]
    mov [rsi], al
    add rsi, 1
    add r14, 2 ; skip %c
    add rbx, 8

    jmp .main_loop
