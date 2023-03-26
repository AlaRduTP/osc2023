#include "bcm2835/cntp.h"
#include "bcm2835/uart.h"
#include "utils.h"

void _svc_hndlr() {
    unsigned int spsr;
    get32sys(spsr, spsr_el1);
    uart_puts("spsr_el1 = ");
    uart_pu32h((unsigned int)spsr);
    uart_send('\n');
    unsigned int elr;
    get32sys(elr, elr_el1);
    uart_puts("elr_el1  = ");
    uart_pu32h((unsigned int)elr);
    uart_send('\n');
    unsigned int esr;
    get32sys(esr, esr_el1);
    uart_puts("esr_el1  = ");
    uart_pu32h((unsigned int)esr);
    uart_send('\n');
}

void _irq_hndlr() {
    unsigned int frq;
    get32sys(frq, cntfrq_el0);
    unsigned int pct;
    get32sys(pct, cntpct_el0);
    unsigned int sec = pct / frq;
    uart_puts("seconds after booting = ");
    uart_pu32h(sec);
    uart_puts(" sec\n");
    cntp_set_timer(2);
}
