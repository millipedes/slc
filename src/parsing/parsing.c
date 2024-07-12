#include "parsing.h"

const char * expression_type_to_string(expression_type type) {
  switch(type) {
    case INT:        return "Int";
    case DOUBLE:     return "Double";
    case VAR:        return "Var";
    case STRING:     return "String";
    case BOOL:       return "Bool";
    case UN_MINUS:   return "Un Minus";
    case BIN_PLUS:   return "Bin Plus";
    case BIN_MINUS:  return "Bin Minus";
    case BIN_MULT:   return "Bin Mult";
    case BIN_DIVIDE: return "Bin Divide";
    case BIN_MOD:    return "Bin Mod";
    case BIN_EQ:     return "Bin Eq";
    case BIN_NEQ:    return "Bin Neq";
    case BIN_GEQ:    return "Bin Geq";
    case BIN_GT:     return "Bin Gt";
    case BIN_LEQ:    return "Bin Leq";
    case BIN_LT:     return "Bin Lt";
  }
  return NULL;
}

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
    expression * parent = (expression *)data;
    expression child = {0};
    factor = parse_factor(parse_ws(factor), &child);
    parent->type = UN_MINUS;
    parent->qty_children = 1;
    parent->child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
    parent->child[0] = child;
    return factor;
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

const char * parse_boolean_expression(const char * input, void * data) {
  const char * expr = parse_expression(parse_ws(input), data);
  const char * maybe_boolean_expr;
  if(expr) {
    if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"==")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_EQ);
      return parse_word(parse_ws(expr), (void *)"==");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"!=")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_NEQ);
      return parse_word(parse_ws(expr), (void *)"!=");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)">=")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_GEQ);
      return parse_word(parse_ws(expr), (void *)">=");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)">")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_GT);
      return parse_word(parse_ws(expr), (void *)">");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"<=")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_LEQ);
      return parse_word(parse_ws(expr), (void *)"<=");
    } else if((maybe_boolean_expr = parse_word(parse_ws(expr), (void *)"<")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_boolean_expr, BIN_LT);
      return parse_word(parse_ws(expr), (void *)"<");
    } else return expr;
  } return NULL;
}

bool is_double_delineator(char c) {
  return c == '.' || c == 'e' || c == 'E';
}

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f';
}

void debug_expression(expression the_expression, int indent) {
  for(int i = 0; i < 2 * indent; i++) printf(" ");
  switch(the_expression.type) {
    case INT:        printf("%d\n", the_expression.value.int_value);    break;
    case DOUBLE:     printf("%f\n", the_expression.value.double_value); break;
    case VAR:        printf("%s\n", the_expression.value.string_value); break;
    case STRING:     printf("%s\n", the_expression.value.string_value); break;
    case BOOL:       printf("%s\n", the_expression.value.bool_value ? "true" : "false"); break;
    case UN_MINUS:   printf("-\n");                                     break;
    case BIN_PLUS:   printf("+\n");                                     break;
    case BIN_MINUS:  printf("-\n");                                     break;
    case BIN_MULT:   printf("*\n");                                     break;
    case BIN_DIVIDE: printf("/\n");                                     break;
    case BIN_MOD:    printf("%\n");                                     break;
    case BIN_POW:    printf("^\n");                                     break;
    case BIN_EQ:     printf("==\n");                                    break;
    case BIN_NEQ:    printf("!=\n");                                    break;
    case BIN_GEQ:    printf(">=\n");                                    break;
    case BIN_GT:     printf(">\n");                                     break;
    case BIN_LEQ:    printf("<=\n");                                    break;
    case BIN_LT:     printf("<\n");                                     break;
  }
  for(uint32_t i = 0; i < the_expression.qty_children; i++) {
    debug_expression(the_expression.child[i], indent + 1);
  }
}

void validate_type(expression the_expression, expression_type type, const char * err) {
  if(the_expression.type != type) {
    fprintf(stderr, err);
    exit(1);
  }
}

