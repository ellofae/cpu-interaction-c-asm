#ifndef _MSR_MODULE_H_
#define _MSR_MODULE_H_

#define uint32 unsigned long

#define IAEFER_IA32e_ENABLE_BIT_OFFSET 8
#define IAEFER_IA32e_ACTIVE_BIT_OFFSET 10

#define DEFAULT_COLOR "\033[0m"
#define GREEN_COLOR "\x1b[32m"
#define RED_COLOR "\x1b[31m"

enum cpuid_registers {
    CPUID_EXTENDED_FEATURES_REGISTER = 0x80000001U
};

enum msr_registers {
    IA32_EFER_REGISTER = 0xC0000080U
};

typedef struct {
    uint32 eax;
    uint32 ebx;
    uint32 ecx;
    uint32 edx;
} cpu_registers;

#endif