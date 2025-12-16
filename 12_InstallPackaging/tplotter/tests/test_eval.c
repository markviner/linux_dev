#include <stdio.h>
#include <math.h>
#include <string.h>
#include "eval.h"

#define EPSILON 1e-6
#define TEST(name) printf("Testing %s...", name); fflush(stdout);
#define PASS() printf(" PASS\n")
#define FAIL(msg) do { printf(" FAIL: %s\n", msg); return 1; } while(0)

int test_basic_arithmetic(void) {
    TEST("basic arithmetic");
    double result;
    
    if (eval_expression("2+3", 0, &result) != 0 || fabs(result - 5.0) > EPSILON)
        FAIL("2+3 should be 5");
    
    if (eval_expression("10-3", 0, &result) != 0 || fabs(result - 7.0) > EPSILON)
        FAIL("10-3 should be 7");
    
    if (eval_expression("4*5", 0, &result) != 0 || fabs(result - 20.0) > EPSILON)
        FAIL("4*5 should be 20");
    
    if (eval_expression("20/4", 0, &result) != 0 || fabs(result - 5.0) > EPSILON)
        FAIL("20/4 should be 5");
    
    PASS();
    return 0;
}

int test_variable_x(void) {
    TEST("variable x");
    double result;
    
    if (eval_expression("x", 5.0, &result) != 0 || fabs(result - 5.0) > EPSILON)
        FAIL("x with x=5 should be 5");
    
    if (eval_expression("x+10", 5.0, &result) != 0 || fabs(result - 15.0) > EPSILON)
        FAIL("x+10 with x=5 should be 15");
    
    if (eval_expression("2*x", 3.0, &result) != 0 || fabs(result - 6.0) > EPSILON)
        FAIL("2*x with x=3 should be 6");
    
    PASS();
    return 0;
}

int test_power(void) {
    TEST("power operator");
    double result;
    
    if (eval_expression("2^3", 0, &result) != 0 || fabs(result - 8.0) > EPSILON)
        FAIL("2^3 should be 8");
    
    if (eval_expression("x^2", 5.0, &result) != 0 || fabs(result - 25.0) > EPSILON)
        FAIL("x^2 with x=5 should be 25");
    
    PASS();
    return 0;
}

int test_trig_functions(void) {
    TEST("trigonometric functions");
    double result;
    
    if (eval_expression("sin(0)", 0, &result) != 0 || fabs(result) > EPSILON)
        FAIL("sin(0) should be 0");
    
    if (eval_expression("cos(0)", 0, &result) != 0 || fabs(result - 1.0) > EPSILON)
        FAIL("cos(0) should be 1");
    
    if (eval_expression("sin(pi/2)", 0, &result) != 0 || fabs(result - 1.0) > EPSILON)
        FAIL("sin(pi/2) should be 1");
    
    PASS();
    return 0;
}

int test_math_functions(void) {
    TEST("math functions");
    double result;
    
    if (eval_expression("sqrt(4)", 0, &result) != 0 || fabs(result - 2.0) > EPSILON)
        FAIL("sqrt(4) should be 2");
    
    if (eval_expression("sqrt(9)", 0, &result) != 0 || fabs(result - 3.0) > EPSILON)
        FAIL("sqrt(9) should be 3");
    
    if (eval_expression("exp(0)", 0, &result) != 0 || fabs(result - 1.0) > EPSILON)
        FAIL("exp(0) should be 1");
    
    if (eval_expression("ln(e)", 0, &result) != 0 || fabs(result - 1.0) > EPSILON)
        FAIL("ln(e) should be 1");
    
    PASS();
    return 0;
}

int test_complex_expressions(void) {
    TEST("complex expressions");
    double result;
    
    if (eval_expression("sin(x)^2 + cos(x)^2", 1.5, &result) != 0 || fabs(result - 1.0) > EPSILON)
        FAIL("sin^2 + cos^2 should be 1");
    
    if (eval_expression("2*sin(x)*cos(x)", M_PI/4, &result) != 0 || fabs(result - 1.0) > 0.001)
        FAIL("2*sin*cos at pi/4 should be ~1");
    
    PASS();
    return 0;
}

int test_parentheses(void) {
    TEST("parentheses");
    double result;
    
    if (eval_expression("(2+3)*4", 0, &result) != 0 || fabs(result - 20.0) > EPSILON)
        FAIL("(2+3)*4 should be 20");
    
    if (eval_expression("2+(3*4)", 0, &result) != 0 || fabs(result - 14.0) > EPSILON)
        FAIL("2+(3*4) should be 14");
    
    PASS();
    return 0;
}

int test_constants(void) {
    TEST("constants");
    double result;
    
    if (eval_expression("pi", 0, &result) != 0 || fabs(result - M_PI) > EPSILON)
        FAIL("pi should be M_PI");
    
    if (eval_expression("e", 0, &result) != 0 || fabs(result - M_E) > EPSILON)
        FAIL("e should be M_E");
    
    if (eval_expression("2*pi", 0, &result) != 0 || fabs(result - 2*M_PI) > EPSILON)
        FAIL("2*pi should be 2*M_PI");
    
    PASS();
    return 0;
}

int test_validation(void) {
    TEST("expression validation");
    
    if (!eval_is_valid("sin(x)"))
        FAIL("sin(x) should be valid");
    
    if (!eval_is_valid("x^2 + 2*x + 1"))
        FAIL("x^2 + 2*x + 1 should be valid");
    
    PASS();
    return 0;
}

int main(void) {
    int failed = 0;
    
    printf("Running unit tests for libeval\n");
    printf("================================\n\n");
    
    failed += test_basic_arithmetic();
    failed += test_variable_x();
    failed += test_power();
    failed += test_trig_functions();
    failed += test_math_functions();
    failed += test_complex_expressions();
    failed += test_parentheses();
    failed += test_constants();
    failed += test_validation();
    
    printf("\n================================\n");
    if (failed == 0) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("%d test(s) failed!\n", failed);
        return 1;
    }
}
