#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include "config.h"
#include "eval.h"

#define _(STRING) gettext(STRING)

#define WIDTH 80
#define HEIGHT 24
#define X_MIN -10.0
#define X_MAX 10.0
#define Y_MIN -10.0
#define Y_MAX 10.0

typedef struct {
    char symbol;
    double values[WIDTH];
} PlotData;

void print_usage(const char *progname) {
    printf(_("Usage: %s <expression1> [expression2] ...\n"), progname);
    printf(_("Example: %s \"sin(x)\" \"cos(x)\"\n"), progname);
    printf(_("\nSupported functions: sin, cos, tan, sqrt, abs, log, log2\n"));
    printf(_("Supported operations: +, -, *, /, ^\n"));
}

void draw_plot(PlotData *plots, int num_plots) {
    char canvas[HEIGHT][WIDTH];
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = ' ';
        }
    }
    
    int zero_y = (int)(HEIGHT * (-Y_MIN) / (Y_MAX - Y_MIN));
    int zero_x = (int)(WIDTH * (-X_MIN) / (X_MAX - X_MIN));
    
    for (int x = 0; x < WIDTH; x++) {
        if (zero_y >= 0 && zero_y < HEIGHT) {
            canvas[zero_y][x] = '-';
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        if (zero_x >= 0 && zero_x < WIDTH) {
            canvas[y][zero_x] = '|';
        }
    }
    if (zero_y >= 0 && zero_y < HEIGHT && zero_x >= 0 && zero_x < WIDTH) {
        canvas[zero_y][zero_x] = '+';
    }
    
    char symbols[] = "*#@%&";
    for (int p = 0; p < num_plots; p++) {
        char sym = (p < 5) ? symbols[p] : 'o';
        
        for (int x = 0; x < WIDTH; x++) {
            double y_val = plots[p].values[x];
            
            if (y_val >= Y_MIN && y_val <= Y_MAX) {
                int y_pos = HEIGHT - 1 - (int)(HEIGHT * (y_val - Y_MIN) / (Y_MAX - Y_MIN));
                
                if (y_pos >= 0 && y_pos < HEIGHT) {
                    canvas[y_pos][x] = sym;
                }
            }
        }
    }
    
    printf(_("\nPlot: X[%.1f, %.1f] Y[%.1f, %.1f]\n"), X_MIN, X_MAX, Y_MIN, Y_MAX);
    printf("┌");
    for (int i = 0; i < WIDTH; i++) printf("─");
    printf("┐\n");
    
    for (int y = 0; y < HEIGHT; y++) {
        printf("│");
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("│\n");
    }
    
    printf("└");
    for (int i = 0; i < WIDTH; i++) printf("─");
    printf("┘\n");
    
    printf(_("\nLegend:\n"));
    for (int p = 0; p < num_plots; p++) {
        char sym = (p < 5) ? symbols[p] : 'o';
        printf("  %c - %s %d\n", sym, _("Function"), p + 1);
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    int num_funcs = argc - 1;
    PlotData *plots = malloc(sizeof(PlotData) * num_funcs);
    
    if (!plots) {
        fprintf(stderr, _("Error: Memory allocation failed\n"));
        return 1;
    }
    
    printf(_("Plotting %d function(s)...\n"), num_funcs);
    
    for (int f = 0; f < num_funcs; f++) {
        const char *expr = argv[f + 1];
        
        if (!eval_is_valid(expr)) {
            fprintf(stderr, _("Error: Invalid expression '%s'\n"), expr);
            free(plots);
            return 1;
        }
        
        printf(_("Function %d: %s\n"), f + 1, expr);
        
        for (int i = 0; i < WIDTH; i++) {
            double x = X_MIN + (X_MAX - X_MIN) * i / (WIDTH - 1);
            double y;
            
            if (eval_expression(expr, x, &y) != 0) {
                fprintf(stderr, _("Error: Failed to evaluate expression at x=%.2f\n"), x);
                free(plots);
                return 1;
            }
            
            plots[f].values[i] = y;
        }
    }
    
    draw_plot(plots, num_funcs);
    
    free(plots);
    return 0;
}
