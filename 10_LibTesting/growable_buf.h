#ifndef GROWABLE_BUF_H
#define GROWABLE_BUF_H

#include <stdlib.h>

#define GROWABLE_BUF_INIT 10
#define GROWABLE_BUF_INCREMENT 10

typedef struct {
    char *buf;
    size_t len;
    size_t cap;
} growable_buf;

void growable_buf_init(growable_buf *buf);
void growable_buf_add(growable_buf *buf, char c);
void growable_buf_free(growable_buf *buf);

#endif
