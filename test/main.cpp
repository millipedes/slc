#include <gtest/gtest.h>

#include "parsing/parsing.h"

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
    case UN_MINUS:
      ASSERT_EQ(the_expression.qty_children, 1);
      break;
    case BIN_PLUS:
    case BIN_MINUS:
    case BIN_MULT:
    case BIN_DIVIDE:
    case BIN_MOD:
      ASSERT_EQ(the_expression.qty_children, 2);
      break;
  }
}

TEST(parsing, variable_name_test_0) {
  const char * the_input = "some_string = 123";
  expression the_expression = {0};
  const char * remainder = parse_variable_name(the_input, &the_expression);
  ASSERT_TRUE(!strncmp(" = 123", remainder, MAX_STR));
  test_expression(the_expression, VAR, (void *)"some_string");
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
}

TEST(parsing, expression_test_0) {
  const char * the_input = "-123";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value = 123;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], INT, &value);
}

TEST(parsing, expression_test_1) {
  const char * the_input = "-1e-2";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  double value = 0.01;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], DOUBLE, &value);
}

TEST(parsing, expression_test_2) {
  const char * the_input = "\"hello world\"";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  test_expression(the_expression, STRING, (void *)"\"hello world\"");
}

TEST(parsing, expression_test_3) {
  const char * the_input = "\"hello world";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, expression_test_4) {
  const char * the_input = "1 + 2";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_PLUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], INT, &value_two);
}

TEST(parsing, expression_test_5) {
  const char * the_input = "1 + 2 * 3";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(the_expression, BIN_PLUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], BIN_MULT, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
  test_expression(the_expression.child[1].child[1], INT, &value_three);
}

TEST(parsing, expression_test_6) {
  const char * the_input = "(1 + 2) * 3";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  int value_three = 3;
  test_expression(the_expression, BIN_MULT, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
  test_expression(the_expression.child[1], INT, &value_three);
}

TEST(parsing, expression_test_7) {
  const char * the_input = "-(1 + 2)";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, UN_MINUS, NULL);
  test_expression(the_expression.child[0], BIN_PLUS, NULL);
  test_expression(the_expression.child[0].child[0], INT, &value_one);
  test_expression(the_expression.child[0].child[1], INT, &value_two);
}

TEST(parsing, expression_test_8) {
  const char * the_input = "(((((1 - - 2)))))";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  int value_one = 1;
  int value_two = 2;
  test_expression(the_expression, BIN_MINUS, NULL);
  test_expression(the_expression.child[0], INT, &value_one);
  test_expression(the_expression.child[1], UN_MINUS, NULL);
  test_expression(the_expression.child[1].child[0], INT, &value_two);
}

int main(int argc, char ** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
