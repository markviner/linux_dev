#include "growable_buf.h"
#include <string.h>
#include <stdio.h>

void growable_buf_init(growable_buf *buf) {
    buf->len = 0;
    buf->cap = GROWABLE_BUF_INIT;
    buf->buf = (char *)malloc(buf->cap);
}

void growable_buf_add(growable_buf *buf, char c) {
    if (buf->len == buf->cap) {
        buf->cap += GROWABLE_BUF_INCREMENT;
        buf->buf = (char *)realloc(buf->buf, buf->cap);
    }
    buf->buf[buf->len++] = c;
}

void growable_buf_free(growable_buf *buf) {
    if (buf && buf->buf) {
        free(buf->buf);
        buf->buf = NULL;
        buf->len = 0;
        buf->cap = 0;
    }
}
