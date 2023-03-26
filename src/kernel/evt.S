.extern svc_hndlr
.extern irq_hndlr

.section ".text"

.global evt

.align 11
evt:
  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7

  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7

  B     svc_hndlr  // SVC
  .align 7
  B     irq_hndlr   // IRQ
  .align 7
  ERET
  .align 7
  ERET
  .align 7

  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7
  ERET
  .align 7
