#include "parsing.h"

const char * parse_ws(const char * input) {
  if(input) {
    uint32_t inc = 0;
    while(is_whitespace(*(input + inc))) inc++;
    return input + inc;
  } else return NULL;
}

const char * or_p(const char * input, void * data, uint32_t num_args, ...) {
  va_list args;
  va_start(args, num_args);
  for(uint32_t i = 0; i < num_args; i++) {
    const char * remainder = va_arg(args,
        const char * (*)(const char *, void *))(input, data);
    if(remainder != NULL) {
      va_end(args);
      return remainder;
    }
  }
  va_end(args);
  return NULL;
}

const char * parse_variable_name(const char * input, void * data) {
  expression * the_expression = (expression *)data;
  uint32_t inc = 0;
  while(isalpha(*(input + inc)) || *(input + inc) == '_') inc++;
  if(inc > 0) {
    the_expression->value.string_value = (char *)calloc(inc + 1, sizeof(char));
    strncpy(the_expression->value.string_value, input, inc);
    the_expression->value.string_value[inc] = '\0';
    the_expression->type = VAR;
    return input + inc;
  } else return NULL;
}

const char * parse_number(const char * input, void * data) {
  expression * the_expression = (expression *)data;
  uint32_t inc = 0;
  bool is_double = false;

  // decimal
  while(isdigit(*(input + inc))) inc++;

  if(*(input + inc) == '.') {
    is_double = true;
    inc++;
  } else if((*(input + inc) == 'e' || *(input + inc) == 'E')
      && (*(input + inc + 1) == '-' || isdigit(*input + inc + 1))) {
    is_double = true;
    inc++;
    if(*(input + inc) == '-') inc++;
  }

  // fractional
  while(isdigit(*(input + inc))) inc++;

  if(is_double && inc > 0) {
    the_expression->value.double_value = strtod(input, NULL);
    the_expression->type = DOUBLE;
    return input + inc;
  } else if(inc > 0) {
    the_expression->value.int_value = strtol(input, NULL, 10);
    the_expression->type = INT;
    return input + inc;
  } else return NULL;
}

const char * parse_string(const char * input, void * data) {
  expression * the_expression = (expression *)data;
  uint32_t inc = 1;
  if(input[0] != '\"') {
    return NULL;
  }
  while(*(input + inc) != '\"') {
    if(*(input + inc) == '\0') return NULL;
    inc++;
  }
  inc++;
  the_expression->value.string_value = (char *)calloc(inc + 1, sizeof(char));
  strncpy(the_expression->value.string_value, input, inc);
  the_expression->value.string_value[inc] = '\0';
  the_expression->type = STRING;
  return input + inc;
}

const char * parse_character(const char * input, void * data) {
  if(input) {
    if(input[0] == *(char *)data) {
      return input + 1;
    } else return NULL;
  } else return NULL;
}

const char * parse_word(const char * input, void * data) {
  if(input) {
    size_t len = strnlen((char *)data, MAX_STR);
    if(!strncmp(input, (char *)data, len)) {
      return input + len;
    } else return NULL;
  } else return NULL;
}

const char * parse_bool(const char * input, void * data) {
  const char * true_str = "true";
  const size_t true_len = 4;
  const char * false_str = "false";
  const size_t false_len = 5;
  expression * the_expression = (expression *)data;
  if(input) {
    if(!strncmp(input, true_str, true_len)) {
      the_expression->value.bool_value = true;
      the_expression->type = BOOL;
      return input + true_len;
    } else if(!strncmp(input, false_str, false_len)) {
      the_expression->value.bool_value = false;
      the_expression->type = BOOL;
      return input + false_len;
    } else return NULL;
  } else return NULL;
}

