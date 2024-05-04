#ifndef _CPU_REGISTERS_H_
#define _CPU_REGISTERS_H_

#define uint32 unsigned int
#define uint16 unsigned short

extern uint32 check_cpuid_supported(); 
extern uint32 cpuid_call(uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx);

extern void read_cs_reg(uint16 *cs_reg);
extern void read_ss_reg(uint16 *ss_reg);
extern void read_ds_reg(uint16 *ds_reg);
extern void read_es_reg(uint16 *es_reg);
extern void read_fs_reg(uint16 *fs_reg);
extern void read_gs_reg(uint16 *gs_reg);

typedef struct {
    uint32 eax;
    uint32 ebx;
    uint32 ecx;
    uint32 edx;
} cpu_registers;

typedef struct {
    uint16 cs;
    uint16 ss;
    uint16 ds;
    uint16 es;
    uint16 fs;
    uint16 gs;
} segment_registers;

#endif