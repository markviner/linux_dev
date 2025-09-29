#include <stdio.h>
#include "outlib.h"

void output(char *str) {
    printf("%d: %s\n", Count++, str);
}

void usage(char *prog) {
    (void)prog; // аргумент больше не нужен
    fprintf(stderr,
        "prog v%.2f: Print all arguments\n\t"
        "Usage: prog arg1 [arg2 […]]\n", VERSION);
}
