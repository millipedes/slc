#ifndef PARSING_H
#define PARSING_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 1024

typedef enum {
  INT,
  DOUBLE,
  VAR,
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
  expression_type type;
} expression;

const char * parse_whitespace(const char * input);

const char * or_p(const char * input, void * data, uint64_t num_args, ...);

const char * parse_variable_name(const char * input, void * data);
const char * parse_number(const char * input, void * data);
const char * parse_string(const char * input, void * data);
const char * parse_expression(const char * input, void * data);

bool is_double_delineator(char c);
bool is_whitespace(char c);

#endif
