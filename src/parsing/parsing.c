#include "parsing.h"

const char * expression_type_to_string(expression_type type) {
  switch(type) {
    case INT:        return "Int";
    case DOUBLE:     return "Double";
    case VAR:        return "Var";
    case STRING:     return "String";
    case UN_MINUS:   return "Un Minus";
    case BIN_PLUS:   return "Bin Plus";
    case BIN_MINUS:  return "Bin Minus";
    case BIN_MULT:   return "Bin Mult";
    case BIN_DIVIDE: return "Bin Divide";
    case BIN_MOD:    return "Bin Mod";
  }
  return NULL;
}

const char * parse_whitespace(const char * input) {
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
  uint64_t inc = 0;
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
  } else if(*(input + inc) == 'e' || *(input + inc) == 'E') {
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
  size_t len = strnlen((char *)data, MAX_STR);
  if(!strncmp(input, (char *)data, len))
    return input + len;
  return NULL;
}

const char * parse_factor(const char * input, void * data) {
  const char * remainder;
  if((remainder = parse_character(parse_whitespace(input), (void *)"-")) != NULL) {
    expression * parent = (expression *)data;
    expression child = {0};
    remainder = parse_factor(parse_whitespace(remainder), &child);
    parent->type = UN_MINUS;
    parent->qty_children = 1;
    parent->child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
    parent->child[0] = child;
    return remainder;
  } else if((remainder = parse_character(parse_whitespace(input), (void *)"(")) != NULL) {
    remainder = parse_expression(parse_whitespace(remainder), data);
    remainder = parse_character(parse_whitespace(remainder), (void *)")");
  } else {
    remainder = or_p(parse_whitespace(input), data, 3, parse_number, parse_string, parse_variable_name);
  }
  const char * maybe_factor;
  if((maybe_factor = parse_character(parse_whitespace(remainder), (void *)"^")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_factor, BIN_POW);
      return NULL;
  }
  return remainder;
}

const char * parse_term(const char * input, void * data) {
  const char * factor = parse_factor(parse_whitespace(input), data);
  const char * maybe_term;
  if(factor) {
    if((maybe_term = parse_character(parse_whitespace(factor), (void *)"*")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_MULT);
      return parse_character(parse_whitespace(factor), (void *)"*");
    } else if((maybe_term = parse_character(parse_whitespace(factor), (void *)"/")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_DIVIDE);
      return parse_character(parse_whitespace(factor), (void *)"/");
    } else if((maybe_term = parse_character(parse_whitespace(factor), (void *)"%")) != NULL) {
      ADJUST_BINARY_TREE(parse_term, maybe_term, BIN_MOD);
      return parse_character(parse_whitespace(factor), (void *)"%");
    } else return factor;
  } return NULL;
}

const char * parse_expression(const char * input, void * data) {
  const char * term = parse_term(parse_whitespace(input), data);
  const char * maybe_expression;
  if(term) {
    if((maybe_expression = parse_character(parse_whitespace(term), (void *)"+")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_expression, BIN_PLUS);
      return parse_character(parse_whitespace(term), (void *)"+");
    } else if((maybe_expression = parse_character(parse_whitespace(term), (void *)"-")) != NULL) {
      ADJUST_BINARY_TREE(parse_expression, maybe_expression, BIN_MINUS);
      return parse_character(parse_whitespace(term), (void *)"-");
    } else return term;
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
    case UN_MINUS:   printf("-\n");                                     break;
    case BIN_PLUS:   printf("+\n");                                     break;
    case BIN_MINUS:  printf("-\n");                                     break;
    case BIN_MULT:   printf("*\n");                                     break;
    case BIN_DIVIDE: printf("/\n");                                     break;
    case BIN_MOD:    printf("%\n");                                     break;
  }
  for(uint32_t i = 0; i < the_expression.qty_children; i++) {
    debug_expression(the_expression.child[i], indent + 1);
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
