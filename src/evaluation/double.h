#ifndef DOUBLE_H
#define DOUBLE_H

#include <math.h>
#include "../parsing/parsing.h"

double double_unary_minus(expression the_expression);
double double_addition(expression left, expression right);
double double_subtraction(expression left, expression right);
double double_multiplication(expression left, expression right);
double double_division(expression left, expression right);
double double_pow(expression left, expression right);
bool double_eq(expression left, expression right);
bool double_neq(expression left, expression right);
bool double_geq(expression left, expression right);
bool double_gt(expression left, expression right);
bool double_leq(expression left, expression right);
bool double_lt(expression left, expression right);
double double_sin(expression the_expression);
double double_cos(expression the_expression);
double double_tan(expression the_expression);
double double_arcsin(expression the_expression);
double double_arccos(expression the_expression);
double double_arctan(expression the_expression);
double double_log(expression the_expression);
double double_ln(expression the_expression);

#endif
