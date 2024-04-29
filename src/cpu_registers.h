#ifndef _CPU_REGISTERS_H_
#define _CPU_REGISTERS_H_

#define uint32 unsigned int

extern uint32 check_cpuid_supported(); 
extern uint32 cpuid_call(uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx);

typedef struct {
    uint32 eax;
    uint32 ebx;
    uint32 ecx;
    uint32 edx;
} cpu_registers;

#endif