#include "bcm2835/uart.h"
#include "init/ramfs.h"
#include "kernel/el.h"
#include "kernel/exec.h"
#include "kernel/ml.h"

void exec(char * filename) {
    void * up_text = (void *)ML_U_TEXT;
    if (ramfs_load(filename, up_text)) {
        el10(up_text);
        return;
    }
    uart_puts(filename);
    uart_puts(": file not found\n");
}
