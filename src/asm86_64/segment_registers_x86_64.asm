section .text

global read_cs_reg
global read_ss_reg
global read_ds_reg
global read_es_reg
global read_fs_reg
global read_gs_reg

read_cs_reg:
    xor rax, rax
    mov ax, cs

    mov [rdi], rax
    ret

read_ss_reg:
    xor rax, rax
    mov ax, ss

    mov [rdi], rax
    ret

read_ds_reg:
    xor rax, rax
    mov ax, ds

    mov [rdi], rax
    ret

read_es_reg:
    xor rax, rax
    mov ax, es

    mov [rdi], rax
    ret

read_fs_reg:
    xor rax, rax
    mov ax, fs

    mov [rdi], rax
    ret

read_gs_reg:
    xor rax, rax
    mov ax, gs

    mov [rdi], rax
    ret