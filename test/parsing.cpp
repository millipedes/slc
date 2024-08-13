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
  test_expression(the_expression, STRING, (void *)"hello world");
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
  const char * remainder = parse_precedence_1_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, factor_test_1) {
  const char * the_input = "-(((((-1e-2)))))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_3_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_3_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_3_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_3_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, BIN_DIVIDE, NULL);
  test_expression(the_expression.child[0], STRING, (void *)"some string");
  test_expression(the_expression.child[1], BIN_MOD, NULL);
  test_expression(the_expression.child[1].child[0], UN_MINUS, NULL);
  test_expression(the_expression.child[1].child[0].child[0], DOUBLE, &value);
  test_expression(the_expression.child[1].child[1], VAR, (void *)"var_name");
  free_expression(the_expression);
}

TEST(parsing, expression_test_0) {
  const char * the_input = "-123";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value = 123;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], INT, &value);
  free_expression(the_expression);
}

TEST(parsing, expression_test_1) {
  const char * the_input = "-1e-2";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
  free_expression(the_expression);
}

TEST(parsing, expression_test_2) {
  const char * the_input = "\"hello world\"";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  test_expression(the_expression, STRING, (void *)"hello world");
  free_expression(the_expression);
}

TEST(parsing, expression_test_3) {
  const char * the_input = "\"hello world";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, expression_test_4) {
  const char * the_input = "1 + 2";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
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
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  bool value_one = true;
  test_expression(the_expression, BOOL, &value_one);
}

TEST(parsing, expression_test_18) {
  const char * the_input = "false";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  bool value_one = false;
  test_expression(the_expression, BOOL, &value_one);
}

TEST(parsing, expression_test_19) {
  const char * the_input = "sin((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, SIN, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_20) {
  const char * the_input = "cos((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, COS, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_21) {
  const char * the_input = "tan((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, TAN, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_22) {
  const char * the_input = "arcsin((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, ARCSIN, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_23) {
  const char * the_input = "arccos((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, ARCCOS, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_24) {
  const char * the_input = "arctan((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, ARCTAN, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_25) {
  const char * the_input = "log((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, LOG, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_26) {
  const char * the_input = "ln((1 + 2))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, LN, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  free_expression(the_expression);
}

TEST(parsing, expression_test_27) {
  const char * the_input = "x[0]";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 0;
  test_expression(the_expression, VAR, (void *)"x");
  test_expression(the_expression.child[0], ARRAY_ACCESSOR, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  free_expression(the_expression);
}

TEST(parsing, expression_test_28) {
  const char * the_input = "x[9 * 1][1 + 2]";
  expression the_expression = {0};
  const char * remainder = parse_precedence_7_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 9;
  int value_two = 1;
  int value_three = 2;
  test_expression(the_expression, VAR, (void *)"x");
  test_expression(the_expression.child[0], ARRAY_ACCESSOR, NULL);
  test_expression(the_expression.child[0].child[0], BIN_MULT, NULL);
  test_expression(the_expression.child[0].child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[0].child[1], INT, &value_two);
  test_expression(the_expression.child[0].child[1], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[1].child[0], INT, &value_two);
  test_expression(the_expression.child[0].child[1].child[1], INT, &value_three);
  free_expression(the_expression);
}

TEST(parsing, expression_test_29) {
  const char * the_input = "1 <= 2 && 1 == 2";
  expression the_expression = {0};
  const char * remainder = parse_precedence_11_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_BOOL_AND, NULL);
  test_expression(the_expression.child[0], BIN_LEQ, NULL);
  test_expression(the_expression.child[1], BIN_EQ, NULL);
  free_expression(the_expression);
}

TEST(parsing, expression_test_30) {
  symbol_table st = {0};
  const char * the_input = "-ln(0.5) + 1.0 * 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_11_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value_one = 0.5;
  double value_two = 1.0;
  double value_three = 2.0;
  test_expression(the_expression, BIN_PLUS, NULL);
  test_expression(the_expression.child[0], UN_MINUS, NULL);
  test_expression(the_expression.child[0].child[0], LN, NULL);
  test_expression(the_expression.child[0].child[0].child[0], DOUBLE, &value_one);
  test_expression(the_expression.child[1], BIN_MULT, NULL);
  test_expression(the_expression.child[1].child[0], DOUBLE, &value_two);
  test_expression(the_expression.child[1].child[1], DOUBLE, &value_three);
  free_expression(the_expression);
}

