#ifndef EVALUATION_TYPES_H
#define EVALUATION_TYPES_H

#include "../shape/ellipse.h"
#include "../shape/rectangle.h"

typedef struct SHAPE_T {
  union {
    ellipse the_ellipse;
    line the_line;
    rectangle the_rectangle;
  } value;
  shape_type type;
} shape;

typedef struct SLC_VALUE_T {
  union {
    expression the_expr;
    shape the_shape;
  } value;
  slc_primitive_type type;
} slc_value;

#endif
