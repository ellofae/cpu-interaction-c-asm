#include <stdio.h>
#include <string.h>
#include "op_flags.h"

static system_flags flags;

int main(int argc, char** argv) {
    flags.arch_config.system_arch = ARCH_X86;

    if (argc == 2) {
        if (strcmp(*(argv + 1), ARCH_OPTION_X86) == 0) {
            flags.arch_config.system_arch = ARCH_X86;
        } else if (strcmp(*(argv + 1), ARCH_OPTION_X86_64) == 0) {
            flags.arch_config.system_arch = ARCH_X86_64;
        }
    }

    

    return 0;
}