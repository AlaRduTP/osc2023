#include "lib/queue.h"

unsigned int cbuf_push(struct cbuf * buf, char c) {
    if (!(buf->f & CBUF_OVERWRITE) && cbuf_full(buf)) {
        return 0;
    }
    buf->b[buf->i] = c;
    buf->i = (buf->i + 1) % CBUF_SIZE;
    if (cbuf_empty(buf)) {
        buf->o = (buf->o + 1) % CBUF_SIZE;
    }
    return 1;
}

unsigned int cbuf_pop(struct cbuf * buf) {
    if (cbuf_empty(buf)) {
        return '\0';
    }
    char c = buf->b[buf->o];
    buf->o = (buf->o + 1) % CBUF_SIZE;
    return c;
}
