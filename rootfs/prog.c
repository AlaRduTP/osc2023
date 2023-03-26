#include "bcm2835/uart.h"

void _start() {
    for (unsigned int i = 0; i < 5; ++i) {
        uart_puts("[*] SVC 0 !!!\n");
        asm("SVC 0");
    }
    do {} while(1);
}
