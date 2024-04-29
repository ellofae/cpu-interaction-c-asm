global cpuid_call

section .text

cpuid_call:
    mov r10, rdi
    mov r11, rsi
    mov r12, rdx
    mov r13, rcx

    mov rax, qword [r10]
    mov rcx, qword [r11]
    cpuid

    mov dword [r10], eax
    mov dword [r11], ebx
    mov dword [r12], ecx
    mov dword [r13], edx
    ret
