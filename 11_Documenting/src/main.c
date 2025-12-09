/**
 * @file main.c
 * @brief Number guessing game with optional Roman numeral support
 * 
 * This program implements a number guessing game where the computer
 * tries to guess a number the user is thinking of. Optionally supports
 * Roman numerals for display.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include <argp.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define N_(STRING) STRING

/**
 * @brief Minimum number in the guessing range
 */
#define MIN_NUMBER 1

/**
 * @brief Maximum number in the guessing range
 */
#define MAX_NUMBER 100

/**
 * @brief Flag indicating whether to use Roman numerals
 */
static int use_roman = 0;

/**
 * @brief Roman numeral representations for numbers 1-100
 * 
 * This table contains pre-computed Roman numeral strings for all
 * numbers in the valid range.
 */
static const char *roman_numerals[101] = {
    "",
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

static char doc_string[] = N_("guessnum -- a number guessing game\n\n"
    "The program tries to guess a number you are thinking of between 1 and 100.");

static char args_doc[] = "";

static struct argp_option options[] = {
    {"roman", 'r', 0, 0, N_("Use Roman numerals for display")},
    {0}
};

/**
 * @brief Parse command line options
 * 
 * @param key The option key
 * @param arg The option argument
 * @param state The argp state
 * @return Error code or 0 on success
 */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'r':
            use_roman = 1;
            break;
        case ARGP_KEY_ARG:
            argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, 0, 0, 0, 0};

/**
 * @brief Convert an integer to Roman numeral representation
 * 
 * @param num The number to convert (must be between 1 and 100)
 * @return Pointer to static string containing Roman numeral
 */
const char *to_roman(int num) {
    if (num < 1 || num > 100)
        return "?";
    return roman_numerals[num];
}

/**
 * @brief Ask a yes/no question and get user's response
 * 
 * This function repeatedly prompts the user until a valid Yes/No answer
 * is provided. It handles EOF gracefully by exiting the program.
 * 
 * @param question The question string to display
 * @return 1 if user answered Yes, 0 if No
 */
int ask(const char *question) {
    while (1) {
        printf("%s", question);
        fflush(stdout);
        char buf[64];
        if (!fgets(buf, sizeof(buf), stdin)) {
            fprintf(stderr, "%s\n", _("Error: input closed"));
            exit(1);
        }
        if (buf[0] == 'Y' || buf[0] == 'y') return 1;
        if (buf[0] == 'N' || buf[0] == 'n') return 0;
        printf("%s\n", _("Please answer Yes or No"));
    }
}

/**
 * @brief Main game loop
 * 
 * Implements a binary search algorithm to guess the user's number.
 * Uses Roman numerals if the -r flag was specified.
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return 0 on success
 */
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    
    argp.doc = _(doc_string);
    options[0].doc = _("Use Roman numerals for display");
    
    argp_parse(&argp, argc, argv, 0, 0, 0);
    
    if (use_roman) {
        printf(_("Think of a number from %s to %s.\n"), 
               to_roman(MIN_NUMBER), to_roman(MAX_NUMBER));
    } else {
        printf(_("Think of a number from %d to %d.\n"), MIN_NUMBER, MAX_NUMBER);
    }
    
    int low = MIN_NUMBER, high = MAX_NUMBER;
    while (low < high) {
        int mid = (low + high) / 2;
        char question[128];
        
        if (use_roman) {
            snprintf(question, sizeof(question), 
                    _("Is your number greater than %s? (Yes/No): "), 
                    to_roman(mid));
        } else {
            snprintf(question, sizeof(question), 
                    _("Is your number greater than %d? (Yes/No): "), 
                    mid);
        }
        
        if (ask(question))
            low = mid + 1;
        else
            high = mid;
    }
    
    if (use_roman) {
        printf(_("Your number is %s!\n"), to_roman(low));
    } else {
        printf(_("Your number is %d!\n"), low);
    }
    
    return 0;
}
