#include <stdio.h>
#include <string.h>

#include "op_flags.h"
#include "cpu_registers.h"
#include "logger.h"

static system_flags flags;

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

    return 0;
}