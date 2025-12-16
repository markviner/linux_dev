/**
 * @file eval.h
 * @brief Simple mathematical expression evaluator
 * @author Dmitry
 * @version 1.0
 */

#ifndef EVAL_H
#define EVAL_H

/**
 * @brief Evaluate mathematical expression at given x value
 * 
 * Supports basic operations: +, -, *, /, ^
 * Supports functions: sin, cos, tan, log, sqrt, abs
 * Variable 'x' is substituted with the provided value
 * 
 * @param expr Mathematical expression string (e.g., "sin(x) + 2*x")
 * @param x Value to substitute for variable x
 * @param result Pointer to store the result
 * @return 0 on success, -1 on error
 */
int eval_expression(const char *expr, double x, double *result);

int eval_is_valid(const char *expr);

/**
 * @brief Check if expression is valid
 * 
 * @param expr Expression to validate
 * @return 1 if valid, 0 if invalid
 */
int eval_validate(const char *expr);

#endif /* EVAL_H */
