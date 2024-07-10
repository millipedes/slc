#ifndef INTEGER_H
#define INTEGER_H

#include <math.h>
#include "../parsing/parsing.h"

int int_unary_minus(expression the_expression);
int int_addition(expression left, expression right);
int int_subtraction(expression left, expression right);
int int_multiplication(expression left, expression right);
int int_division(expression left, expression right);
int int_modulus(expression left, expression right);
int int_pow(expression left, expression right);

#endif