void free_expression(expression the_expression) {
  if((the_expression.type == STRING || the_expression.type == VAR)
      && the_expression.value.string_value) {
    free(the_expression.value.string_value);
  }
  for(uint32_t i = 0; i < the_expression.qty_children; i++) {
    free_expression(the_expression.child[i]);
  }
  if(the_expression.child) {
    free(the_expression.child);
  }
}

const char * parse_shape(const char * input, void * data) {
  expression name = {0};
  expression tmp_value = {0};
  const char * remainder = parse_expression(parse_ws(input), &name);
  const char * delimiter;
  parsed_shape * the_shape = (parsed_shape *)data;

  validate_type(name, VAR, "[PARSE_SHAPE]: attempted to parse shape\n");
  if(!strncmp(name.value.string_value, "line", sizeof("line") - 1)) {
    the_shape->type = LINE;
  } else if(!strncmp(name.value.string_value, "rectangle", sizeof("rectangle") - 1)) {
    the_shape->type = RECTANGLE;
  } else if(!strncmp(name.value.string_value, "ellipse", sizeof("ellipse") - 1)) {
    the_shape->type = ELLIPSE;
  } else {
    fprintf(stderr, "[PARSE_SHAPE]: unrecognized shape `%s`\n", name.value.string_value);
    exit(1);
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

parsed_shape * add_expression(parsed_shape * the_shape, expression the_expression) {
  the_shape->qty_values++;
  if(the_shape->values) {
    the_shape->values = (expression *)realloc(the_shape->values,
        the_shape->qty_values * sizeof(struct EXPRESSION_T));
  } else {
    the_shape->values = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  }
  the_shape->values[the_shape->qty_values - 1] = the_expression;
  return the_shape;
}

void free_parsed_shape(parsed_shape the_shape) {
  for(uint32_t i = 0; i < the_shape.qty_values; i++) {
    free_expression(the_shape.values[i]);
  }
  if(the_shape.values) {
    free(the_shape.values);
  }
}

const char * parse_assignment(const char * input, void * data) {
  parsed_lline * the_lline = (parsed_lline *)data;
  expression maybe_variable = {0};
  const char * remainder = parse_variable_name(parse_ws(input), &maybe_variable);
  if(remainder) {
    if((remainder = parse_character(parse_ws(remainder), (void *)"=")) != NULL) {
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
      }
      return NULL;
    } else return NULL;
  } else return NULL;
}

parsed_lline add_to_lline(parsed_lline the_lline, slc_value_type type, void * addition) {
  the_lline.qty_values++;
  if(the_lline.value) {
    the_lline.value = (lline_union *)realloc(the_lline.value,
        the_lline.qty_values * sizeof(lline_union));
    the_lline.value_type = (slc_value_type *)realloc(the_lline.value_type,
        the_lline.qty_values * sizeof(slc_value_type));
  } else {
    the_lline.value = (lline_union *)calloc(1, sizeof(lline_union));
    the_lline.value_type = (slc_value_type *)calloc(1, sizeof(slc_value_type));
  }
  the_lline.value_type[the_lline.qty_values - 1] = type;
  switch(type) {
    case EXPR:
      the_lline.value[the_lline.qty_values - 1].the_expr = *(expression *)addition;
      break;
    case SHAPE:
      the_lline.value[the_lline.qty_values - 1].the_shape = *(parsed_shape *)addition;
      break;
  }
  return the_lline;
}

void free_parsed_lline(parsed_lline the_lline) {
  for(uint32_t i = 0; i < the_lline.qty_values; i++) {
    switch(the_lline.value_type[i]) {
      case EXPR:
        free_expression(the_lline.value[i].the_expr);
        break;
      case SHAPE:
        free_parsed_shape(the_lline.value[i].the_shape);
        break;
    }
  }
  if(the_lline.value)
    free(the_lline.value);
  if(the_lline.value_type)
    free(the_lline.value_type);
}
