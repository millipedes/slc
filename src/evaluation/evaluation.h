#ifndef EVALUATION_H
#define EVALUATION_H

#include "double.h"
#include "integer.h"
#include "string.h"

expression evaluate_expression(expression the_expression);
expression expression_unary_minus(expression the_expression);
expression expression_addition(expression left, expression right);
expression expression_subtraction(expression left, expression right);
expression expression_multiplication(expression left, expression right);
expression expression_division(expression left, expression right);
expression expression_modulus(expression left, expression right);

#endif
