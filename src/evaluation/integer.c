#include "integer.h"

int int_unary_minus(expression the_expression) {
  return -the_expression.value.int_value;
}

int int_addition(expression left, expression right) {
  return left.value.int_value + right.value.int_value;
}

int int_subtraction(expression left, expression right) {
  return left.value.int_value - right.value.int_value;
}

int int_multiplication(expression left, expression right) {
  return left.value.int_value * right.value.int_value;
}

int int_division(expression left, expression right) {
  return left.value.int_value / right.value.int_value;
}

int int_modulus(expression left, expression right) {
  return left.value.int_value % right.value.int_value;
}

int int_pow(expression left, expression right) {
  return pow(left.value.int_value, right.value.int_value);
}