TEST(parsing, expression_test_31) {
  const char * the_input = "1 <= 2 && 1 == 2 || 2 == 3";
  expression the_expression = {0};
  const char * remainder = parse_precedence_12_expr(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  debug_expression(the_expression, 0);
  test_expression(the_expression, BIN_BOOL_OR, NULL);
  test_expression(the_expression.child[0], BIN_BOOL_AND, NULL);
  test_expression(the_expression.child[0].child[0], BIN_LEQ, NULL);
  test_expression(the_expression.child[0].child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[0].child[1], INT, &value_two);
  test_expression(the_expression.child[0].child[1], BIN_EQ, NULL);
  test_expression(the_expression.child[0].child[1].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1].child[1], INT, &value_two);
  test_expression(the_expression.child[1], BIN_EQ, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
  test_expression(the_expression.child[1].child[1], INT, &value_three);
  free_expression(the_expression);
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

TEST(parsing, shape_test_1) {
  const char * the_input = "canvas(width 1, height 2)";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_shape.type, CANVAS);
  int value_one = 1;
  int value_two = 2;
  test_expression(the_shape.values[0], VAR, (void *)"width");
  test_expression(the_shape.values[1], INT, &value_one);
  test_expression(the_shape.values[2], VAR, (void *)"height");
  test_expression(the_shape.values[3], INT, &value_two);
  free_parsed_shape(the_shape);
}

TEST(parsing, array_test_0) {
  const char * the_input = "[1, 2.0, \"hello\", world]";
  parsed_array the_array = {0};
  const char * remainder = parse_array(the_input, &the_array);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  double value_two = 2.0;
  test_expression(the_array.value[0].the_expr, INT, &value_one);
  test_expression(the_array.value[1].the_expr, DOUBLE, &value_two);
  test_expression(the_array.value[2].the_expr, STRING, (void *)"hello");
  test_expression(the_array.value[3].the_expr, VAR, (void *)"world");
  free_parsed_array(the_array);
}

TEST(parsing, array_test_1) {
  const char * the_input = "[1, 2.0, \"hello\", world, rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)]";
  parsed_array the_array = {0};
  const char * remainder = parse_array(the_input, &the_array);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  double value_two = 2.0;
  test_expression(the_array.value[0].the_expr, INT, &value_one);
  test_expression(the_array.value[1].the_expr, DOUBLE, &value_two);
  test_expression(the_array.value[2].the_expr, STRING, (void *)"hello");
  test_expression(the_array.value[3].the_expr, VAR, (void *)"world");
  ASSERT_EQ(the_array.value_type[4], SHAPE);
  parsed_shape the_shape = the_array.value[4].the_shape;
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
  int value_three = 1;
  int value_four = 2;
  test_expression(the_shape.values[1].child[0], INT, &value_three);
  test_expression(the_shape.values[1].child[1], INT, &value_four);
  test_expression(the_shape.values[2], VAR, (void *)"center_x");
  test_expression(the_shape.values[3], INT, &value_four);
  test_expression(the_shape.values[4], VAR, (void *)"center_y");
  test_expression(the_shape.values[5], INT, &value_three);
  test_expression(the_shape.values[6], VAR, (void *)"width");
  test_expression(the_shape.values[7], INT, &value_three);
  test_expression(the_shape.values[8], VAR, (void *)"height");
  test_expression(the_shape.values[9], INT, &value_four);
  free_parsed_array(the_array);
}

TEST(parsing, array_test_2) {
  const char * the_input = "[[1, 2.0], [\"hello\", world]]";
  parsed_array the_array = {0};
  const char * remainder = parse_array(the_input, &the_array);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  double value_two = 2.0;
  ASSERT_EQ(the_array.value_type[0], ARRAY);
  ASSERT_EQ(the_array.value_type[1], ARRAY);
  parsed_array sub_array_one = the_array.value[0].the_array[0];
  parsed_array sub_array_two = the_array.value[1].the_array[0];
  test_expression(sub_array_one.value[0].the_expr, INT, &value_one);
  test_expression(sub_array_one.value[1].the_expr, DOUBLE, &value_two);
  test_expression(sub_array_two.value[0].the_expr, STRING, (void *)"hello");
  test_expression(sub_array_two.value[1].the_expr, VAR, (void *)"world");
  free_parsed_array(the_array);
}

TEST(parsing, assignment_test_0) {
  const char * the_input = "x = rectangle();";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, ASSIGNMENT);
  ASSERT_EQ(the_lline.value_type[0], EXPR);
  ASSERT_EQ(the_lline.value_type[1], SHAPE);
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
  ASSERT_EQ(the_lline.value_type[0], EXPR);
  ASSERT_EQ(the_lline.value_type[1], SHAPE);
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

TEST(parsing, assignment_test_2) {
  const char * the_input = "x = [1 < 3 == 2 > 1, -(((1 - - 2)))];";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, ASSIGNMENT);
  ASSERT_EQ(the_lline.value_type[0], EXPR);
  ASSERT_EQ(the_lline.value_type[1], ARRAY);
  test_expression(the_lline.value[0].the_expr, VAR, (void *)"x");
  expression head_one = the_lline.value[1].the_array[0].value[0].the_expr;
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(head_one, BIN_EQ, NULL);
  test_expression(head_one.child[0], BIN_LT, NULL);
  test_expression(head_one.child[0].child[0], INT, &value_one);
  test_expression(head_one.child[0].child[1], INT, &value_three);
  test_expression(head_one.child[1], BIN_GT, NULL);
  test_expression(head_one.child[1].child[0], INT, &value_two);
  test_expression(head_one.child[1].child[1], INT, &value_one);
  expression head_two = the_lline.value[1].the_array[0].value[1].the_expr;
  test_expression(head_two, UN_MINUS, NULL);
  test_expression(head_two.child[0], BIN_MINUS, NULL);
  test_expression(head_two.child[0].child[0], INT, &value_one);
  test_expression(head_two.child[0].child[1], UN_MINUS, NULL);
  test_expression(head_two.child[0].child[1].child[0], INT, &value_two);
  free_parsed_lline(the_lline);
}

