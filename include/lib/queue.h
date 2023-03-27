#ifndef _QUEUE_H
#define _QUEUE_H

#define CBUF_SIZE      0x100U

#define CBUF_OVERWRITE  (1U << 0)

#define cbuf_init(x, g) ((x)->i = (x)->o = 0, (x)->f = (g))
#define cbuf_empty(x)   ((x)->i == (x)->o)
#define cbuf_full(x)    (((x)->i + 1) % CBUF_SIZE == (x)->o)

struct cbuf {
    unsigned int f;
    unsigned int i;
    unsigned int o;
    char b[CBUF_SIZE];
};

unsigned int cbuf_push(struct cbuf * buf, char c);
unsigned int cbuf_pop(struct cbuf * buf);

#endif