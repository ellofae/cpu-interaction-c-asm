#include <stdio.h>
#include <string.h>

#include "op_flags.h"
#include "cpu_registers.h"
#include "logger.h"

static system_flags flags;

static void print_binary(unsigned int value);
static void get_cpu_vendor(cpu_registers *registers);
static void read_misc_security_info_bits(cpu_registers *registers);
static void read_segment_registers(void);

int main(int argc, char** argv) {
    flags.arch_config.system_arch = ARCH_X86;
    flags.arch_config.system_privilage = USER_PRIVILAGE;

    if (argc == 2) {
        if (strcmp(*(argv + 1), ARCH_OPTION_X86) == 0) {
            flags.arch_config.system_arch = ARCH_X86;
        } else if (strcmp(*(argv + 1), ARCH_OPTION_X86_64) == 0) {
            flags.arch_config.system_arch = ARCH_X86_64;
        }
    }

    uint32 result = 0;
    result = check_cpuid_supported();

    if (!result) {
        log_message(LOG_ERROR, "System doesn't implement cpuid usage\n");
        return 1;
    }
    log_message(LOG_INFO, "System implements cpuid usage\n");

    cpu_registers registers;
    registers.eax = 0;
    registers.ecx = 0; 

    get_cpu_vendor(&registers);
    
    registers.eax = 7;
    registers.ecx = 0;

    read_misc_security_info_bits(&registers);

    read_segment_registers();

    return 0;
}

static void print_binary(unsigned int value) {
    int num_bits;
    
    num_bits = sizeof(unsigned long long) * 8;
    for (int i = num_bits - 1; i >= 0; i--) {
        int bit = (value >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

static void get_cpu_vendor(cpu_registers *registers) {
    char vendor_str[3 * sizeof(uint32) + 1];

    uint32 result;
    result = cpuid_call(&registers->eax, &registers->ebx, &registers->ecx, &registers->edx);
    memcpy(vendor_str, &registers->ebx, sizeof(uint32));
    memcpy(vendor_str + sizeof(uint32) * 1, &registers->edx, sizeof(uint32));
    memcpy(vendor_str + sizeof(uint32) * 2, &registers->ecx, sizeof(uint32));
    vendor_str[sizeof(uint32) * 3] = '\0';

    log_message(LOG_INFO, "CPU Vendor - %s\n", vendor_str);
}

static void read_misc_security_info_bits(cpu_registers *registers) {
    uint32 result;
    result = cpuid_call(&registers->eax, &registers->ebx, &registers->ecx, &registers->edx);

    if ((registers->ebx >> 2) & 0x1) {
        log_message(LOG_INFO, "Software Guard Extensions (SGX) feature - supported\n");
    } else {
        log_message(LOG_WARNING, "Software Guard Extensions (SGX) feature - unsupported\n");
    }

    if ((registers->ebx >> 7) & 0x1) {
        log_message(LOG_INFO, "Supervisor-Mode Execution Prevention (SMEP) feature - supported\n");
    } else {
        log_message(LOG_WARNING, "Supervisor-Mode Execution Prevention (SMEP) feature - unsupported\n");
    }

    if ((registers->ebx >> 20) & 0x1) {
        log_message(LOG_INFO, "Supervisor-Mode Access Prevention (SMAP) feature - supported\n");
    } else {
        log_message(LOG_WARNING, "Supervisor-Mode Access Prevention (SMAP) feature - unsupported\n");
    }
}

static void segment_register_info(char *register_name, uint16 reg_value) {
    log_message(LOG_INFO, "Segment Register - %s, Register Value - %x\n", register_name, reg_value);
    log_message(LOG_INFO, "RPL=%d, Descriptor Table: %s, Index: %d\n\n", reg_value & 0x03, 
        ((reg_value >> 2) & 0x01) ? "LDT (Local Descriptor Table)" : "GDT (Global Descriptor Table)",
        (reg_value >> 3) & 0x1FFF);
}

static void read_segment_registers(void) {
    log_message(LOG_INFO, "There are several segment registers available: CS, SS. DS, ES, FS, GS\n");
    log_message(LOG_INFO, "Accessing segment registers in ring 3 (userspace)\n\n");

    segment_registers registers;  

    read_cs_reg(&registers.cs);
    read_ss_reg(&registers.ss);

    segment_register_info("CS", registers.cs);
    segment_register_info("SS", registers.ss);

    log_message(LOG_WARNING, "Other segment registers are zeros in userspace\n");

    return;
}