#include <stdio.h>
#include <string.h>

#include "op_flags.h"
#include "cpu_registers.h"
#include "logger.h"

static system_flags flags;

static void get_cpu_vendor(cpu_registers *registers);

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

    return 0;
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