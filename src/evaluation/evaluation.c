#include "evaluation.h"

slc_value evaluate_expression(expression the_expression, symbol_table * st) {
  slc_value result = {0};
  result.type = EXPR;
  switch(the_expression.type) {
    case INT:
    case DOUBLE:
    case STRING:
    case BOOL:
      result.value.the_expr = the_expression;
      break;
    case VAR:
      return find_symbol(*st, the_expression);
    case UN_MINUS:
      result.value.the_expr = expression_unary_minus(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case SIN:
      result.value.the_expr = expression_sin(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case COS:
      result.value.the_expr = expression_cos(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case TAN:
      result.value.the_expr = expression_tan(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case ARCSIN:
      result.value.the_expr = expression_arcsin(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case ARCCOS:
      result.value.the_expr = expression_arccos(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case ARCTAN:
      result.value.the_expr = expression_arctan(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case LOG:
      result.value.the_expr = expression_log(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case LN:
      result.value.the_expr = expression_ln(evaluate_expression(the_expression.child[0], st).value.the_expr);
      break;
    case BIN_PLUS:
      result.value.the_expr = expression_addition(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_MINUS:
      result.value.the_expr = expression_subtraction(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_MULT:
      result.value.the_expr = expression_multiplication(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_DIVIDE:
      result.value.the_expr = expression_division(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_MOD:
      result.value.the_expr = expression_modulus(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_POW:
      result.value.the_expr = expression_pow(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_EQ:
      result.value.the_expr = expression_eq(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_NEQ:
      result.value.the_expr = expression_neq(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_GEQ:
      result.value.the_expr = expression_geq(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_GT:
      result.value.the_expr = expression_gt(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_LEQ:
      result.value.the_expr = expression_leq(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
    case BIN_LT:
      result.value.the_expr = expression_lt(
          evaluate_expression(the_expression.child[0], st).value.the_expr,
          evaluate_expression(the_expression.child[1], st).value.the_expr);
      break;
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
      fprintf(stderr, "[EXPRESSION_ADDITION]: type do not match: `%s`, `%s`\n",
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
    default:
      fprintf(stderr, "[EXPRESSION_ADDITION]: operation addition not supported "
          "for type: `%s`\n", expression_type_to_string(left.type));
      exit(1);
  }
}

expression expression_subtraction(expression left, expression right) {
  if(left.type != right.type) {
      fprintf(stderr, "[EXPRESSION_SUBTRACTION]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_MULTIPLICATION]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_DIVISION]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_MODULUS]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_POW]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_EQ]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_NEQ]: type do not match: `%s`, `%s`\n",
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
    case STRING:
      result.value.bool_value = string_neq(left, right);
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
      fprintf(stderr, "[EXPRESSION_GEQ]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_GT]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_LEQ]: type do not match: `%s`, `%s`\n",
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
      fprintf(stderr, "[EXPRESSION_LT]: type do not match: `%s`, `%s`\n",
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

expression expression_sin(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_sin(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_SIN]: operation sin not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_cos(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_cos(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_COS]: operation cos not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_tan(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_tan(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_TAN]: operation tan not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_arcsin(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_arcsin(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_ARCSIN]: operation arcsin not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_arccos(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_arccos(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_ARCCOS]: operation arccos not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_arctan(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_arctan(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_ARCTAN]: operation arctan not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_log(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_log(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_LOG]: operation log not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

expression expression_ln(expression the_expression) {
  expression result = {0};
  switch(the_expression.type) {
    case DOUBLE:
      result.value.double_value = double_ln(the_expression);
      result.type = DOUBLE;
      return result;
    default:
      fprintf(stderr, "[EXPRESSION_UNARY_MINUS]: operation ln not supported "
          "for type: `%s`\n", expression_type_to_string(the_expression.type));
      exit(1);
  }
}

slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st) {
  slc_value result = {0};
  result.type = SHAPE;
  switch(the_shape.type) {
    case ELLIPSE:
      result.value.the_shape.type = ELLIPSE;
      result.value.the_shape.value.the_ellipse = evaluate_ellipse(the_shape, st);
      break;
    case LINE:
      result.value.the_shape.type = LINE;
      result.value.the_shape.value.the_line = evaluate_line(the_shape, st);
      break;
    case RECTANGLE:
      result.value.the_shape.type = RECTANGLE;
      result.value.the_shape.value.the_rectangle = evaluate_rectangle(the_shape, st);
      break;
    case CANVAS:
      result.value.the_shape.type = CANVAS;
      result.value.the_shape.value.the_canvas = evaluate_canvas(the_shape, st);
      break;
  }
  return result;
}

slc_value evaluate_array(parsed_array the_array, symbol_table * st) {
  slc_value result = {0};
  result.value.the_array = (array *)calloc(1, sizeof(struct ARRAY_T));
  result.type = ARRAY;
  for(uint32_t i = 0; i < the_array.qty_values; i++) {
    switch(the_array.value_type[i]) {
      case EXPR:
        result.value.the_array[0]
          = add_to_array(result.value.the_array[0], EXPR, &the_array.value[i].the_expr, st);
        break;
      case SHAPE:
        result.value.the_array[0]
          = add_to_array(result.value.the_array[0], SHAPE, &the_array.value[i].the_shape, st);
        break;
      case ARRAY:
        result.value.the_array[0]
          = add_to_array(result.value.the_array[0], ARRAY, the_array.value[i].the_array, st);
        break;
    }
  }
  return result;
}

slc_value evaluate_slc_primitive(slc_primitive value, slc_primitive_type type, symbol_table * st) {
  switch(type) {
    case EXPR:
      return evaluate_expression(value.the_expr, st);
    case SHAPE:
      return evaluate_shape(value.the_shape, st);
    case ARRAY:
      return evaluate_array(value.the_array[0], st);
    default:
      fprintf(stderr, "[EVALUATE_SLC_PRIMITIVE]: Unknown slc_primitive_type\n");
      exit(1);
  }
}

void evaluate_lline(parsed_lline the_lline, symbol_table * st) {
  // if
  expression truth = {0};
  // for
  expression init = {0};
  expression top_ex = {0};
  expression bottom_ex = {0};
  switch(the_lline.type) {
    case ASSIGNMENT:
      *st = add_slc_value_to_table(*st,
          the_lline.value[0].the_expr.value.string_value,
          evaluate_slc_primitive(the_lline.value[1], the_lline.value_type[1], st));
      break;
    case DRAW_STMT:
      draw_shape(the_lline, st);
      break;
    case IF_STMT:
      truth = evaluate_expression(the_lline.value[0].the_expr, st).value.the_expr;
      if(truth.type == BOOL) {
        if(truth.value.bool_value) {
          for(uint32_t i = 0; i < the_lline.qty_children; i++) {
            evaluate_lline(the_lline.child[i], st);
          }
        }
      } else {
        fprintf(stderr, "[EVALUATE_LLINE]: if statements only accepts boolean "
            "values\n");
        exit(1);
      }
      break;
    case FOR_LOOP:
      init = the_lline.value[0].the_expr;
      top_ex = the_lline.qty_values == 2
        ? evaluate_expression(the_lline.value[1].the_expr, st).value.the_expr
        : evaluate_expression(the_lline.value[2].the_expr, st).value.the_expr;
      bottom_ex = the_lline.qty_values == 2
        ? (expression){0}
        : evaluate_expression(the_lline.value[1].the_expr, st).value.the_expr;
      if(top_ex.type == INT) {
        for(int i = bottom_ex.value.int_value; i < top_ex.value.int_value; i++) {
          *st = add_slc_value_to_table(*st, init.value.string_value,
              (slc_value){(expression){{.int_value = i}, NULL, 0, INT}, EXPR});
          for(uint32_t j = 0; j < the_lline.qty_children; j++) {
            evaluate_lline(the_lline.child[j], st);
          }
        }
      } else {
        fprintf(stderr, "[EVALUATE_LLINE]: for loops only accepts integer "
            "values\n");
        exit(1);
      }
      break;
  }
}

expression opaque_eval_expr(expression * value, symbol_table * st) {
  return evaluate_expression(*value, st).value.the_expr;
}
