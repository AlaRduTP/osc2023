#ifndef _UTILS
#define _UTILS

#define get32sys(v, s) {\
    asm volatile("MRS x0, " #s);\
    asm("MOV %w0, w0":"=r"(v));\
}

unsigned int load_big32u(char * addr);

#endif