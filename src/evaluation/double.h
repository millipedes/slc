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

#endif
