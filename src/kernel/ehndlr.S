// save general registers to stack
.macro SAVE_ALL
    SUB     sp, sp, 32 * 8
    STP     x0, x1, [sp, 16 * 0]
    STP     x2, x3, [sp, 16 * 1]
    STP     x4, x5, [sp, 16 * 2]
    STP     x6, x7, [sp, 16 * 3]
    STP     x8, x9, [sp, 16 * 4]
    STP     x10, x11, [sp, 16 * 5]
    STP     x12, x13, [sp, 16 * 6]
    STP     x14, x15, [sp, 16 * 7]
    STP     x16, x17, [sp, 16 * 8]
    STP     x18, x19, [sp, 16 * 9]
    STP     x20, x21, [sp, 16 * 10]
    STP     x22, x23, [sp, 16 * 11]
    STP     x24, x25, [sp, 16 * 12]
    STP     x26, x27, [sp, 16 * 13]
    STP     x28, x29, [sp, 16 * 14]
    STR     x30, [sp, 16 * 15]
.endm

// load general registers from stack
.macro LOAD_ALL
    LDP     x0, x1, [sp, 16 * 0]
    LDP     x2, x3, [sp, 16 * 1]
    LDP     x4, x5, [sp, 16 * 2]
    LDP     x6, x7, [sp, 16 * 3]
    LDP     x8, x9, [sp, 16 * 4]
    LDP     x10, x11, [sp, 16 * 5]
    LDP     x12, x13, [sp, 16 * 6]
    LDP     x14, x15, [sp, 16 * 7]
    LDP     x16, x17, [sp, 16 * 8]
    LDP     x18, x19, [sp, 16 * 9]
    LDP     x20, x21, [sp, 16 * 10]
    LDP     x22, x23, [sp, 16 * 11]
    LDP     x24, x25, [sp, 16 * 12]
    LDP     x26, x27, [sp, 16 * 13]
    LDP     x28, x29, [sp, 16 * 14]
    LDR     x30, [sp, 16 * 15]
    ADD     sp, sp, 32 * 8
.endm

.extern _svc_hndlr
.extern _irq_hndlr

.section ".text"

.global svc_hndlr

svc_hndlr:
    SAVE_ALL
    BL      _svc_hndlr
    LOAD_ALL
    ERET

.global irq_hndlr

irq_hndlr:
    SAVE_ALL
    BL      _irq_hndlr
    LOAD_ALL
    ERET
