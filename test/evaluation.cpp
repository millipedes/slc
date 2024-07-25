#include "test_helper.h"

TEST(evaluation, evaluate_expression_test_0) {
  symbol_table st = {0};
  // int
  expression head_int = {0};
  head_int.type = UN_MINUS;
  head_int.child = (expression *)calloc(1, sizeof(struct EXPRESSION_T));
  head_int.qty_children = 1;
  expression value_int = {0};
  value_int.type = INT;
  value_int.value.int_value = 1;
  head_int.child[0] = value_int;
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
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
  slc_value slc_value_double = evaluate_expression(head_double, &st);
  expression result_double = slc_value_double.value.the_expr;
  double value_one_dobule = -1.0;
  test_expression(result_double, DOUBLE, &value_one_dobule);
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluate_expression_test_1) {
  symbol_table st = {0};
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
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
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
  slc_value slc_value_double = evaluate_expression(head_double, &st);
  expression result_double = slc_value_double.value.the_expr;
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
  slc_value slc_value_string = evaluate_expression(head_string, &st);
  expression result_string = slc_value_string.value.the_expr;
  test_expression(result_string, STRING, (void *)"some string");
  // frees
  free_expression(head_int);
  free_expression(head_double);
  free_expression(head_string);
  free_expression(result_string);
}

TEST(evaluation, evaluate_expression_test_2) {
  symbol_table st = {0};
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
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
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
  slc_value slc_value_double = evaluate_expression(head_double, &st);
  expression result_double = slc_value_double.value.the_expr;
  double value_one_double = -14.0;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluate_expression_test_3) {
  symbol_table st = {0};
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
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
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
  slc_value slc_value_double = evaluate_expression(head_double, &st);
 expression result_double = slc_value_double.value.the_expr;
  double value_one_double = 30.0;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluate_expression_test_4) {
  symbol_table st = {0};
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
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
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
  slc_value slc_value_double = evaluate_expression(head_double, &st);
 expression result_double = slc_value_double.value.the_expr;
  double value_one_double = 7.5;
  test_expression(result_double, DOUBLE, &value_one_double);
  // frees
  free_expression(head_int);
  free_expression(head_double);
}

TEST(evaluation, evaluate_expression_test_5) {
  symbol_table st = {0};
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
  slc_value slc_value_int = evaluate_expression(head_int, &st);
  expression result_int = slc_value_int.value.the_expr;
  int value_one_int = 1;
  test_expression(result_int, INT, &value_one_int);
  // frees
  free_expression(head_int);
}

