#include "evaluation_types.h"

shape deep_copy_shape(shape original) {
  shape copy = {0};
  copy.type = original.type;
  switch(original.type) {
    case RECTANGLE:
      copy.value.the_rectangle = original.value.the_rectangle;
      break;
    case ELLIPSE:
      copy.value.the_ellipse = original.value.the_ellipse;
      break;
    case LINE:
      copy.value.the_line = original.value.the_line;
      break;
    case CANVAS:
      copy.value.the_canvas = deep_copy_canvas(original.value.the_canvas);
      break;
  }
  return copy;
}

void free_shape(shape the_shape) {
  if(the_shape.type == CANVAS) {
    free_canvas(the_shape.value.the_canvas);
  }
}

array deep_copy_array(array original) {
  array copy = {0};
  copy.qty_values = original.qty_values;
  copy.value = (slc_value_primitive *)calloc(original.qty_values, sizeof(slc_value_primitive));
  copy.value_type = (slc_primitive_type *)calloc(original.qty_values, sizeof(slc_primitive_type));
  for(uint32_t i = 0; i < original.qty_values; i++) {
    copy.value_type[i] = original.value_type[i];
    switch(original.value_type[i]) {
      case EXPR:
        copy.value[i].the_expr = deep_copy_expression(original.value[i].the_expr);
        break;
      case SHAPE:
        copy.value[i].the_shape = deep_copy_shape(original.value[i].the_shape);
        break;
      case ARRAY:
        *copy.value[i].the_array = deep_copy_array(*original.value[i].the_array);
        break;
    }
  }
  return copy;
}

array add_to_array(array the_array, slc_primitive_type type, void * addition, symbol_table * st) {
  the_array.qty_values++;
  if(the_array.value) {
    the_array.value = (slc_value_primitive *)realloc(the_array.value,
        the_array.qty_values * sizeof(slc_value_primitive));
    the_array.value_type = (slc_primitive_type *)realloc(the_array.value_type,
        the_array.qty_values * sizeof(slc_primitive_type));
  } else {
    the_array.value = (slc_value_primitive *)calloc(1, sizeof(slc_value_primitive));
    the_array.value_type = (slc_primitive_type *)calloc(1, sizeof(slc_primitive_type));
  }
  the_array.value_type[the_array.qty_values - 1] = type;
  switch(type) {
    case EXPR:
      the_array.value[the_array.qty_values - 1].the_expr
        = deep_copy_expression(evaluate_expression(*(expression *)addition, st).value.the_expr);
      break;
    case SHAPE:
      the_array.value[the_array.qty_values - 1].the_shape
        = evaluate_shape(*(parsed_shape *)addition, st).value.the_shape;
      break;
    case ARRAY:
      the_array.value[the_array.qty_values - 1].the_array
        = evaluate_array(*(parsed_array *)addition, st).value.the_array;
      break;
  }
  return the_array;
}

void free_array(array the_array) {
  for(uint32_t i = 0; i < the_array.qty_values; i++) {
    switch(the_array.value_type[i]) {
      case EXPR:
        free_expression(the_array.value[i].the_expr);
        break;
      case SHAPE:
        free_shape(the_array.value[i].the_shape);
        break;
      case ARRAY:
        free_array(the_array.value[i].the_array[0]);
        if(the_array.value[i].the_array)
          free(the_array.value[i].the_array);
        break;
    }
  }
  if(the_array.value_type)
    free(the_array.value_type);
  if(the_array.value)
    free(the_array.value);
}

slc_value deep_copy_slc_value(slc_value original) {
  slc_value copy = {0};
  copy.type = original.type;
  switch(original.type) {
    case EXPR:
      copy.value.the_expr = deep_copy_expression(original.value.the_expr);
      break;
    case SHAPE:
      copy.value.the_shape = deep_copy_shape(original.value.the_shape);
      break;
    case ARRAY:
      *copy.value.the_array = deep_copy_array(*original.value.the_array);
      break;
  }
  return copy;
}

void free_slc_value(slc_value the_value) {
  switch(the_value.type) {
    case EXPR:
      free_expression(the_value.value.the_expr);
      break;
    case SHAPE:
      free_shape(the_value.value.the_shape);
      break;
    case ARRAY:
      free_array(the_value.value.the_array[0]);
      if(the_value.value.the_array)
        free(the_value.value.the_array);
      break;
  }
}
