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
