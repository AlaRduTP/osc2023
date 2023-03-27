#include "bcm2835/uart.h"
#include "fs/cpio.h"
#include "fs/file.h"
#include "init/fdt.h"
#include "init/ramfs.h"
#include "lib/string.h"
#include "lib/utils.h"

#define ramfs_traverse(cpiof) {\
    struct cpio _cpio; \
    char * _addr = ramfs_addr(); \
    cpio_open_archive(&_cpio, _addr, CPIO_NEWC); \
    while (cpio_read_archive(&_cpio) != CPIO_EARCHIVE) { \
        struct cpio_file cpiof; \
        cpio_extract(&_cpio, &cpiof);
#define _end }}

static char * _ramfs_addr = 0;

static void _callback(struct fdt_node * node) {
    struct fdt_prop * prop = node->prpty;
    while (prop) {
        if (!strcmp(prop->name, "linux,initrd-start")) {
            _ramfs_addr = (char *)(unsigned long long int)load_big32u(prop->val);
            return;
        }
        prop = prop->next;
    }
}

static unsigned int _cmp(struct fdt_node * node) {
    return !strcmp(node->name, "chosen");
}

static inline char * ramfs_addr() {
    if (!_ramfs_addr) {
        fdt_traverse(_callback, _cmp);
    }
    return _ramfs_addr;
}

void ramfs_ls() {
    ramfs_traverse(file) {
        uart_puts(file.name);
        uart_send('\n');
    } _end;
}

void ramfs_cat(char * filename) {
    ramfs_traverse(cpio_file) {
        if (!strcmp(cpio_file.name, filename)) {
            struct file file;
            cpio_open(&cpio_file, &file);
            return pfile(&file);
        }
    } _end;
    uart_puts(filename);
    uart_puts(": file not found\n");
}

static inline void _ramfs_load(struct file * file, char * addr) {
    char c;
    while (read(file, &c, 1)) {
        *(addr++) = c;
    }
}

int ramfs_load(char * filename, void * addr) {
    ramfs_traverse(cpio_file) {
        if (!strcmp(cpio_file.name, filename)) {
            struct file file;
            cpio_open(&cpio_file, &file);
            _ramfs_load(&file, (char *)addr);
            return 1;
        }
    } _end;
    return 0;
}
