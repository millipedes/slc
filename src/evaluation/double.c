#include "double.h"

double double_unary_minus(expression the_expression) {
  return -the_expression.value.double_value;
}

double double_addition(expression left, expression right) {
  return left.value.double_value + right.value.double_value;
}

double double_subtraction(expression left, expression right) {
  return left.value.double_value - right.value.double_value;
}

double double_multiplication(expression left, expression right) {
  return left.value.double_value * right.value.double_value;
}

double double_division(expression left, expression right) {
  return left.value.double_value / right.value.double_value;
}

double double_pow(expression left, expression right) {
  return pow(left.value.double_value, right.value.double_value);
}

bool double_eq(expression left, expression right) {
  return left.value.double_value == right.value.double_value;
}

bool double_neq(expression left, expression right) {
  return left.value.double_value != right.value.double_value;
}

bool double_geq(expression left, expression right) {
  return left.value.double_value >= right.value.double_value;
}

bool double_gt(expression left, expression right) {
  return left.value.double_value > right.value.double_value;
}

bool double_leq(expression left, expression right) {
  return left.value.double_value <= right.value.double_value;
}

bool double_lt(expression left, expression right) {
  return left.value.double_value < right.value.double_value;
}

double double_sin(expression the_expression) {
  return sin(the_expression.value.double_value);
}

double double_cos(expression the_expression) {
  return cos(the_expression.value.double_value);
}

double double_tan(expression the_expression) {
  return tan(the_expression.value.double_value);
}

double double_arcsin(expression the_expression) {
  return asin(the_expression.value.double_value);
}

double double_arccos(expression the_expression) {
  return acos(the_expression.value.double_value);
}

double double_arctan(expression the_expression) {
  return atan(the_expression.value.double_value);
}

double double_log(expression the_expression) {
  return log(the_expression.value.double_value) / log(2);
}

double double_ln(expression the_expression) {
  return log(the_expression.value.double_value);
}
