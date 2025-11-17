#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include "config.h"

int ask(const char *question) {
    while (1) {
        printf("%s", question);
        fflush(stdout);

        char buf[64];
        if (!fgets(buf, sizeof(buf), stdin)) {
            fprintf(stderr, "%s\n", gettext("Error: input closed"));
            exit(1);
        }

        if (buf[0] == 'Y' || buf[0] == 'y') return 1;
        if (buf[0] == 'N' || buf[0] == 'n') return 0;

        printf("%s\n", gettext("Please answer Yes or No"));
    }
}

int main() {
    setlocale(LC_ALL, "");
    
    bindtextdomain("guessnum", "../share/locale");
    textdomain("guessnum");
    
    printf("%s\n", gettext("Think of a number from 1 to 100."));

    int low = 1, high = 100;

    while (low < high) {
        int mid = (low + high) / 2;
        char question[128];
        snprintf(question, sizeof(question), gettext("Is your number greater than %d? (Yes/No): "), mid);

        if (ask(question))
            low = mid + 1;
        else
            high = mid;
    }

    printf(gettext("Your number is %d!\n"), low);
    return 0;
}