TEST(evaluation, evaluate_expression_test_6) {
  symbol_table st = {0};
  const char * the_input = "(((1 - - 2 * 3)))";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  int value_one = 7;
  test_expression(result, INT, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_7) {
  symbol_table st = {0};
  const char * the_input = "2 ^ 2 ^ 3";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  int value_one = 256;
  test_expression(result, INT, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_8) {
  symbol_table st = {0};
  const char * the_input = "(1.0 + 2.0) ^ -(1.0 + 2.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = pow(3.0, -3.0);
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_9) {
  symbol_table st = {0};
  const char * the_input = "1.0 == 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = false;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_10) {
  symbol_table st = {0};
  const char * the_input = "1.0 != 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = true;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_11) {
  symbol_table st = {0};
  const char * the_input = "1.0 >= 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = false;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_12) {
  symbol_table st = {0};
  const char * the_input = "1.0 > 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = false;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_13) {
  symbol_table st = {0};
  const char * the_input = "1.0 <= 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = true;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_14) {
  symbol_table st = {0};
  const char * the_input = "1.0 < 2.0";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = true;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_15) {
  symbol_table st = {0};
  const char * the_input = "false == true";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = false;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_16) {
  symbol_table st = {0};
  const char * the_input = "1 < 3 == 2 > 1";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = true;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_17) {
  symbol_table st = {0};
  const char * the_input = "\"some string\" == \"some string\"";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = true;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_18) {
  symbol_table st = {0};
  const char * the_input = "\"some string\" == \"some other string\"";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  bool value_one = false;
  test_expression(result, BOOL, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_19) {
  symbol_table st = {0};
  const char * the_input = "sin(3.1415926 / 6.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = 0.5;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_20) {
  symbol_table st = {0};
  const char * the_input = "cos(3.1415926 / 3.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = 0.5;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_21) {
  symbol_table st = {0};
  const char * the_input = "tan(3.1415926 / 4.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = 1.0;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_22) {
  symbol_table st = {0};
  const char * the_input = "arcsin(0.5)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = M_PI / 6.0;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_23) {
  symbol_table st = {0};
  const char * the_input = "arccos(0.5)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = M_PI / 3.0;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_24) {
  symbol_table st = {0};
  const char * the_input = "arctan(1.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = M_PI / 4.0;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_25) {
  symbol_table st = {0};
  const char * the_input = "log(2.0)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = 1.0;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_expression_test_26) {
  symbol_table st = {0};
  const char * the_input = "ln(0.5)";
  expression the_expression = {0};
  const char * remainder = parse_precedence_1_expression(the_input, &the_expression);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_expression(the_expression, &st);
  expression result = value_result.value.the_expr;
  double value_one = -0.6931;
  test_expression(result, DOUBLE, &value_one);
  free_expression(the_expression);
  free_expression(result);
}

TEST(evaluation, evaluate_shape_test_0) {
  symbol_table st = {0};
  const char * the_input = "rectangle(thickness 1 + 2, center_x 2.0, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1)";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_shape(the_shape, &st);
  shape result = value_result.value.the_shape;
  validate_rectangle((rectangle){(coord_2d){2.0, 1.0},
      (pixel){1, 35, 66}, 2, 1, 3}, result.value.the_rectangle);
  free_parsed_shape(the_shape);
}

TEST(evaluation, evaluate_shape_test_1) {
  symbol_table st = {0};
  const char * the_input = "line(thickness 1 + 2, pixel_r 1, to_x 2.0, from_x 2.0, to_y 2.0, from_y 2.0 pixel_b 66, pixel_g 35)";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_shape(the_shape, &st);
  shape result = value_result.value.the_shape;
  validate_line((line){(coord_2d){2.0, 2.0},
      (coord_2d){2.0, 2.0}, (pixel){1, 35, 66}, 3}, result.value.the_line);
  free_parsed_shape(the_shape);
}

TEST(evaluation, evaluate_shape_test_2) {
  symbol_table st = {0};
  const char * the_input = "ellipse(thickness 1 + 2, pixel_r 1, center_x 2.0, minor_axis 2, center_y 2.0, pixel_b 66, major_axis 3, pixel_g 35)";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_shape(the_shape, &st);
  shape result = value_result.value.the_shape;
  validate_ellipse((ellipse){(coord_2d){2.0, 2.0},
      (pixel){1, 35, 66}, 3, 2, 3}, result.value.the_ellipse);
  free_parsed_shape(the_shape);
}

TEST(evaluation, evaluate_shape_test_3) {
  symbol_table st = {0};
  const char * the_input = "ellipse()";
  parsed_shape the_shape = {0};
  const char * remainder = parse_shape(the_input, &the_shape);
  ASSERT_EQ(remainder[0], '\0');
  slc_value value_result = evaluate_shape(the_shape, &st);
  shape result = value_result.value.the_shape;
  validate_ellipse((ellipse){(coord_2d){0.0, 0.0},
      (pixel){0, 0, 0}, 15, 15, 10}, result.value.the_ellipse);
  free_parsed_shape(the_shape);
}

TEST(evaluation, symbol_table_test_0) {
  symbol_table st = {0};
  const char * the_input = "some_value = rectangle(thickness 1 + 2, center_x 2.0, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1);";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  evaluate_lline(the_lline, &st);
  slc_value the_value = find_symbol(st, "some_value");
  ASSERT_EQ(the_value.type, SHAPE);
  ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
  validate_rectangle((rectangle){(coord_2d){2.0, 1.0},
      (pixel){1, 35, 66}, 2, 1, 3}, the_value.value.the_shape.value.the_rectangle);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}

TEST(evaluation, symbol_table_test_1) {
  symbol_table st = {0};
  st = add_slc_value_to_table(st, "x", slc_value{expression{{.int_value = 5}, NULL, 0, INT}, EXPR});
  st = add_slc_value_to_table(st, "y", slc_value{expression{{.double_value = 3.0}, NULL, 0, DOUBLE}, EXPR});
  const char * the_input = "some_value = rectangle(thickness x, center_x y, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1);";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  evaluate_lline(the_lline, &st);
  slc_value the_value = find_symbol(st, "some_value");
  ASSERT_EQ(the_value.type, SHAPE);
  ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
  validate_rectangle((rectangle){(coord_2d){3.0, 1.0},
      (pixel){1, 35, 66}, 2, 1, 5}, the_value.value.the_shape.value.the_rectangle);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}
