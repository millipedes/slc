#ifndef EVALUATION_H
#define EVALUATION_H

#include "bool.h"
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
expression expression_pow(expression left, expression right);
expression expression_eq(expression left, expression right);
expression expression_neq(expression left, expression right);
expression expression_geq(expression left, expression right);
expression expression_gt(expression left, expression right);
expression expression_leq(expression left, expression right);
expression expression_lt(expression left, expression right);

#endif
