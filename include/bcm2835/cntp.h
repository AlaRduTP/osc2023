#ifndef BCM2835_CNTP
#define BCM2835_CNTP

#define CORE0_TIMER_IRQ_CTRL 0x40000040U

#ifndef __ASSEMBLER__

void cntp_enable();
void cntp_set_timer(unsigned int sec);

#endif

#endif