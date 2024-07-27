#include "parsing_ds.h"

const char * expression_type_to_string(expression_type type) {
  switch(type) {
    case INT:            return "Int";
    case DOUBLE:         return "Double";
    case VAR:            return "Var";
    case STRING:         return "String";
    case BOOL:           return "Bool";
    case UN_MINUS:       return "Un Minus";
    case SIN:            return "Sin";
    case COS:            return "Cos";
    case TAN:            return "Tan";
    case ARCSIN:         return "Arcsin";
    case ARCCOS:         return "Arccos";
    case ARCTAN:         return "Arctan";
    case LOG:            return "Log";
    case LN:             return "Ln";
    case ARRAY_ACCESSOR: return "Array Access";
    case BIN_PLUS:       return "Bin Plus";
    case BIN_MINUS:      return "Bin Minus";
    case BIN_MULT:       return "Bin Mult";
    case BIN_DIVIDE:     return "Bin Divide";
    case BIN_POW:        return "Bin Pow";
    case BIN_MOD:        return "Bin Mod";
    case BIN_EQ:         return "Bin Eq";
    case BIN_NEQ:        return "Bin Neq";
    case BIN_GEQ:        return "Bin Geq";
    case BIN_GT:         return "Bin Gt";
    case BIN_LEQ:        return "Bin Leq";
    case BIN_LT:         return "Bin Lt";
  }
  return NULL;
}

void debug_expression(expression the_expression, int indent) {
  for(int i = 0; i < 2 * indent; i++) printf(" ");
  switch(the_expression.type) {
    case INT:            printf("%d\n", the_expression.value.int_value);    break;
    case DOUBLE:         printf("%f\n", the_expression.value.double_value); break;
    case VAR:            printf("%s\n", the_expression.value.string_value); break;
    case STRING:         printf("%s\n", the_expression.value.string_value); break;
    case BOOL:           printf("%s\n", the_expression.value.bool_value ? "true" : "false"); break;
    case UN_MINUS:       printf("-\n");                                     break;
    case SIN:            printf("sin\n");                                   break;
    case COS:            printf("cos\n");                                   break;
    case TAN:            printf("tan\n");                                   break;
    case ARCSIN:         printf("arcsin\n");                                break;
    case ARCCOS:         printf("arccos\n");                                break;
    case ARCTAN:         printf("arctan\n");                                break;
    case LOG:            printf("log\n");                                   break;
    case LN:             printf("ln\n");                                    break;
    case ARRAY_ACCESSOR: printf("[x]\n");                                   break;
    case BIN_PLUS:       printf("+\n");                                     break;
    case BIN_MINUS:      printf("-\n");                                     break;
    case BIN_MULT:       printf("*\n");                                     break;
    case BIN_DIVIDE:     printf("/\n");                                     break;
    case BIN_MOD:        printf("%\n");                                     break;
    case BIN_POW:        printf("^\n");                                     break;
    case BIN_EQ:         printf("==\n");                                    break;
    case BIN_NEQ:        printf("!=\n");                                    break;
    case BIN_GEQ:        printf(">=\n");                                    break;
    case BIN_GT:         printf(">\n");                                     break;
    case BIN_LEQ:        printf("<=\n");                                    break;
    case BIN_LT:         printf("<\n");                                     break;
  }
  for(uint32_t i = 0; i < the_expression.qty_children; i++) {
    debug_expression(the_expression.child[i], indent + 1);
  }
}

expression add_expression_child(expression the_expression, expression addition) {
  the_expression.qty_children++;
  if(the_expression.child) {
    the_expression.child = (expression *)realloc(the_expression.child,
        the_expression.qty_children * sizeof(struct EXPRESSION_T));
  } else {
    the_expression.child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  }
  the_expression.child[the_expression.qty_children - 1] = addition;
  return the_expression;
}

void free_expression(expression the_expression) {
  if((the_expression.type == STRING || the_expression.type == VAR)
      && the_expression.value.string_value) {
    free(the_expression.value.string_value);
  }
  for(uint32_t i = 0; i < the_expression.qty_children; i++) {
    free_expression(the_expression.child[i]);
  }
  if(the_expression.child) {
    free(the_expression.child);
  }
}

void validate_type(expression the_expression, expression_type type, const char * err) {
  if(the_expression.type != type) {
    fprintf(stderr, err);
    exit(1);
  }
}

