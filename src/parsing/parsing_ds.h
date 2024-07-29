#ifndef PARSING_DS_H
#define PARSING_DS_H

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
  SIN,
  COS,
  TAN,
  ARCSIN,
  ARCCOS,
  ARCTAN,
  LOG,
  LN,
  ARRAY_ACCESSOR,
  BIN_PLUS,
  BIN_MINUS,
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

expression deep_copy_expression(expression the_expression);
expression add_expression_child(expression the_expression, expression addition);
void debug_expression(expression the_expression, int indent);
void free_expression(expression the_expression);
void validate_type(expression the_expression, expression_type type, const char * err);

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

parsed_shape * add_expression(parsed_shape * the_shape, expression the_expression);
void free_parsed_shape(parsed_shape the_shape);

typedef enum {
  EXPR,
  SHAPE,
  ARRAY,
} slc_primitive_type;

typedef enum {
  ASSIGNMENT,
  DRAW_STMT,
} lline_type;

struct PARSED_ARRAY_T;
typedef struct PARSED_ARRAY_T parsed_array;
typedef union {
  expression the_expr;
  parsed_shape the_shape;
  parsed_array * the_array;
} slc_primitive;

typedef struct PARSED_ARRAY_T {
  slc_primitive * value;
  slc_primitive_type * value_type;
  uint32_t qty_values;
} parsed_array;

parsed_array add_to_parsed_array(parsed_array the_array, slc_primitive_type type, void * addition);
void free_parsed_array(parsed_array the_array);

typedef struct PARSED_LINE_T {
  slc_primitive * value;
  slc_primitive_type * value_type;
  lline_type type;
  uint32_t qty_values;
} parsed_lline;

parsed_lline add_to_lline(parsed_lline the_lline, slc_primitive_type type, void * addition);
void free_parsed_lline(parsed_lline the_lline);

#endif