TEST(parsing, draw_test_0) {
  const char * the_input = "draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));";
  parsed_lline the_lline = {0};
  const char * remainder = parse_draw_statement(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, DRAW_STMT);
  ASSERT_EQ(the_lline.value_type[0], SHAPE);
  parsed_shape the_shape = the_lline.value[0].the_shape;
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

TEST(parsing, draw_test_1) {
  const char * the_input = "draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)) -> \"some_place\";";
  parsed_lline the_lline = {0};
  const char * remainder = parse_draw_statement(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  ASSERT_EQ(the_lline.type, DRAW_STMT);
  ASSERT_EQ(the_lline.value_type[0], SHAPE);
  parsed_shape the_shape = the_lline.value[0].the_shape;
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

  ASSERT_EQ(the_lline.value_type[1], EXPR);
  test_expression(the_lline.value[1].the_expr, STRING, (void *)"some_place");
  free_parsed_lline(the_lline);
}

TEST(parsing, if_test_0) {
  const char * the_input = "if 1 == 2 {"
                           "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
                           "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
                           "}";
  parsed_lline the_lline = {0};
  const char * remainder = parse_lline(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');

  ASSERT_EQ(the_lline.type, IF_STMT);
  ASSERT_EQ(the_lline.qty_children, 2);
  ASSERT_EQ(the_lline.qty_values, 1);

  int value_one = 1;
  int value_two = 2;
  test_expression(the_lline.value[0].the_expr, BIN_EQ, NULL);
  test_expression(the_lline.value[0].the_expr.child[0], INT, &value_one);
  test_expression(the_lline.value[0].the_expr.child[1], INT, &value_two);

  ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
  ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
  parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
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

  ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
  ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
  ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
  test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
  parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
  ASSERT_EQ(the_shape_two.type, RECTANGLE);
  test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
  test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
  test_expression(the_shape_two.values[1].child[0], INT, &value_one);
  test_expression(the_shape_two.values[1].child[1], INT, &value_two);
  test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
  test_expression(the_shape_two.values[3], INT, &value_two);
  test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
  test_expression(the_shape_two.values[5], INT, &value_one);
  test_expression(the_shape_two.values[6], VAR, (void *)"width");
  test_expression(the_shape_two.values[7], INT, &value_one);
  test_expression(the_shape_two.values[8], VAR, (void *)"height");
  test_expression(the_shape_two.values[9], INT, &value_two);

  free_parsed_lline(the_lline);
}

TEST(parsing, for_test_0) {
  const char * the_input = "for i in range(1 + 2) {"
                           "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
                           "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
                           "}";
  parsed_lline the_lline = {0};
  const char * remainder = parse_lline(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');

  ASSERT_EQ(the_lline.type, FOR_LOOP);
  ASSERT_EQ(the_lline.qty_children, 2);
  ASSERT_EQ(the_lline.qty_values, 2);

  int value_one = 1;
  int value_two = 2;
  test_expression(the_lline.value[0].the_expr, VAR, (void *)"i");
  test_expression(the_lline.value[1].the_expr, BIN_PLUS, NULL);
  test_expression(the_lline.value[1].the_expr.child[0], INT, &value_one);
  test_expression(the_lline.value[1].the_expr.child[1], INT, &value_two);

  ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
  ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
  parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
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

  ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
  ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
  ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
  test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
  parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
  ASSERT_EQ(the_shape_two.type, RECTANGLE);
  test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
  test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
  test_expression(the_shape_two.values[1].child[0], INT, &value_one);
  test_expression(the_shape_two.values[1].child[1], INT, &value_two);
  test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
  test_expression(the_shape_two.values[3], INT, &value_two);
  test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
  test_expression(the_shape_two.values[5], INT, &value_one);
  test_expression(the_shape_two.values[6], VAR, (void *)"width");
  test_expression(the_shape_two.values[7], INT, &value_one);
  test_expression(the_shape_two.values[8], VAR, (void *)"height");
  test_expression(the_shape_two.values[9], INT, &value_two);

  free_parsed_lline(the_lline);
}

TEST(parsing, for_test_1) {
  const char * the_input = "for i in range(1, 2) {"
                           "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
                           "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
                           "}";
  parsed_lline the_lline = {0};
  const char * remainder = parse_lline(the_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');

  ASSERT_EQ(the_lline.type, FOR_LOOP);
  ASSERT_EQ(the_lline.qty_children, 2);
  ASSERT_EQ(the_lline.qty_values, 3);

  int value_one = 1;
  int value_two = 2;
  test_expression(the_lline.value[0].the_expr, VAR, (void *)"i");
  test_expression(the_lline.value[1].the_expr, INT, &value_one);
  test_expression(the_lline.value[2].the_expr, INT, &value_two);

  ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
  ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
  parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
  ASSERT_EQ(the_shape.type, RECTANGLE);
  test_expression(the_shape.values[0], VAR, (void *)"thickness");
  test_expression(the_shape.values[1], BIN_PLUS, NULL);
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

  ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
  ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
  ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
  test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
  parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
  ASSERT_EQ(the_shape_two.type, RECTANGLE);
  test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
  test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
  test_expression(the_shape_two.values[1].child[0], INT, &value_one);
  test_expression(the_shape_two.values[1].child[1], INT, &value_two);
  test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
  test_expression(the_shape_two.values[3], INT, &value_two);
  test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
  test_expression(the_shape_two.values[5], INT, &value_one);
  test_expression(the_shape_two.values[6], VAR, (void *)"width");
  test_expression(the_shape_two.values[7], INT, &value_one);
  test_expression(the_shape_two.values[8], VAR, (void *)"height");
  test_expression(the_shape_two.values[9], INT, &value_two);

  free_parsed_lline(the_lline);
}
