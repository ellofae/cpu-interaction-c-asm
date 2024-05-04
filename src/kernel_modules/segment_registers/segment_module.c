#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "segment_module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ellofae");

static void read_cs_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%cs, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void read_ss_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%ss, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void read_ds_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%ds, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void read_es_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%es, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void read_fs_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%fs, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void read_gs_register(uint16 *segment_register) {
    asm (
        "xor %%eax, %%eax\n\t"
        "mov %%gs, %%ax\n\t"
        : "=a" (*segment_register)
        :
        : 
    );

    return;
}

static void segment_register_info(char *register_name, uint16 reg_value) {
    printk(KERN_INFO "Segment Register - %s, Register Value - %x\n", register_name, reg_value);
    printk(KERN_INFO "RPL=%d, Descriptor Table: %s, Index: %d\n\n", reg_value & 0x03, 
        ((reg_value >> 2) & 0x01) ? "LDT (Local Descriptor Table)" : "GDT (Global Descriptor Table)",
        (reg_value >> 3) & 0x1FFF);
}

static int segment_module_init(void) {
    printk(KERN_ALERT "Inside the %s procedure\n", __FUNCTION__);

    segment_registers registers;  

    read_cs_register(&registers.cs);
    read_ss_register(&registers.ss);
    read_ds_register(&registers.ds);
    read_es_register(&registers.es);
    read_fs_register(&registers.fs);
    read_gs_register(&registers.gs);

    segment_register_info("CS", registers.cs);
    segment_register_info("SS", registers.ss);
    segment_register_info("DS", registers.ds);
    segment_register_info("ES", registers.es);
    segment_register_info("FS", registers.fs);
    segment_register_info("GS", registers.gs);

    return 0;
}

static void segment_module_exit(void) {
    printk(KERN_ALERT "Outside the %s procedure\n", __FUNCTION__);
    return;
}

module_init(segment_module_init);
module_exit(segment_module_exit);