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
  BOOL,
  UN_MINUS,
  BIN_PLUS,
  BIN_MINUS,
  SIN,
  COS,
  TAN,
  ARCSIN,
  ARCCOS,
  ARCTAN,
  LOG,
  LN,
  BIN_MULT,
  BIN_DIVIDE,
  BIN_MOD,
  BIN_POW,
  BIN_EQ,
  BIN_NEQ,
  BIN_GEQ,
  BIN_GT,
  BIN_LEQ,
  BIN_LT,
} expression_type;

const char * expression_type_to_string(expression_type type);

typedef struct EXPRESSION_T {
  union {
    int    int_value;
    double double_value;
    char * string_value;
    bool   bool_value;
  } value;
  struct EXPRESSION_T * child;
  uint32_t qty_children;
  expression_type type;
} expression;

const char * parse_ws(const char * input);

const char * or_p(const char * input, void * data, uint32_t num_args, ...);

const char * parse_variable_name(const char * input, void * data);
const char * parse_number(const char * input, void * data);
const char * parse_string(const char * input, void * data);
const char * parse_character(const char * input, void * data);
const char * parse_word(const char * input, void * data);
const char * parse_bool(const char * input, void * data);

#define ADJUST_UNARY_TREE(parser, str, parent_type) \
    expression * parent = (expression *)data; \
    expression child = {0}; \
    factor = parser(parse_ws(factor), &child); \
    parent->type = parent_type; \
    parent->qty_children = 1; \
    parent->child = (expression *)calloc(1, sizeof(struct EXPRESSION_T)); \
    parent->child[0] = child; \
    return factor;

#define ADJUST_BINARY_TREE(right_p, str, parent_type)                    \
  expression parent = {0};                                               \
  expression * left = (expression *)data;                                \
  expression right = {0};                                                \
  str = right_p(parse_ws(str), &right);                                  \
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
const char * parse_boolean_expression(const char * input, void * data);

bool is_double_delineator(char c);
bool is_whitespace(char c);
void debug_expression(expression the_expression, int indent);
void validate_type(expression the_expression, expression_type type, const char * err);
void free_expression(expression the_expression);

typedef enum {
  ELLIPSE,
  LINE,
  RECTANGLE,
} shape_type;

typedef struct PARSED_SHAPE_T {
  expression * values;
  uint32_t qty_values;
  shape_type type;
} parsed_shape;

const char * parse_shape(const char * input, void * data);
parsed_shape * add_expression(parsed_shape * the_shape, expression the_expression);
void free_parsed_shape(parsed_shape the_shape);

typedef enum {
  EXPR,
  SHAPE,
} slc_value_type;

typedef enum {
  ASSIGNMENT,
} lline_type;

typedef union {
  expression the_expr;
  parsed_shape the_shape;
} lline_union;

typedef struct PARSED_LINE_T {
  lline_union * value;
  slc_value_type * value_type;
  lline_type type;
  uint32_t qty_values;
} parsed_lline;

const char * parse_assignment(const char * input, void * data);
parsed_lline add_to_lline(parsed_lline the_lline, slc_value_type type, void * addition);
void free_parsed_lline(parsed_lline the_lline);

#endif
