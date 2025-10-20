#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_GROUPS 10
#define MAX_OUTPUT 4096

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "%s: Usage: %s <regexp> <pattern> <text>\n", argv[0], argv[0]);
        return 1;
    }

    char *regexp = argv[1];
    char *pattern = argv[2];
    char *text = argv[3];

    regex_t regex;
    regmatch_t groups[MAX_GROUPS];
    int ret;

    ret = regcomp(&regex, regexp, REG_EXTENDED);
    if (ret != 0) {
        char error_msg[256];
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "regex compilation error: %s\n", error_msg);
        return 1;
    }

    ret = regexec(&regex, text, MAX_GROUPS, groups, 0);
    
    if (ret == REG_NOMATCH) {
        printf("%s\n", text);
        regfree(&regex);
        return 0;
    } else if (ret != 0) {
        char error_msg[256];
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "regex execution error: %s\n", error_msg);
        regfree(&regex);
        return 1;
    }

    int num_groups = 0;
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (groups[i].rm_so == -1) break;
        num_groups = i + 1;
    }

    char output[MAX_OUTPUT];
    int out_pos = 0;

    int match_start = groups[0].rm_so;
    int match_end = groups[0].rm_eo;
    
    for (int i = 0; i < match_start; i++) {
        output[out_pos++] = text[i];
    }

    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] == '\\' && pattern[i+1] != '\0') {
            if (pattern[i+1] == '\\') {
                output[out_pos++] = '\\';
                i++;
            } else if (pattern[i+1] >= '0' && pattern[i+1] <= '9') {
                int group_num = pattern[i+1] - '0';
                i++;
                
                if (group_num >= num_groups) {
                    fprintf(stderr, "error: reference to non-existent group \\%d\n", group_num);
                    regfree(&regex);
                    return 1;
                }
                
                int start = groups[group_num].rm_so;
                int end = groups[group_num].rm_eo;
                for (int j = start; j < end; j++) {
                    output[out_pos++] = text[j];
                }
            } else {
                output[out_pos++] = pattern[i];
            }
        } else {
            output[out_pos++] = pattern[i];
        }
    }

    for (int i = match_end; text[i] != '\0'; i++) {
        output[out_pos++] = text[i];
    }
    
    output[out_pos] = '\0';

    printf("%s\n", output);

    regfree(&regex);
    return 0;
}
