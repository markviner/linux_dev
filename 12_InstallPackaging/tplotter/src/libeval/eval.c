#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static const char *expr_ptr;
static double x_value;

static double parse_expr();
static double parse_term();
static double parse_factor();
static double parse_power();

static int parse_error;

static void skip_spaces() {
    while (*expr_ptr && isspace(*expr_ptr)) {
        expr_ptr++;
    }
}

static double parse_number()
{
    char *end;
    double val = strtod(expr_ptr, &end);

    if (end == expr_ptr) {
        parse_error = 1;
        return 0.0;
    }

    expr_ptr = end;
    return val;
}

static double parse_factor() {
    skip_spaces();
    
    if (*expr_ptr == '(') {
        expr_ptr++;
        double val = parse_expr();
        skip_spaces();
        if (*expr_ptr == ')') {
            expr_ptr++;
        }
        return val;
    }

    if (*expr_ptr == 'x') {
        expr_ptr++;
        return x_value;
    }

    if (strncmp(expr_ptr, "sin", 3) == 0) {
        expr_ptr += 3;
        return sin(parse_factor());
    }
    if (strncmp(expr_ptr, "cos", 3) == 0) {
        expr_ptr += 3;
        return cos(parse_factor());
    }
    if (strncmp(expr_ptr, "tan", 3) == 0) {
        expr_ptr += 3;
        return tan(parse_factor());
    }
    if (strncmp(expr_ptr, "sqrt", 4) == 0) {
        expr_ptr += 4;
        return sqrt(parse_factor());
    }
    if (strncmp(expr_ptr, "abs", 3) == 0) {
        expr_ptr += 3;
        return fabs(parse_factor());
    }
    if (strncmp(expr_ptr, "log2", 4) == 0) {
        expr_ptr += 4;
        return log2(parse_factor());
    }
    if (strncmp(expr_ptr, "log", 3) == 0) {
        expr_ptr += 3;
        return log(parse_factor());
    }
    if (strncmp(expr_ptr, "ln", 2) == 0) {
        expr_ptr += 2;
        return log(parse_factor());
    }
    if (strncmp(expr_ptr, "exp", 3) == 0) {
        expr_ptr += 3;
        return exp(parse_factor());
    }

    if (strncmp(expr_ptr, "pi", 2) == 0) {
        expr_ptr += 2;
        return M_PI;
    }

    if (*expr_ptr == 'e') {
        expr_ptr++;
        return M_E;
    }
    
    
    if (*expr_ptr == '-') {
        expr_ptr++;
        return -parse_factor();
    }
    if (*expr_ptr == '+') {
        expr_ptr++;
        return parse_factor();
    }

    if (isdigit(*expr_ptr) || *expr_ptr == '.') {
        return parse_number();
    }

    parse_error = 1;
    return 0.0;
}

static double parse_power() {
    double val = parse_factor();
    skip_spaces();
    
    if (*expr_ptr == '^') {
        expr_ptr++;
        double exp = parse_power();
        return pow(val, exp);
    }
    
    return val;
}

static double parse_term() {
    double val = parse_power();
    skip_spaces();
    
    while (*expr_ptr == '*' || *expr_ptr == '/') {
        char op = *expr_ptr;
        expr_ptr++;
        double right = parse_power();
        if (op == '*') {
            val *= right;
        } else {
            if (right != 0.0) {
                val /= right;
            }
        }
        skip_spaces();
    }
    
    return val;
}

static double parse_expr() {
    double val = parse_term();
    skip_spaces();
    
    while (*expr_ptr == '+' || *expr_ptr == '-') {
        char op = *expr_ptr;
        expr_ptr++;
        double right = parse_term();
        if (op == '+') {
            val += right;
        } else {
            val -= right;
        }
        skip_spaces();
    }
    
    return val;
}

int eval_expression(const char *expr, double x, double *result)
{
    if (!expr || !result) {
        return -1;
    }

    expr_ptr = expr;
    x_value = x;
    parse_error = 0;

    *result = parse_expr();
    skip_spaces();

    if (*expr_ptr != '\0') {
        parse_error = 1;
    }

    return parse_error ? -1 : 0;
}

int eval_is_valid(const char *expr)
{
    double dummy;
    return eval_expression(expr, 0.0, &dummy) == 0;
}
