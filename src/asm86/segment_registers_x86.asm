section .text

global read_cs_reg
global read_ss_reg
global read_ds_reg
global read_es_reg
global read_fs_reg
global read_gs_reg

read_cs_reg:
    xor eax, eax
    mov ax, cs
    mov [esp + 4], ax
    ret            

read_ss_reg:
    xor eax, eax
    mov ax, ss
    mov [esp + 4], ax
    ret            

read_ds_reg:
    xor eax, eax
    mov ax, ds
    mov [esp + 4], ax
    ret            

read_es_reg:
    xor eax, eax
    mov ax, es
    mov [esp + 4], ax
    ret            

read_fs_reg:
    xor eax, eax
    mov ax, fs
    mov [esp + 4], ax
    ret            

read_gs_reg:
    xor eax, eax
    mov ax, gs
    mov [esp + 4], ax
    ret            