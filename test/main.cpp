#include <gtest/gtest.h>

#include "parsing/parsing.h"

TEST(parsing, variable_name_test_0) {
  const char * the_input = "some_string = 123";
  expression the_expression = {0};
  const char * remainder = parse_variable_name(the_input, &the_expression);
  ASSERT_TRUE(!strncmp(" = 123", remainder, MAX_STR));
  ASSERT_TRUE(!strncmp("some_string", the_expression.value.string_value, MAX_STR));
}

TEST(parsing, number_test_0) {
  const char * the_input = "123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.int_value == 123);
}

TEST(parsing, number_test_1) {
  const char * the_input = "-123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.int_value == -123);
}

TEST(parsing, number_test_2) {
  const char * the_input = "123.123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.double_value == 123.123);
}

TEST(parsing, number_test_3) {
  const char * the_input = "-123.123";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.double_value == -123.123);
}

TEST(parsing, number_test_4) {
  const char * the_input = "1e-2";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.double_value == 0.01);
}

TEST(parsing, number_test_5) {
  const char * the_input = "-1e-2";
  expression the_expression = {0};
  const char * remainder = parse_number(the_input, &the_expression);
  ASSERT_TRUE(remainder[0] == '\0');
  ASSERT_TRUE(the_expression.value.double_value == -0.01);
}

int main(int argc, char ** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
