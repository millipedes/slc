#include "parsing.h"

const char * parse_whitespace(const char * input) {
  uint64_t inc = 0;
  while(is_whitespace(*(input + inc))) inc++;
  return input + inc;
}

const char * or_p(const char * input, void * data, uint64_t num_args, ...) {
  va_list args;
  va_start(args, num_args);
  for(uint64_t i = 0; i < num_args; i++) {
    const char * remainder = va_arg(args,
        const char * (*)(const char *, void *))(input, data);
    if(remainder != input) {
      va_end(args);
      return remainder;
    }
  }
  va_end(args);
  return input;
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
  }
  return input + inc;
}

const char * parse_number(const char * input, void * data) {
  expression * the_expression = (expression *)data;
  uint64_t inc = 0;
  bool is_double = false;

  while(isdigit(*(input + inc))
      || is_double_delineator(*(input + inc))
      || *(input + inc) == '-') {
    if(is_double_delineator(*(input + inc))) {
      is_double = true;
    }
    inc++;
  }

  if(is_double && inc > 0) {
    the_expression->value.double_value = strtod(input, NULL);
    the_expression->type = DOUBLE;
  } else if(inc > 0) {
    the_expression->value.int_value = strtol(input, NULL, 10);
    the_expression->type = INT;
  }

  return input + inc;
}

const char * parse_string(const char * input, void * data) {
  expression * the_expression = (expression *)data;
  uint64_t inc = 1;
  if(input[0] != '\"') {
    return input;
  }
  while(*(input + inc) != '\"') {
    if(*(input + inc) == '\0') return input; // not matched
    inc++;
  }
  inc++;
  the_expression->value.string_value = (char *)calloc(inc, sizeof(char));
  strncpy(the_expression->value.string_value, input, inc);
  the_expression->value.string_value[inc] = '\0';
  the_expression->type = STRING;
  return input + inc;
}

const char * parse_character(const char * input, void * data) {
  if(input[0] == *(char *)data)
    return input + 1;
  return input;
}

const char * parse_expression(const char * input, void * data) {
  return or_p(input, data, 3, parse_string, parse_number, parse_variable_name);
}

bool is_double_delineator(char c) {
  return c == '.' || c == 'e' || c == 'E';
}

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f';
}
