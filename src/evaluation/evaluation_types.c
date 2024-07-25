#include "evaluation_types.h"

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
        = evaluate_expression(*(expression *)addition, st).value.the_expr;
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

void free_slc_value(slc_value the_value) {
  switch(the_value.type) {
    case EXPR:
      free_expression(the_value.value.the_expr);
      break;
    case SHAPE:
      break;
    case ARRAY:
      free_array(the_value.value.the_array[0]);
      if(the_value.value.the_array)
        free(the_value.value.the_array);
      break;
  }
}
