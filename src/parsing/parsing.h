#ifndef PARSING_H
#define PARSING_H
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 1024

typedef enum {
  INT,
  DOUBLE,
  STRING,
} expression_type;

typedef struct EXPRESSION_T {
  union {
    int    int_value;
    double double_value;
    char * string_value;
  } value;
  struct EXPRESSION_T * expression;
  uint64_t qty_children;
} expression;

const char * parse_variable_name(const char * input, expression * the_expression);
const char * parse_number(const char * input, expression * the_expression);

#endif
