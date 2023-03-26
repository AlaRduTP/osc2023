#include "kernel/ml.h"

#define CORE0_TIMER_IRQ_CTRL 0x40000040

.section ".text"
.global el21

// switch exception level from 2 to 1
el21:
    MOV     x1, 1 << 31
    MSR     hcr_el2, x1
    MOV     x1, #0x3c5
    // 0x3c5 =
    // 0b001111000101
    //     1111       : PSTATE.{D,A,I,F}
    //            101 : EL1, SP_EL1
    MSR     spsr_el2, x1
    MSR     elr_el2, lr
    ERET

.extern evt
.global el10

// switch exception level from 1 to 0
// and branch to the user program
el10:
    MSR     elr_el1, x0
    MOV     x1, #0x340
    // 0x340 = 
    // 0b001101000000
    //     1101       : PSTATE.{D,A,I,F}
    //            000 : EL0, SP_EL0
    MSR     spsr_el1, x1
    LDR     x1, =evt
    MSR     vbar_el1, x1
    MOV     x1, #ML_U_STACK_TOP
    MSR     sp_el0, x1
    // enable coer timer
    MOV     x0, #1
    MSR     cntp_ctl_el0, x0
    MRS     x0, cntfrq_el0
    MSR     cntp_tval_el0, x0
    MOV     x0, #2
    LDR     x1, =CORE0_TIMER_IRQ_CTRL
    STR     w0, [x1]
    ERET
