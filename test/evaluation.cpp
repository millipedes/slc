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
  // frees
  free_expression(head_int);
  free_expression(head_double);
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
  free_slc_value(value_result);
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
  free_slc_value(value_result);
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
      (pixel){DEFAULT_ELLIPSE_PIXEL_R, DEFAULT_ELLIPSE_PIXEL_G,
              DEFAULT_ELLIPSE_PIXEL_B, DEFAULT_ELLIPSE_PIXEL_A},
      DEFAULT_ELLIPSE_MAJOR_AXIS, DEFAULT_ELLIPSE_MINOR_AXIS, DEFAULT_ELLIPSE_THICKNESS},
      result.value.the_ellipse);
  free_parsed_shape(the_shape);
}

TEST(evaluation, array_test_0) {
  symbol_table st = {0};
  const char * input = "[1 < 3 == 2 > 1, -(((1 - - 2)))]";
  parsed_array the_parsed_array = {0};
  const char * remainder = parse_array(input, &the_parsed_array);
  ASSERT_EQ(remainder[0], '\0');
  slc_value the_value = evaluate_array(the_parsed_array, &st);
  bool value_one = true;
  int value_two = -3;
  test_expression(the_value.value.the_array[0].value[0].the_expr, BOOL, &value_one);
  test_expression(the_value.value.the_array[0].value[1].the_expr, INT, &value_two);
  free_parsed_array(the_parsed_array);
  free_slc_value(the_value);
}

TEST(evaluation, array_test_1) {
  symbol_table st = {0};
  const char * input = "[1 < 3 == 2 > 1, -(((1 - - 2))), rectangle(center_x 1.0, center_y 1.0, pixel_r 1, pixel_g 35, pixel_b 66)]";
  parsed_array the_parsed_array = {0};
  const char * remainder = parse_array(input, &the_parsed_array);
  ASSERT_EQ(remainder[0], '\0');
  slc_value the_value = evaluate_array(the_parsed_array, &st);
  bool value_one = true;
  int value_two = -3;
  test_expression(the_value.value.the_array[0].value[0].the_expr, BOOL, &value_one);
  test_expression(the_value.value.the_array[0].value[1].the_expr, INT, &value_two);
  validate_rectangle((rectangle){(coord_2d){1.0, 1.0}, (pixel){1, 35, 66, 255},
      DEFAULT_RECTANGLE_HEIGHT, DEFAULT_RECTANGLE_WIDTH, DEFAULT_RECTANGLE_THICKNESS},
      the_value.value.the_array[0].value[2].the_shape.value.the_rectangle);
  free_parsed_array(the_parsed_array);
  free_slc_value(the_value);
}

TEST(evaluation, array_test_2) {
  symbol_table st = {0};
  const char * input = "[[1 < 3 == 2 > 1], [-(((1 - - 2)))]]";
  parsed_array the_parsed_array = {0};
  const char * remainder = parse_array(input, &the_parsed_array);
  ASSERT_EQ(remainder[0], '\0');
  slc_value the_value = evaluate_array(the_parsed_array, &st);
  bool value_one = true;
  int value_two = -3;
  array sub_array_one = the_value.value.the_array[0].value[0].the_array[0];
  array sub_array_two = the_value.value.the_array[0].value[1].the_array[0];
  test_expression(sub_array_one.value[0].the_expr, BOOL, &value_one);
  test_expression(sub_array_two.value[0].the_expr, INT, &value_two);
  free_parsed_array(the_parsed_array);
  free_slc_value(the_value);
}

TEST(evaluation, symbol_table_test_0) {
  symbol_table st = {0};
  const char * the_input = "some_value = rectangle(thickness 1 + 2, center_x 2.0, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1);";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(the_input, &the_lline);
  evaluate_lline(the_lline, &st);
  expression symbol = {0};
  symbol.type = VAR;
  symbol.value.string_value = (char *)calloc(sizeof("some_value"), sizeof(char));
  strncpy(symbol.value.string_value, "some_value", sizeof("some_value"));
  slc_value the_value = find_symbol(st, symbol);
  ASSERT_EQ(the_value.type, SHAPE);
  ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
  validate_rectangle((rectangle){(coord_2d){2.0, 1.0},
      (pixel){1, 35, 66}, 2, 1, 3}, the_value.value.the_shape.value.the_rectangle);
  free_expression(symbol);
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
  expression symbol = {0};
  symbol.type = VAR;
  symbol.value.string_value = (char *)calloc(sizeof("some_value"), sizeof(char));
  strncpy(symbol.value.string_value, "some_value", sizeof("some_value"));
  slc_value the_value = find_symbol(st, symbol);
  ASSERT_EQ(the_value.type, SHAPE);
  ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
  validate_rectangle((rectangle){(coord_2d){3.0, 1.0},
      (pixel){1, 35, 66}, 2, 1, 5}, the_value.value.the_shape.value.the_rectangle);
  free_expression(symbol);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}

