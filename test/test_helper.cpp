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

void validate_ellipse(ellipse truth, ellipse test) {
  ASSERT_EQ(truth.center.x, test.center.x);
  ASSERT_EQ(truth.center.y, test.center.y);
  ASSERT_EQ(truth.color.r, test.color.r);
  ASSERT_EQ(truth.color.b, test.color.b);
  ASSERT_EQ(truth.color.g, test.color.g);
  ASSERT_EQ(truth.major_axis, test.major_axis);
  ASSERT_EQ(truth.minor_axis, test.minor_axis);
  ASSERT_EQ(truth.thickness, test.thickness);
}

void validate_line(line truth, line test) {
  ASSERT_EQ(truth.to.x, test.to.x);
  ASSERT_EQ(truth.to.y, test.to.y);
  ASSERT_EQ(truth.from.x, test.from.x);
  ASSERT_EQ(truth.from.y, test.from.y);
  ASSERT_EQ(truth.color.r, test.color.r);
  ASSERT_EQ(truth.color.g, test.color.g );
  ASSERT_EQ(truth.color.b, test.color.b);
  ASSERT_EQ(truth.thickness, test.thickness);
}

void validate_rectangle(rectangle truth, rectangle test) {
  ASSERT_EQ(truth.center.x, test.center.x);
  ASSERT_EQ(truth.center.y, test.center.y);
  ASSERT_EQ(truth.color.r, test.color.r);
  ASSERT_EQ(truth.color.g, test.color.g);
  ASSERT_EQ(truth.color.b, test.color.b);
  ASSERT_EQ(truth.height, test.height);
  ASSERT_EQ(truth.width, test.width);
  ASSERT_EQ(truth.thickness, test.thickness);
}
