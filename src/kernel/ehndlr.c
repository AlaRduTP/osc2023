#include "bcm2835/uart.h"

void _svc_hndlr() {
    unsigned int spsr;
    asm("MRS x0, spsr_el1");
    asm("MOV %w0, w0":"=r"(spsr));
    uart_puts("spsr_el1 = ");
    uart_pu32h((unsigned int)spsr);
    uart_send('\n');
    unsigned int elr;
    asm("MRS x0, elr_el1");
    asm("MOV %w0, w0":"=r"(elr));
    uart_puts("elr_el1  = ");
    uart_pu32h((unsigned int)elr);
    uart_send('\n');
    unsigned int esr;
    asm("MRS x0, esr_el1");
    asm("MOV %w0, w0":"=r"(esr));
    uart_puts("esr_el1  = ");
    uart_pu32h((unsigned int)esr);
    uart_send('\n');
}

static inline void set_timer(unsigned int sec) {
    unsigned int frq;
    asm("MRS  x0, cntfrq_el0");
    asm("MOV  %w0, w0":"=r"(frq));
    frq *= sec;
    asm("UXTW x0, %w0"::"r"(frq));
    asm("MSR  cntp_tval_el0, x0");
}

void _irq_hndlr() {
    unsigned int frq;
    asm("MRS x0, cntfrq_el0");
    asm("MOV %w0, w0":"=r"(frq));
    unsigned int pct;
    asm("MRS x0, cntpct_el0");
    asm("MOV %w0, w0":"=r"(pct));
    unsigned int sec = pct / frq;
    uart_puts("seconds after booting = ");
    uart_pu32h(sec);
    uart_puts(" sec\n");
    set_timer(2);
}
