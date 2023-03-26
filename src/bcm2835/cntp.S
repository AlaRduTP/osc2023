#include "bcm2835/cntp.h"

.section ".text"

.global cntp_enable

cntp_enable:
    SUB     sp, sp, 0x8
    STR     x30, [sp, 0x8]
    MOV     x0, #1
    MSR     cntp_ctl_el0, x0
    BL      cntp_set_timer
    MOV     x0, #2
    LDR     x1, =CORE0_TIMER_IRQ_CTRL
    STR     w0, [x1]
    LDR     x30, [sp, 0x8]
    ADD     sp, sp, 0x8
    RET

.global cntp_set_timer

cntp_set_timer:
    MRS     x1, cntfrq_el0
    MUL     w1, w1, w0
    UXTW    x1, w1
    MSR     cntp_tval_el0, x1
    RET
