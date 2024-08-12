#ifndef EVALUATION_TYPES_H
#define EVALUATION_TYPES_H

#include "ellipse.h"
#include "rectangle.h"

typedef struct SHAPE_T {
  union {
    ellipse the_ellipse;
    line the_line;
    rectangle the_rectangle;
    canvas the_canvas;
  } value;
  shape_type type;
} shape;

void free_shape(shape the_shape);

struct ARRAY_T;
typedef struct ARRAY_T array;
typedef union {
  expression the_expr;
  shape the_shape;
  array * the_array;
} slc_value_primitive;

typedef struct ARRAY_T {
  slc_value_primitive * value;
  slc_primitive_type * value_type;
  uint32_t qty_values;
} array;

array add_to_array(array the_array, slc_primitive_type type, void * addition, symbol_table * st);
void free_array(array the_array);

typedef struct SLC_VALUE_T {
  slc_value_primitive value;
  slc_primitive_type type;
} slc_value;

void free_slc_value(slc_value the_value);

extern slc_value evaluate_expression(expression the_expression, symbol_table * st);
extern slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st);
extern slc_value evaluate_array(parsed_array the_array, symbol_table * st);

#endif