parsed_shape * add_expression(parsed_shape * the_shape, expression the_expression) {
  the_shape->qty_values++;
  if(the_shape->values) {
    the_shape->values = (expression *)realloc(the_shape->values,
        the_shape->qty_values * sizeof(struct EXPRESSION_T));
  } else {
    the_shape->values = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  }
  the_shape->values[the_shape->qty_values - 1] = the_expression;
  return the_shape;
}

void free_parsed_shape(parsed_shape the_shape) {
  for(uint32_t i = 0; i < the_shape.qty_values; i++) {
    free_expression(the_shape.values[i]);
  }
  if(the_shape.values) {
    free(the_shape.values);
  }
}

parsed_array add_to_parsed_array(parsed_array the_array, slc_primitive_type type, void * addition) {
  the_array.qty_values++;
  if(the_array.value) {
    the_array.value = (slc_primitive *)realloc(the_array.value,
        the_array.qty_values * sizeof(slc_primitive));
    the_array.value_type = (slc_primitive_type *)realloc(the_array.value_type,
        the_array.qty_values * sizeof(slc_primitive_type));
  } else {
    the_array.value = (slc_primitive *)calloc(1, sizeof(slc_primitive));
    the_array.value_type = (slc_primitive_type *)calloc(1, sizeof(slc_primitive_type));
  }
  the_array.value_type[the_array.qty_values - 1] = type;
  switch(type) {
    case EXPR:
      the_array.value[the_array.qty_values - 1].the_expr = *(expression *)addition;
      break;
    case SHAPE:
      the_array.value[the_array.qty_values - 1].the_shape = *(parsed_shape *)addition;
      break;
    case ARRAY:
      the_array.value[the_array.qty_values - 1].the_array = (parsed_array *)calloc(1, sizeof(struct PARSED_ARRAY_T));
      the_array.value[the_array.qty_values - 1].the_array[0] = *(parsed_array *)addition;
      break;
  }
  return the_array;
}

void free_parsed_array(parsed_array the_array) {
  for(uint32_t i = 0; i < the_array.qty_values; i++) {
    switch(the_array.value_type[i]) {
      case EXPR:
        free_expression(the_array.value[i].the_expr);
        break;
      case SHAPE:
        free_parsed_shape(the_array.value[i].the_shape);
        break;
      case ARRAY:
        free_parsed_array(the_array.value[i].the_array[0]);
        if(the_array.value[i].the_array)
          free(the_array.value[i].the_array);
        break;
    }
  }
  if(the_array.value)
    free(the_array.value);
  if(the_array.value_type)
    free(the_array.value_type);
}

parsed_lline add_to_lline(parsed_lline the_lline, slc_primitive_type type, void * addition) {
  the_lline.qty_values++;
  if(the_lline.value) {
    the_lline.value = (slc_primitive *)realloc(the_lline.value,
        the_lline.qty_values * sizeof(slc_primitive));
    the_lline.value_type = (slc_primitive_type *)realloc(the_lline.value_type,
        the_lline.qty_values * sizeof(slc_primitive_type));
  } else {
    the_lline.value = (slc_primitive *)calloc(1, sizeof(slc_primitive));
    the_lline.value_type = (slc_primitive_type *)calloc(1, sizeof(slc_primitive_type));
  }
  the_lline.value_type[the_lline.qty_values - 1] = type;
  switch(type) {
    case EXPR:
      the_lline.value[the_lline.qty_values - 1].the_expr = *(expression *)addition;
      break;
    case SHAPE:
      the_lline.value[the_lline.qty_values - 1].the_shape = *(parsed_shape *)addition;
      break;
    case ARRAY:
      the_lline.value[the_lline.qty_values - 1].the_array = (parsed_array *)calloc(1, sizeof(struct PARSED_ARRAY_T));
      the_lline.value[the_lline.qty_values - 1].the_array[0] = *(parsed_array *)addition;
  }
  return the_lline;
}

void free_parsed_lline(parsed_lline the_lline) {
  for(uint32_t i = 0; i < the_lline.qty_values; i++) {
    switch(the_lline.value_type[i]) {
      case EXPR:
        free_expression(the_lline.value[i].the_expr);
        break;
      case SHAPE:
        free_parsed_shape(the_lline.value[i].the_shape);
        break;
      case ARRAY:
        free_parsed_array(the_lline.value[i].the_array[0]);
        if(the_lline.value[i].the_array)
          free(the_lline.value[i].the_array);
        break;
    }
  }
  if(the_lline.value)
    free(the_lline.value);
  if(the_lline.value_type)
    free(the_lline.value_type);
}
