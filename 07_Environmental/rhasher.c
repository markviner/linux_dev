#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "rhash.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

/* check the chosen hash algo */
int get_algorithm(const char *name) {
    if (!name) return 0;
    if (strcasecmp(name, "md5") == 0) return RHASH_MD5;
    if (strcasecmp(name, "sha1") == 0) return RHASH_SHA1;
    if (strcasecmp(name, "tth") == 0) return RHASH_TTH;
    return 0;
}

int main() {
    rhash_library_init();

    char *line = NULL;
    size_t len = 0;

    printf("rhasher> Enter command (exml: MD5 file.txt or sha1 \"hello\")\n");

    while(1) {
#ifdef USE_READLINE
        char *input = readline("rhasher> ");
        if (!input) break;
        if (*input) add_history(input);
        line = strdup(input);
        free(input);
        if (!line) break;
#else
        printf("rhasher> ");
        fflush(stdout);
        ssize_t read_bytes = getline(&line, &len, stdin);
        if (read_bytes < 0) break;
        if (read_bytes > 0 && line[read_bytes - 1] == '\n')
            line[read_bytes - 1] = '\0';
#endif
        /* the first arg -> name of an algo */ 
        /* the second -> arg */
        char *alg = strtok(line, " \t");
        char *arg = strtok(NULL, " \t");

        if (!alg || !arg) {
            fprintf(stderr, "error: enter algo name and str or file name\n");
            free(line);
            line = NULL;
            continue;
        }

        int alg_type = get_algorithm(alg);
        if (!alg_type) {
            fprintf(stderr, "error: unknown algo name '%s'\n", alg);
            free(line);
            line = NULL;
            continue;
        }

        unsigned char hash[64];
        int hash_len = rhash_get_digest_size(alg_type);

        int result = 0;

        /* whether the arg is a str... */
        if (arg[0] == '"') {
            char *text = arg + 1;
            size_t text_len = strlen(text);
            if (text[text_len - 1] == '"') text[text_len - 1] = '\0';
            result = rhash_msg(alg_type, text, strlen(text), hash);
        } else {
            /* its a file name*/
            result = rhash_file(alg_type, arg, hash);
        }

        if (result < 0) {
            fprintf(stderr, "error in hash computations: %s\n", strerror(errno));
            free(line);
            line = NULL;
            continue;
        }

        int flags = isupper((unsigned char)alg[0]) ? RHPR_HEX : RHPR_BASE64;

        char output[256];
        rhash_print_bytes(output, hash, hash_len, flags);
        printf("%s\n", output);

        free(line);
        line = NULL;
    }
    free(line);
    printf("\nexit.\n");
    return 0;
}
