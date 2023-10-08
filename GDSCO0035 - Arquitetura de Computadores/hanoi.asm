;Compile: nasm -f elf32 assignment.asm
;Link:    gcc -m32 assignment.o

;nasm -f elf32 assignment.asm && gcc -m32 assignment.o

section .data
    output_format:  db  "%d. Mover da Torre %d para a Torre %d", 10, 0    ; The printf format + "\n" + '\0'
    start_msg: db "Insira o numero de discos ate 6: ", 0
    input_format: db "%d", 0

    msg_lwr: db "O numero minimo de discos eh 1!", 10, 0
    msg_grt: db "O numero maximo de discos eh 6!", 10, 0

section .bss
    s_vector: resw 127

section .text
    extern printf
    extern scanf
    global main

main:
    push ebp
    mov ebp, esp

    push start_msg
    call printf
    add esp, 4

    lea eax, [ebp-4]
    push eax
    push input_format
    call scanf
    add esp, 8

    mov eax, [ebp-4]

    cmp eax, 6
    jg error_grt

    cmp eax, 1
    jl error_lwr

    xor ecx, ecx
    push 2                          ; aux
    push 3                          ; destiny
    push 1                          ; origin
    push eax                        ; n_disks
    call solve
    add esp, 16

    mov dword[s_vector + ecx], -1
    add ecx, 4
    jmp vector2stack

    error_grt:
        push msg_grt
        call printf
        jmp exit

    error_lwr:
        push msg_lwr
        call printf
        jmp exit

    solve:                          ; parameters: (n_disks[+8], origin[+12], destiny[+16], aux[+20]) -> stack
        push ebp
        mov ebp, esp

        cmp dword[ebp+8], 1        ; if n_disks == 1
        jne solve_1

        call vector_write
        mov esp, ebp
        pop ebp
        ret
        solve_1:
            mov eax, dword[ebp+8]
            dec eax

            push dword[ebp+16]      ; destiny
            push dword[ebp+20]      ; aux
            push dword[ebp+12]      ; origin
            push eax                ; n_disks-1
            call solve
            add esp, 16

            call vector_write

            mov eax, dword[ebp+8]
            dec eax
            
            push dword[ebp+12]      ; origin
            push dword[ebp+16]      ; destiny
            push dword[ebp+20]      ; aux
            push eax                ; n_disks-1
            call solve
            add esp, 16

            mov esp, ebp
            pop ebp
            ret

    vector_write:
        mov eax, dword[ebp+12]     ; origin tower
        mov dword[s_vector + ecx], eax
        add ecx, 4
        
        mov eax, dword[ebp+16]      ; destiny tower
        mov dword[s_vector + ecx], eax
        add ecx, 4

        ret

    vector2stack:
        cmp ecx, -4
        je pre_print
        push dword[s_vector + ecx]
        sub ecx, 4
        jmp vector2stack

    pre_print:
        mov ecx, 1
    print_solution:
        cmp dword[esp], -1
        je exit
        
        push ecx
        push output_format
        call printf

        mov ecx, [esp+4]
        inc ecx
        add esp, 16

        jmp print_solution

    exit:
        mov esp, ebp
        pop ebp

        xor eax, eax
        ret