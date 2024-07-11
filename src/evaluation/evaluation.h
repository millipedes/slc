#ifndef EVALUATION_H
#define EVALUATION_H

#include "bool.h"
#include "double.h"
#include "integer.h"
#include "string.h"

#include "../shape/rectangle.h"

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

typedef struct SHAPE_T {
  union {
    line the_line;
    rectangle rect;
  } value;
  shape_type type;
} shape;

shape evaluate_shape(shape_parsed the_shape);

#endif
