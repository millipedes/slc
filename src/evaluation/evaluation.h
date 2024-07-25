#ifndef EVALUATION_H
#define EVALUATION_H

#include "bool.h"
#include "double.h"
#include "evaluation_types.h"
#include "integer.h"
#include "string.h"
#include "symbol_table.h"

slc_value evaluate_expression(expression the_expression, symbol_table * st);
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
expression expression_sin(expression the_expression);
expression expression_cos(expression the_expression);
expression expression_tan(expression the_expression);
expression expression_arcsin(expression the_expression);
expression expression_arccos(expression the_expression);
expression expression_arctan(expression the_expression);
expression expression_log(expression the_expression);
expression expression_ln(expression the_expression);

slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st);

slc_value evaluate_lline_union(slc_primitive value, slc_primitive_type type);
void evaluate_lline(parsed_lline the_lline, symbol_table * st);

#endif
