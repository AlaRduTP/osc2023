export PATH := /usr/local/opt/llvm/bin:$(PATH)

PROG := prog

BCM := ../src/bcm2835
SRC := $(BCM)/uart.c
OBJ := $(SRC:.c=.o)

ARC := aarch64-elf
LDF := -m aarch64elf -nostdlib -T linker.ld

CPU := cortex-a53

CFLAGS := --target=$(ARC) -mcpu=$(CPU)
CINCLD := -I ../include

INITRAMFS := ../initramfs.cpio

.PHONY: clean

all: clean $(PROG)
	rm -rf $(addsuffix .o,$(PROG)) $(addsuffix .elf,$(PROG))
	find . | cpio -o -H newc > $(INITRAMFS)

$(PROG): %: %.o $(OBJ)
	ld.lld $(LDF) -o $@.elf $^
	llvm-objcopy -I $(ARC) -O binary $@.elf $@

%.o: %.c
	clang $(CFLAGS) $(CINCLD) -c $< -o $@

%.o: %.S
	clang $(CFLAGS) $(CINCLD) -c $< -o $@

clean:
	rm -rf $(INITRAMFS) $(PROG) $(addsuffix .o,$(PROG)) $(addsuffix .elf,$(PROG))