const char * parse_factor(const char * input, void * data) {
  const char * factor;
  if((factor = parse_character(parse_ws(input), (void *)"-")) != NULL) {
    ADJUST_UNARY_TREE(parse_factor, factor, UN_MINUS);
  } else if((factor = parse_word(parse_ws(input), (void *)"sin")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, SIN);
  } else if((factor = parse_word(parse_ws(input), (void *)"cos")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, COS);
  } else if((factor = parse_word(parse_ws(input), (void *)"tan")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, TAN);
  } else if((factor = parse_word(parse_ws(input), (void *)"arcsin")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, ARCSIN);
  } else if((factor = parse_word(parse_ws(input), (void *)"arccos")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, ARCCOS);
  } else if((factor = parse_word(parse_ws(input), (void *)"arctan")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, ARCTAN);
  } else if((factor = parse_word(parse_ws(input), (void *)"log")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, LOG);
  } else if((factor = parse_word(parse_ws(input), (void *)"ln")) != NULL) {
    ADJUST_UNARY_TREE(parse_expression, factor, LN);
  } else if((factor = parse_character(parse_ws(input), (void *)"(")) != NULL) {
    factor = parse_expression(parse_ws(factor), data);
    factor = parse_character(parse_ws(factor), (void *)")");
  } else {
    factor = or_p(parse_ws(input), data, 4, parse_number, parse_bool,
        parse_string, parse_variable_name);
  }
  const char * maybe_factor;
  if((maybe_factor = parse_character(parse_ws(factor), (void *)"^")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_factor, BIN_POW);
      return NULL;
  }
  const char * maybe_accessors;
  if((maybe_accessors = parse_character(parse_ws(factor), (void *)"[")) != NULL) {
    expression * parent = (expression *)data;
    expression accessor_parent = (expression){{.int_value = 0}, NULL, 0, ARRAY_ACCESSOR};
    expression accessor_value = {0};
    maybe_accessors = parse_expression(parse_ws(maybe_accessors), &accessor_value);
    accessor_parent = add_expression_child(accessor_parent, accessor_value);
    maybe_accessors = parse_character(parse_ws(maybe_accessors), (void *)"]");
    factor = maybe_accessors;
    accessor_value = (expression){0};
    while((maybe_accessors = parse_character(parse_ws(factor), (void *)"[")) != NULL) {
      maybe_accessors = parse_expression(parse_ws(maybe_accessors), &accessor_value);
      accessor_parent = add_expression_child(accessor_parent, accessor_value);
      maybe_accessors = parse_character(parse_ws(maybe_accessors), (void *)"]");
      factor = maybe_accessors;
      accessor_value = (expression){0};
    }
    *parent = add_expression_child(*parent, accessor_parent);
  }
  return factor;
}

const char * parse_term(const char * input, void * data) {
  const char * factor = parse_factor(parse_ws(input), data);
  const char * maybe_term;
  if(factor) {
    if((maybe_term = parse_character(parse_ws(factor), (void *)"*")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_MULT);
      return parse_character(parse_ws(factor), (void *)"*");
    } else if((maybe_term = parse_character(parse_ws(factor), (void *)"/")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_DIVIDE);
      return parse_character(parse_ws(factor), (void *)"/");
    } else if((maybe_term = parse_character(parse_ws(factor), (void *)"%")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_MOD);
      return parse_character(parse_ws(factor), (void *)"%");
    } else return factor;
  } return NULL;
}

const char * parse_expression(const char * input, void * data) {
  const char * term = parse_term(parse_ws(input), data);
  const char * maybe_expression;
  if(term) {
    if((maybe_expression = parse_character(parse_ws(term), (void *)"+")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_expression, BIN_PLUS);
      return parse_character(parse_ws(term), (void *)"+");
    } else if((maybe_expression = parse_character(parse_ws(term), (void *)"-")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_expression, BIN_MINUS);
      return parse_character(parse_ws(term), (void *)"-");
    } else return term;
  } return NULL;
}

const char * parse_relational_expression(const char * input, void * data) {
  const char * expr = parse_expression(parse_ws(input), data);
  const char * maybe_boolean_expr;
  if(expr) {
    if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)">=")) != NULL) {
      ADJUST_BINARY_TREE(parse_relational_expression, maybe_boolean_expr, BIN_GEQ);
      return parse_word(parse_ws(expr), (void *)">=");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)">")) != NULL) {
      ADJUST_BINARY_TREE(parse_relational_expression, maybe_boolean_expr, BIN_GT);
      return parse_word(parse_ws(expr), (void *)">");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"<=")) != NULL) {
      ADJUST_BINARY_TREE(parse_relational_expression, maybe_boolean_expr, BIN_LEQ);
      return parse_word(parse_ws(expr), (void *)"<=");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"<")) != NULL) {
      ADJUST_BINARY_TREE(parse_relational_expression, maybe_boolean_expr, BIN_LT);
      return parse_word(parse_ws(expr), (void *)"<");
    } else return expr;

  } return NULL;
}
const char * parse_precedence_1_expression(const char * input, void * data) {
  const char * expr = parse_relational_expression(parse_ws(input), data);
  const char * maybe_boolean_expr;
  if(expr) {
    if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"==")) != NULL) {
      ADJUST_BINARY_TREE(parse_precedence_1_expression, maybe_boolean_expr, BIN_EQ);
      return parse_word(parse_ws(expr), (void *)"==");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"!=")) != NULL) {
      ADJUST_BINARY_TREE(parse_precedence_1_expression, maybe_boolean_expr, BIN_NEQ);
      return parse_word(parse_ws(expr), (void *)"!=");
    } else return expr;
  } return NULL;
}

bool is_double_delineator(char c) {
  return c == '.' || c == 'e' || c == 'E';
}

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f';
}

