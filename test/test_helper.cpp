#include "test_helper.h"

void test_expression(expression the_expression, expression_type type, void * value) {
  ASSERT_EQ(the_expression.type, type);
  switch(type) {
    case INT:
      ASSERT_EQ(the_expression.value.int_value, *(int *)value);
      break;
    case DOUBLE:
      ASSERT_EQ(the_expression.value.double_value, *(double *)value);
      break;
    case VAR:
    case STRING:
      ASSERT_TRUE(!strncmp((char *)value, the_expression.value.string_value, MAX_STR));
      break;
    case BOOL:
      ASSERT_EQ(the_expression.value.bool_value, *(bool *)value);
      break;
    case UN_MINUS:
      ASSERT_EQ(the_expression.qty_children, 1);
      break;
    case BIN_PLUS:
    case BIN_MINUS:
    case BIN_MULT:
    case BIN_DIVIDE:
    case BIN_MOD:
    case BIN_POW:
    case BIN_EQ:
    case BIN_NEQ:
    case BIN_GEQ:
    case BIN_GT:
    case BIN_LEQ:
    case BIN_LT:
      ASSERT_EQ(the_expression.qty_children, 2);
      break;
  }
}
