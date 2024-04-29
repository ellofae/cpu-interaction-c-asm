; the ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction.
; If a software procedure can set and clear this flag, the processor executing the procedure
; supports the CPUID instruction.
global check_cpuid_supported

section .text

check_cpuid_supported:
    pushfq
    mov r10, [rsp]
    bts qword [rsp], 21
    jnc bit_changed
    jmp not_supported
    ret

bit_changed:
    popfq

    pushfq
    cmp [rsp], r10
    jz not_supported

    mov [rsp], r10
    popfq
    mov eax, 1
    ret
    
not_supported:
    popfq
    mov eax, 0
    ret