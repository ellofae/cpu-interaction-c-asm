#ifndef _SEGMENT_REGISTERS_H_
#define _SEGMENT_REGISTERS_H_

#define uint16 unsigned short

typedef struct {
    uint16 cs;
    uint16 ss;
    uint16 ds;
    uint16 es;
    uint16 fs;
    uint16 gs;
} segment_registers;

#endif