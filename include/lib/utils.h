#ifndef _UTILS_H
#define _UTILS_H

// get the lower 32-bit of a system register
#define get32sys(v, s) {\
    asm volatile("MRS x0, " #s);\
    asm volatile("MOV %w0, w0":"=r"(v));\
}

unsigned int load_big32u(char * addr);

#endif