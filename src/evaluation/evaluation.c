#include "evaluation.h"

expression evaluate_expression(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case INT:
    case DOUBLE:
    case STRING:
      return the_expression;
    case VAR:
      fprintf(stderr, "[EVALUATE_EXPRESSION]: variables not yet supported");
      exit(1);
    case UN_MINUS:
      result = expression_unary_minus(evaluate_expression(the_expression.child[0]));
      return result;
    case BIN_PLUS:
      result = expression_addition(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
    case BIN_MINUS:
      result = expression_subtraction(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
    case BIN_MULT:
      result = expression_multiplication(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
    case BIN_DIVIDE:
      result = expression_division(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
    case BIN_MOD:
      result = expression_modulus(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
    case BIN_POW:
      result = expression_pow(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
      return result;
  }
  return result;
}

expression expression_unary_minus(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case INT:
      result.value.int_value = int_unary_minus(the_expression);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_unary_minus(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_UNARY_MINUS]: operation unary minus not "
          "supported for type: `%s`\n",
          expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_addition(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_ADDITION]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_addition(left, right);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_addition(left, right);
      result.type = DOUBLE;
      return result;
    case STRING:
      result.value.string_value = string_addition(left, right);
      result.type = STRING;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_ADDITION]: operation addition not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_subtraction(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_SUBTRACTION]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_subtraction(left, right);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_subtraction(left, right);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_SUBTRACTION]: operation subtraction not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_multiplication(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_MULTIPLICATION]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_multiplication(left, right);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_multiplication(left, right);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_MULTIPLICATION]: operation multiplication not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_division(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_DIVISION]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_division(left, right);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_division(left, right);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_DIVISION]: operation division not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_modulus(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_MODULUS]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_modulus(left, right);
      result.type = INT;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_MODULUS]: operation modulus not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_pow(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_POW]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  switch(left.type) {
    case INT:
      result.value.int_value = int_pow(left, right);
      result.type = INT;
      return result;
    case DOUBLE:
      result.value.double_value = double_pow(left, right);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_POW]: operation power not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}
