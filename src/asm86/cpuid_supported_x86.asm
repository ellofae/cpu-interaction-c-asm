; the ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction.
; If a software procedure can set and clear this flag, the processor executing the procedure
; supports the CPUID instruction.
global check_cpuid_supported

section .text

check_cpuid_supported:
    pushfd
    mov edx, [esp]
    bts dword [esp], 21
    jnc bit_changed
    jmp not_supported
    ret

bit_changed:
    popfd

    pushfd
    cmp [esp], edx
    jz not_supported

    mov [esp], edx
    popfd
    mov eax, 1
    ret
    
not_supported:
    popfd
    mov eax, 0
    ret