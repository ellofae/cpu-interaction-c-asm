#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "msr_module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ellofae");

static void cpuid_call(uint32 *eax_reg, uint32 *ebx_reg, uint32* ecx_reg, uint32 *edx_reg) {
    asm volatile (
        "cpuid\n\t"
        : "=a" (*eax_reg), "=b" (*ebx_reg), "=c" (*ecx_reg), "=d" (*edx_reg)
        : "a" (*eax_reg), "c" (*ecx_reg)
        : // No clobbered registers
    );

    return;
}

static uint32 readmsr_call(uint32 msr_register) {
    register uint32 rax asm("rax");
    asm("rdmsr\n"
        "shlq $32, %%rdx\n"
        "addq %%rdx,%%rax\n"
        : "=a" (rax)
        : "c" (msr_register)
        : "rdx"
    );

    if (rax & (1 << IAEFER_IA32e_ENABLE_BIT_OFFSET)) {
        printk(KERN_INFO "%sIA32e Mode Enable Bit - Enabled%s\n", GREEN_COLOR, DEFAULT_COLOR);
    } else {
        printk(KERN_INFO "%sIA32e Mode Enable Bit - Disabled%s\n", RED_COLOR, DEFAULT_COLOR);
    }

    if (rax & (1 << IAEFER_IA32e_ACTIVE_BIT_OFFSET)) {
        printk(KERN_INFO "%sIA32e Mode Active Bit - Enabled%s", GREEN_COLOR, DEFAULT_COLOR);
    } else {
        printk(KERN_INFO "%sIA32e Mode Active Bit - Disabled%s", RED_COLOR, DEFAULT_COLOR);
    }

    return rax;
}

static int msr_module_init(void) {
    printk(KERN_ALERT "Inside the %s procedure\n", __FUNCTION__);

    cpu_registers registers;

    registers.eax = 0x80000001;
    registers.ecx = 0;
    cpuid_call(&registers.eax, &registers.ebx, &registers.ecx, &registers.edx);

    if (!(0x1 & (registers.edx >> 20)) && !(0x1 & (registers.edx >> 29))) {
        printk(KERN_ALERT "%sIA32_EFER MSR register is not supported on the platform%s\n", RED_COLOR, DEFAULT_COLOR);
    }

    registers.eax = 0x00;
    registers.ecx = (uint32) IA32_EFER_REGISTER;
    uint32 result = readmsr_call(registers.ecx);

    printk(KERN_ALERT "MSR Call Ret: %x\n", result);
    return 0;
}

static void msr_module_exit(void) {
    printk(KERN_ALERT "Outside the %s procedure\n", __FUNCTION__);
    return;
}

module_init(msr_module_init);
module_exit(msr_module_exit);