TEST(evaluation, symbol_table_test_2) {
  symbol_table st = {0};
  const char * setup_input = "x = [1 < 3 == 2 > 1, -(((1 - - 2)))];";
  const char * evaluation_input_one = "x[13 - 13]";
  // I just asked chatdpt for "a complicated expression which evaluated to 1"
  // lol, but good test
  const char * evaluation_input_two = "x[((((3 ^ 4 - 2 ^ 6) * (7 - 3) + 5 ^ 2) - (8 ^ 2 - 9)) - 17) / ((6 * 4 - 2 ^ 3) - 5)]";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(setup_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  expression accessor_one = {0};
  const char * evaluation_remainer_one = parse_precedence_1_expression(evaluation_input_one, &accessor_one);
  ASSERT_EQ(evaluation_remainer_one[0], '\0');
  expression accessor_two = {0};
  const char * evaluation_remainer_two = parse_precedence_1_expression(evaluation_input_two, &accessor_two);
  ASSERT_EQ(evaluation_remainer_two[0], '\0');
  bool value_one = true;
  int value_two = -3;
  evaluate_lline(the_lline, &st);
  test_expression(accessor_one, VAR, (void *)"x");
  slc_value the_value_one = find_symbol(st, accessor_one);
  ASSERT_EQ(the_value_one.type, EXPR);
  test_expression(the_value_one.value.the_expr, BOOL, &value_one);
  slc_value the_value_two = find_symbol(st, accessor_two);
  ASSERT_EQ(the_value_two.type, EXPR);
  test_expression(the_value_two.value.the_expr, INT, &value_two);
  free_expression(accessor_one);
  free_expression(accessor_two);
  free_parsed_lline(the_lline);
  free_slc_value(the_value_one);
  free_slc_value(the_value_two);
  free_symbol_table(st);
}

TEST(evaluation, symbol_table_test_3) {
  symbol_table st = {0};
  const char * setup_input = "x = [[1 < 3 == 2 > 1]];";
  const char * evaluation_input_one = "x[0][0]";
  parsed_lline the_lline = {0};
  const char * remainder = parse_assignment(setup_input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  expression accessor_one = {0};
  const char * evaluation_remainer_one = parse_precedence_1_expression(evaluation_input_one, &accessor_one);
  ASSERT_EQ(evaluation_remainer_one[0], '\0');
  bool value_one = true;
  evaluate_lline(the_lline, &st);
  test_expression(accessor_one, VAR, (void *)"x");
  slc_value the_value_one = find_symbol(st, accessor_one);
  ASSERT_EQ(the_value_one.type, EXPR);
  test_expression(the_value_one.value.the_expr, BOOL, &value_one);
  free_expression(accessor_one);
  free_parsed_lline(the_lline);
  free_slc_value(the_value_one);
  free_symbol_table(st);
}

TEST(evaluation, draw_test_0) {
  symbol_table st = {0};
  const char * input = "draw(rectangle());";
  parsed_lline the_lline = {0};
  const char * remainder = parse_draw_statement(input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  evaluate_lline(the_lline, &st);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}

TEST(evaluation, draw_test_1) {
  symbol_table st = {0};
  const char * input = "draw(ellipse());";
  parsed_lline the_lline = {0};
  const char * remainder = parse_draw_statement(input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  evaluate_lline(the_lline, &st);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}

TEST(evaluation, draw_test_2) {
  symbol_table st = {0};
  const char * input = "draw(line());";
  parsed_lline the_lline = {0};
  const char * remainder = parse_draw_statement(input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  evaluate_lline(the_lline, &st);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}

TEST(evaluation, lline_test_0) {
  symbol_table st = {0};
  const char * input = "draw(rectangle());";
  parsed_lline the_lline = {0};
  const char * remainder = parse_lline(input, &the_lline);
  ASSERT_EQ(remainder[0], '\0');
  evaluate_lline(the_lline, &st);
  free_parsed_lline(the_lline);
  free_symbol_table(st);
}
