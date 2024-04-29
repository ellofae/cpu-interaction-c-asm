section .bss
    eax_stored resb 4


section .text

global cpuid_call

cpuid_call:
    push ebx
    mov ebx, esp

    mov eax, dword [esp + 8]
    mov ecx, dword [esp + 16]

    mov eax, [eax]
    mov ecx, [ecx]

    cpuid
    
    mov [eax_stored], eax

    mov eax, dword [esp + 12]
    mov dword [eax], ebx

    mov eax, dword [esp + 16]
    mov dword [eax], ecx

    mov eax, dword [esp + 20]
    mov dword [eax], edx

    mov eax, [eax_stored]

    pop ebx
    ret