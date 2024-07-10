#include "evaluation/evaluation.h"
#include "test_helper.h"

TEST(evaluation, evaluation_test_0) {
  // int
  expression head_int = {0};
  head_int.type = UN_MINUS;
  head_int.child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 1;
  expression value_int = {0};
  value_int.type = INT;
  value_int.value.int_value = 1;
  head_int.child[0] = value_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = -1;
  test_expression(result_int, INT, &value_one_int);
  // double
  expression head_double = {0};
  head_double.type = UN_MINUS;
  head_double.child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  head_double.qty_children = 1;
  expression value_double = {0};
  value_double.type = DOUBLE;
  value_double.value.double_value = 1.0;
  head_double.child[0] = value_double;
  expression result_double = evaluate_expression(head_double);
  double value_one_dobule = -1.0;
  test_expression(result_double, DOUBLE, &value_one_dobule);
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluation_test_1) {
  // int
  expression head_int = {0};
  head_int.type = BIN_PLUS;
  head_int.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 2;
  expression left_int = {0};
  left_int.type = INT;
  left_int.value.int_value = 1;
  expression right_int = {0};
  right_int.type = INT;
  right_int.value.int_value = 15;
  head_int.child[0] = left_int;
  head_int.child[1] = right_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = 16;
  test_expression(result_int, INT, &value_one_int);
  // double
  expression head_double = {0};
  head_double.type = BIN_PLUS;
  head_double.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_double.qty_children = 2;
  expression left_double = {0};
  left_double.type = DOUBLE;
  left_double.value.double_value = 1.0;
  expression right_double = {0};
  right_double.type = DOUBLE;
  right_double.value.double_value = 15.0;
  head_double.child[0] = left_double;
  head_double.child[1] = right_double;
  expression result_double = evaluate_expression(head_double);
  double value_one_double = 16.0;
  test_expression(result_double, DOUBLE, &value_one_double);
  // string
  expression head_string = {0};
  head_string.type = BIN_PLUS;
  head_string.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_string.qty_children = 2;
  expression left_string = {0};
  left_string.type = STRING;
  left_string.value.string_value = (char *)calloc(6, sizeof(char));
  strncpy(left_string.value.string_value, "some ", 5);
  left_string.value.string_value[5] = '\0';
  expression right_string = {0};
  right_string.type = STRING;
  right_string.value.string_value = (char *)calloc(7, sizeof(char));
  strncpy(right_string.value.string_value, "string", 6);
  right_string.value.string_value[6] = '\0';
  head_string.child[0] = left_string;
  head_string.child[1] = right_string;
  expression result_string = evaluate_expression(head_string);
  test_expression(result_string, STRING, (void *)"some string");
  // frees
  free_expression(head_int);
  free_expression(head_double);
  free_expression(head_string);
  free_expression(result_string);
}

TEST(evaluation, evaluation_test_2) {
  // int
  expression head_int = {0};
  head_int.type = BIN_MINUS;
  head_int.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 2;
  expression left_int = {0};
  left_int.type = INT;
  left_int.value.int_value = 1;
  expression right_int = {0};
  right_int.type = INT;
  right_int.value.int_value = 15;
  head_int.child[0] = left_int;
  head_int.child[1] = right_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = -14;
  test_expression(result_int, INT, &value_one_int);
  // double
  expression head_double = {0};
  head_double.type = BIN_MINUS;
  head_double.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_double.qty_children = 2;
  expression left_double = {0};
  left_double.type = DOUBLE;
  left_double.value.double_value = 1.0;
  expression right_double = {0};
  right_double.type = DOUBLE;
  right_double.value.double_value = 15.0;
  head_double.child[0] = left_double;
  head_double.child[1] = right_double;
  expression result_double = evaluate_expression(head_double);
  double value_one_double = -14.0;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluation_test_3) {
  // int
  expression head_int = {0};
  head_int.type = BIN_MULT;
  head_int.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 2;
  expression left_int = {0};
  left_int.type = INT;
  left_int.value.int_value = 2;
  expression right_int = {0};
  right_int.type = INT;
  right_int.value.int_value = 15;
  head_int.child[0] = left_int;
  head_int.child[1] = right_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = 30;
  test_expression(result_int, INT, &value_one_int);
  // double
  expression head_double = {0};
  head_double.type = BIN_MULT;
  head_double.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_double.qty_children = 2;
  expression left_double = {0};
  left_double.type = DOUBLE;
  left_double.value.double_value = 2.0;
  expression right_double = {0};
  right_double.type = DOUBLE;
  right_double.value.double_value = 15.0;
  head_double.child[0] = left_double;
  head_double.child[1] = right_double;
  expression result_double = evaluate_expression(head_double);
  double value_one_double = 30.0;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluation_test_4) {
  // int
  expression head_int = {0};
  head_int.type = BIN_DIVIDE;
  head_int.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 2;
  expression left_int = {0};
  left_int.type = INT;
  left_int.value.int_value = 2;
  expression right_int = {0};
  right_int.type = INT;
  right_int.value.int_value = 15;
  head_int.child[0] = left_int;
  head_int.child[1] = right_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = 0;
  test_expression(result_int, INT, &value_one_int);
  // double
  expression head_double = {0};
  head_double.type = BIN_DIVIDE;
  head_double.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_double.qty_children = 2;
  expression left_double = {0};
  left_double.type = DOUBLE;
  left_double.value.double_value = 15.0;
  expression right_double = {0};
  right_double.type = DOUBLE;
  right_double.value.double_value = 2.0;
  head_double.child[0] = left_double;
  head_double.child[1] = right_double;
  expression result_double = evaluate_expression(head_double);
  double value_one_double = 7.5;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluation_test_5) {
  // int
  expression head_int = {0};
  head_int.type = BIN_MOD;
  head_int.child = (expression *)calloc(2, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 2;
  expression left_int = {0};
  left_int.type = INT;
  left_int.value.int_value = 15;
  expression right_int = {0};
  right_int.type = INT;
  right_int.value.int_value = 2;
  head_int.child[0] = left_int;
  head_int.child[1] = right_int;
  expression result_int = evaluate_expression(head_int);
  int value_one_int = 1;
  test_expression(result_int, INT, &value_one_int);
  // frees
  free_expression(head_int);
}

TEST(evaluation, evaluation_test_6) {
  const char * the_input = "(((1 - - 2 * 3)))";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  expression result = evaluate_expression(the_expression);
  int value_one = 7;
  test_expression(result, INT, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluation_test_7) {
  const char * the_input = "2 ^ 2 ^ 3";
  expression the_expression = {0};
  const char * remainder = parse_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  expression result = evaluate_expression(the_expression);
  int value_one = 256;
  test_expression(result, INT, &value_one);
  free_expression(the_expression);
  free_expression(result);
}
