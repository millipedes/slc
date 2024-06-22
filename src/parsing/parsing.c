#include "parsing.h"

const char * parse_variable_name(const char * input, expression * the_expression) {
  uint64_t inc = 0;
  while(isalpha(*(input + inc)) || *(input + inc) == '_') inc++;
  the_expression->value.string_value = (char *)calloc(inc + 1, sizeof(char));
  strncpy(the_expression->value.string_value, input, inc);
  the_expression->value.string_value[inc] = '\0';
  return input + inc;
}

const char * parse_number(const char * input, expression * the_expression) {
  uint64_t inc = 0;
  bool is_double = false;

  while(isdigit(*(input + inc))
      || *(input + inc) == '.'
      || *(input + inc) == 'e'
      || *(input + inc) == 'E'
      || *(input + inc) == '-') {
    if(*(input + inc) == '.' || *(input + inc) == 'e' || *(input + inc) == 'E') {
      is_double = true;
    }
    inc++;
  }

  if(is_double) {
    the_expression->value.double_value = strtod(input, NULL);
  } else {
    the_expression->value.int_value = strtol(input, NULL, 10);
  }

  return input + inc;
}
