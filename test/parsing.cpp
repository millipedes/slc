#include "test_helper.h"

TEST(parsing, variable_name_test_0) {
  const char * the_input = "some_string = 123";
  expression the_expression = {0};
  const char * remainder = parse_variable_name(the_input, &the_expression);
  ASSERT_TRUE(!strncmp(" = 123", remainder, MAX_STR));
  test_expression(the_expression, VAR, (void *)"some_string");
  free_expression(the_expression);
}

TEST(parsing, number_test_0) {
  const char * the_input = "123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value = 123;
  test_expression(the_expression, INT, &value);
}

TEST(parsing, number_test_1) {
  const char * the_input = "123.123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 123.123;
  test_expression(the_expression, DOUBLE, &value);
}

TEST(parsing, number_test_2) {
  const char * the_input = "1e-2";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, DOUBLE, &value);
}

TEST(parsing, number_test_3) {
  const char * the_input = "1E-2";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, DOUBLE, &value);
}

TEST(parsing, string_test_0) {
  const char * the_input = "\"hello world\"";
  expression the_expression = {0};
  const char * remainder = parse_string(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  test_expression(the_expression, STRING, (void *)"\"hello world\"");
  free_expression(the_expression);
}

TEST(parsing, string_test_1) {
  const char * the_input = "\"hello world";
  expression the_expression = {0};
  const char * remainder = parse_string(the_input, &the_expression);
  ASSERT_TRUE(remainder == NULL); // cpp doesn't allow for this in ASSERT_EQ :(
}

TEST(parsing, word_test_0) {
  const char * the_input = ".\\";
  const char * remainder = parse_word(the_input, (void *)".\\");
  ASSERT_EQ(remainder[0], '\0');
}

TEST(parsing, factor_test_0) {
  const char * the_input = "(((((-1e-2)))))";
  expression the_expression = {0};
  const char * remainder = parse_factor(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, factor_test_1) {
  const char * the_input = "-(((((-1e-2)))))";
  expression the_expression = {0};
  const char * remainder = parse_factor(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], UN_MINUS, NULL);
  test_expression(the_expression.child[0].child[0], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, term_test_0) {
  const char * the_input = "1e-2 * 1e-2";
  expression the_expression = {0};
  const char * remainder = parse_term(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, BIN_MULT, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  test_expression(the_expression.child[1], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, term_test_1) {
  const char * the_input = "1e-2 * 1e-2 * 1e-2";
  expression the_expression = {0};
  const char * remainder = parse_term(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, BIN_MULT, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  test_expression(the_expression.child[1], BIN_MULT, NULL);
  test_expression(the_expression.child[1].child[0], DOUBLE, &value);
  test_expression(the_expression.child[1].child[1], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, term_test_2) {
  const char * the_input = "1 / 2 % 3";
  expression the_expression = {0};
  const char * remainder = parse_term(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(the_expression, BIN_DIVIDE, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], BIN_MOD, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
  test_expression(the_expression.child[1].child[1], INT, &value_three);
  free_expression(the_expression);
}

TEST(parsing, term_test_3) {
  const char * the_input = "\"some string\" / -1e-2 % var_name";
  expression the_expression = {0};
  const char * remainder = parse_term(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, BIN_DIVIDE, NULL);
  test_expression(the_expression.child[0], STRING, (void *)"\"some string\"");
  test_expression(the_expression.child[1], BIN_MOD, NULL);
  test_expression(the_expression.child[1].child[0], UN_MINUS, NULL);
  test_expression(the_expression.child[1].child[0].child[0], DOUBLE, &value);
  test_expression(the_expression.child[1].child[1], VAR, (void *)"var_name");
  free_expression(the_expression);
}

TEST(parsing, expression_test_0) {
  const char * the_input = "-123";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value = 123;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], INT, &value);
  free_expression(the_expression);
}

TEST(parsing, expression_test_1) {
  const char * the_input = "-1e-2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, expression_test_2) {
  const char * the_input = "\"hello world\"";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  test_expression(the_expression, STRING, (void *)"\"hello world\"");
  free_expression(the_expression);
}

TEST(parsing, expression_test_3) {
  const char * the_input = "\"hello world";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, expression_test_4) {
  const char * the_input = "1 + 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_PLUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_5) {
  const char * the_input = "1 + 2 * 3";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(the_expression, BIN_PLUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], BIN_MULT, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
  test_expression(the_expression.child[1].child[1], INT, &value_three);
  free_expression(the_expression);
}

TEST(parsing, expression_test_6) {
  const char * the_input = "(1 + 2) * 3";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(the_expression, BIN_MULT, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  test_expression(the_expression.child[1], INT, &value_three);
  free_expression(the_expression);
}

TEST(parsing, expression_test_7) {
  const char * the_input = "-(1 + 2)";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_8) {
  const char * the_input = "(((((1 - - 2)))))";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_MINUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], UN_MINUS, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_9) {
  const char * the_input = "1 ^ 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_POW, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_10) {
  const char * the_input = "(1 + 2) ^ -(1 + 2)";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_POW, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  test_expression(the_expression.child[1], UN_MINUS, NULL);
  test_expression(the_expression.child[1].child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[1].child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[1].child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_11) {
  const char * the_input = "1 == 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_EQ, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_12) {
  const char * the_input = "1 != 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_NEQ, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_13) {
  const char * the_input = "1 >= 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_GEQ, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_14) {
  const char * the_input = "1 > 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_GT, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_15) {
  const char * the_input = "1 <= 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_LEQ, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_16) {
  const char * the_input = "1 < 2";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_LT, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_17) {
  const char * the_input = "true";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  bool value_one = true;
  test_expression(the_expression, BOOL, &value_one);
}

TEST(parsing, expression_test_18) {
  const char * the_input = "false";
  expression the_expression = {0};
  const char * remainder = parse_boolean_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  bool value_one = false;
  test_expression(the_expression, BOOL, &value_one);
}

TEST(parsing, shape_test_0) {
  const char * the_input = "rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
  int value_one = 1;
  int value_two = 2;
  test_expression(the_shape.values[1].child[0], INT, &value_one);
  test_expression(the_shape.values[1].child[1], INT, &value_two);
  test_expression(the_shape.values[2], VAR, (void *)"center_x");
  test_expression(the_shape.values[3], INT, &value_two);
  test_expression(the_shape.values[4], VAR, (void *)"center_y");
  test_expression(the_shape.values[5], INT, &value_one);
  test_expression(the_shape.values[6], VAR, (void *)"width");
  test_expression(the_shape.values[7], INT, &value_one);
  test_expression(the_shape.values[8], VAR, (void *)"height");
  test_expression(the_shape.values[9], INT, &value_two);
  free_parsed_shape(the_shape);
}

TEST(parsing, assignment_test_0) {
  const char * the_input = "x = rectangle();";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, ASSIGNMENT);
  test_expression(the_lline.value[0].the_expr, VAR, (void *)"x");
  ASSERT_EQ(the_lline.value[1].the_shape.type, RECTANGLE);
  ASSERT_EQ(the_lline.value[1].the_shape.qty_values, 0);
  ASSERT_TRUE(the_lline.value[1].the_shape.values == NULL);
  free_parsed_lline(the_lline);
}

TEST(parsing, assignment_test_1) {
  const char * the_input = "some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, ASSIGNMENT);
  test_expression(the_lline.value[0].the_expr, VAR, (void *)"some_value");
  parsed_shape the_shape = the_lline.value[1].the_shape;
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
  int value_one = 1;
  int value_two = 2;
  test_expression(the_shape.values[1].child[0], INT, &value_one);
  test_expression(the_shape.values[1].child[1], INT, &value_two);
  test_expression(the_shape.values[2], VAR, (void *)"center_x");
  test_expression(the_shape.values[3], INT, &value_two);
  test_expression(the_shape.values[4], VAR, (void *)"center_y");
  test_expression(the_shape.values[5], INT, &value_one);
  test_expression(the_shape.values[6], VAR, (void *)"width");
  test_expression(the_shape.values[7], INT, &value_one);
  test_expression(the_shape.values[8], VAR, (void *)"height");
  test_expression(the_shape.values[9], INT, &value_two);
  free_parsed_lline(the_lline);
}
