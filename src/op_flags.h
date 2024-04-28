#ifndef _OP_FLAGS_H_
#define _OP_FLAGS_H_

#define ARCH_OPTION_X86 "--arch=x86"
#define ARCH_OPTION_X86_64 "--arch=x86_64"

enum system_architecture {
    ARCH_X86,
    ARCH_X86_64,
};

typedef struct _private_arch_config {
    enum system_architecture system_arch;
} architecture_configuration;

typedef struct _private_sys_flags {
    architecture_configuration arch_config;
} system_flags; 

#endif