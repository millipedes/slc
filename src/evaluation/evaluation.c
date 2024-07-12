#include "evaluation.h"

expression evaluate_expression(expression the_expression) {
  switch(the_expression.type) {
    case INT:
    case DOUBLE:
    case STRING:
    case BOOL:
      return the_expression;
    case VAR:
      fprintf(stderr, "[EVALUATE_EXPRESSION]: variables not yet supported\n");
      exit(1);
    case UN_MINUS:
      return expression_unary_minus(evaluate_expression(the_expression.child[0]));
    case BIN_PLUS:
      return expression_addition(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_MINUS:
      return expression_subtraction(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_MULT:
      return expression_multiplication(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_DIVIDE:
      return expression_division(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_MOD:
      return expression_modulus(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_POW:
      return expression_pow(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_EQ:
      return expression_eq(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_NEQ:
      return expression_neq(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_GEQ:
      return expression_geq(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_GT:
      return expression_gt(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_LEQ:
      return expression_leq(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
    case BIN_LT:
      return expression_lt(
          evaluate_expression(the_expression.child[0]),
          evaluate_expression(the_expression.child[1]));
  }
  return (expression){0};
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

expression expression_eq(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_EQ]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_eq(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_eq(left, right);
      return result;
    case STRING:
      result.value.bool_value = string_eq(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_eq(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_EQ]: operation equality not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_neq(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_NEQ]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_neq(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_neq(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_neq(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_NEQ]: operation inequality not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_geq(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_GEQ]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_geq(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_geq(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_geq(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_GEQ]: operation greater than or equal not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_gt(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_GT]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_gt(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_gt(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_gt(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_GT]: operation greater than not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_leq(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_LEQ]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_leq(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_leq(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_leq(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_LEQ]: operation less than or equal not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_lt(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_LT]: type do not match: `%s`, `%s`",
          expression_type_to_string(left.type),
          expression_type_to_string(right.type));
      exit(1);
  }
  expression result = {0};
  result.type = BOOL;
  switch(left.type) {
    case INT:
      result.value.bool_value = int_lt(left, right);
      return result;
    case DOUBLE:
      result.value.bool_value = double_lt(left, right);
      return result;
    case BOOL:
      result.value.bool_value = bool_lt(left, right);
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_LT]: operation less than not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

shape evaluate_shape(shape_parsed the_shape) {
  shape result = {0};
  result.type = the_shape.type;
  switch(the_shape.type) {
    case ELLIPSE:
      result.value.the_ellipse = evaluate_ellipse(the_shape);
      break;
    case LINE:
      result.value.the_line = evaluate_line(the_shape);
      break;
    case RECTANGLE:
      result.value.the_rectangle = evaluate_rectangle(the_shape);
      break;
  }
  return result;
}
