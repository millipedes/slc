#ifndef PARSING_H
#define PARSING_H

#include "parsing_ds.h"

#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#define MAX_STR 1024


const char * parse_ws(const char * input);

const char * or_p(const char * input, void * data, uint32_t num_args, ...);

const char * parse_variable_name(const char * input, void * data);
const char * parse_number(const char * input, void * data);
const char * parse_string(const char * input, void * data);
const char * parse_character(const char * input, void * data);
const char * parse_word(const char * input, void * data);
const char * parse_bool(const char * input, void * data);
const char * parse_array(const char * input, void * data);

#define ADJUST_UNARY_TREE(parser, str, parent_type)                       \
    expression * parent = (expression *)data;                             \
    expression child = {0};                                               \
    factor = parser(parse_ws(factor), &child);                            \
    parent->type = parent_type;                                           \
    parent->qty_children = 1;                                             \
    parent->child = (expression *)calloc(1, sizeof(struct EXPRESSION_T)); \
    parent->child[0] = child;                                             \
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
const char * parse_relational_expression(const char * input, void * data);
const char * parse_precedence_1_expression(const char * input, void * data);

bool is_double_delineator(char c);
bool is_whitespace(char c);

const char * parse_shape(const char * input, void * data);

const char * parse_assignment(const char * input, void * data);

#endif
