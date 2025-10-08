#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long start = 0, end = 0, step = 1;
    long current;

    if (argc == 1) {
        printf("Usage:\n");
        printf("  %s stop [default: start=0, step=1]\n", argv[0]);
        printf("  %s start stop [default: step=1]\n", argv[0]);
        printf("  %s start stop step\n", argv[0]);
        return 0;
    }

    if (argc == 2) {
        start = 0;
        end = atol(argv[1]);
    } else if (argc == 3) {
        start = atol(argv[1]);
        end = atol(argv[2]);
    } else if (argc == 4) {
        start = atol(argv[1]);
        end = atol(argv[2]);
        step = atol(argv[3]);
    } else {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    for (current = start; (step > 0) ? current < end : current > end; current += step) {
        printf("%ld\n", current);
    }

    return 0;
}
