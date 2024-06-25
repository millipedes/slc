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
  UN_MINUS,
  BIN_PLUS,
  BIN_MINUS,
  BIN_MULT,
  BIN_DIVIDE,
  BIN_MOD,
} expression_type;

typedef struct EXPRESSION_T {
  union {
    int    int_value;
    double double_value;
    char * string_value;
  } value;
  struct EXPRESSION_T * child;
  uint64_t qty_children;
  expression_type type;
} expression;

const char * parse_whitespace(const char * input);

const char * or_p(const char * input, void * data, uint64_t num_args, ...);

const char * parse_variable_name(const char * input, void * data);
const char * parse_number(const char * input, void * data);
const char * parse_string(const char * input, void * data);
const char * parse_character(const char * input, void * data);
const char * parse_word(const char * input, void * data);

#define ADJUST_BINARY_TREE(right_p, str, parent_type)                    \
  expression parent = {0};                                               \
  expression * left = (expression *)data;                                \
  expression right = {0};                                                \
  str = right_p(parse_whitespace(str), &right);                          \
  if(str) {                                                              \
    parent.type = parent_type;                                           \
    parent.qty_children = 2;                                             \
    parent.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T)); \
    parent.child[0] = *left;                                             \
    parent.child[1] = right;                                             \
    *(expression *)data = parent;                                        \
    return str;                                                          \
  }

const char * parse_factor(const char * input, void * data);
const char * parse_term(const char * input, void * data);
const char * parse_expression(const char * input, void * data);

bool is_double_delineator(char c);
bool is_whitespace(char c);
void debug_expression(expression the_expression, int indent);

typedef struct LAMBDA_T {
  expression arg;
  union {
    expression expr;
    struct LAMBDA_T * func;
  } function;
} lambda;

const char * parse_lambda_expression(const char * input, void * data);

#endif