const char * parse_shape(const char * input, void * data) {
  expression name = {0};
  expression tmp_value = {0};
  const char * remainder = parse_expression(parse_ws(input), &name);
  const char * delimiter;
  parsed_shape * the_shape = (parsed_shape *)data;

  if(name.type != VAR) {
    free_expression(name);
    return NULL;
  }
  if(!strncmp(name.value.string_value, "line", sizeof("line") - 1)) {
    the_shape->type = LINE;
  } else if(!strncmp(name.value.string_value, "rectangle", sizeof("rectangle") - 1)) {
    the_shape->type = RECTANGLE;
  } else if(!strncmp(name.value.string_value, "ellipse", sizeof("ellipse") - 1)) {
    the_shape->type = ELLIPSE;
  } else {
    free_expression(name);
    return NULL;
  }
  free_expression(name);

  if((remainder = parse_character(parse_ws(remainder), (void *)"(")) != NULL) {
    while((delimiter = parse_character(parse_ws(remainder), (void *)")")) == NULL) {
      remainder = parse_expression(parse_ws(remainder), &tmp_value);
      the_shape = add_expression(the_shape, tmp_value);
      tmp_value = (expression){0};
      remainder = parse_expression(parse_ws(remainder), &tmp_value);
      the_shape = add_expression(the_shape, tmp_value);
      if((delimiter = parse_character(parse_ws(remainder), (void *)",")) != NULL) {
        remainder = delimiter;
      }
      tmp_value = (expression){0};
    }
    return delimiter;
  } else return NULL;
}

const char * parse_array(const char * input, void * data) {
  const char * remainder = parse_character(parse_ws(input), (void *)"[");
  if(!remainder) return NULL;
  const char * delimiter;
  parsed_array * the_array = (parsed_array *)data;
  while((delimiter = parse_character(parse_ws(remainder), (void *)"]")) == NULL) {
      parsed_shape maybe_shape = {0};
      const char * maybe_shape_remainder;
      expression maybe_expression = {0};
      const char * maybe_expr_remainder;
      parsed_array maybe_array = {0};
      const char * maybe_array_remainder;
      if((maybe_array_remainder = parse_word(parse_ws(remainder), (void *)"[")) != NULL) {
        remainder = parse_array(parse_ws(remainder), &maybe_array);
        *the_array = add_to_parsed_array(*the_array, ARRAY, &maybe_array);
      } else if((maybe_shape_remainder
            = parse_shape(parse_ws(remainder), &maybe_shape)) != NULL) {
        *the_array = add_to_parsed_array(*the_array, SHAPE, &maybe_shape);
        remainder = maybe_shape_remainder;
      } else if((maybe_expr_remainder
            = parse_precedence_1_expression(parse_ws(remainder), &maybe_expression)) != NULL) {
        *the_array = add_to_parsed_array(*the_array, EXPR, &maybe_expression);
        remainder = maybe_expr_remainder;
      }

    if((delimiter = parse_character(parse_ws(remainder), (void *)",")) != NULL) {
      remainder = delimiter;
    }
  }
  return delimiter;
}

const char * parse_assignment(const char * input, void * data) {
  parsed_lline * the_lline = (parsed_lline *)data;
  expression maybe_variable = {0};
  const char * remainder = parse_variable_name(parse_ws(input), &maybe_variable);
  if(remainder) {
    if((remainder = parse_character(parse_ws(remainder), (void *)"=")) != NULL) {
      // Array?
      parsed_array maybe_array = {0};
      const char * maybe_array_remainder;
      if((maybe_array_remainder = parse_array(parse_ws(remainder), &maybe_array)) != NULL) {
        if((maybe_array_remainder
              = parse_character(parse_ws(maybe_array_remainder), (void *)";")) != NULL) {
          the_lline->type = ASSIGNMENT;
          *the_lline = add_to_lline(*the_lline, EXPR, &maybe_variable);
          *the_lline = add_to_lline(*the_lline, ARRAY, &maybe_array);
          return maybe_array_remainder;
        } else return NULL;
      }
      // Shape?
      parsed_shape maybe_shape = {0};
      const char * maybe_shape_remainder;
      if((maybe_shape_remainder = parse_shape(parse_ws(remainder), &maybe_shape)) != NULL) {
        if((maybe_shape_remainder
              = parse_character(parse_ws(maybe_shape_remainder), (void *)";")) != NULL) {
          the_lline->type = ASSIGNMENT;
          *the_lline = add_to_lline(*the_lline, EXPR, &maybe_variable);
          *the_lline = add_to_lline(*the_lline, SHAPE, &maybe_shape);
          return maybe_shape_remainder;
        } else return NULL;
      }
      // Expression?
      expression maybe_expression = {0};
      const char * maybe_expr_remainder;
      if((maybe_expr_remainder
            = parse_expression(parse_ws(remainder), &maybe_expression)) != NULL) {
        if((maybe_expr_remainder
              = parse_character(parse_ws(maybe_expr_remainder), (void *)";")) != NULL) {
          the_lline->type = ASSIGNMENT;
          *the_lline = add_to_lline(*the_lline, EXPR, &maybe_variable);
          *the_lline = add_to_lline(*the_lline, EXPR, &maybe_expression);
          return maybe_expr_remainder;
        } else return NULL;
      } else return NULL;
    } else return NULL;
  } else return NULL;
}
