#include "test_helper.h"

namespace slcp = SLCParsing;
namespace slce = SLCEvaluation;

TEST(evaluation, evaluate_expression_test_0) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::UnMinus);
  head_int.add_children(1);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(-1));
  // double
  auto head_double = slcp::Expr(slcp::OpType::UnMinus);
  head_double.add_children(1.0);
  auto result_double = slce::evaluate_expression(head_double, sts);
  test_expr(result_double, slcp::Expr(-1.0));
}

TEST(evaluation, evaluate_expression_test_1) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::BinPlus);
  head_int.add_children(1, 15);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(16));
  // double
  auto head_double = slcp::Expr(slcp::OpType::BinPlus);
  head_double.add_children(1.0, 15.0);
  auto result_double = slce::evaluate_expression(head_double, sts);
  test_expr(result_double, slcp::Expr(16.0));
  // std::string
  auto head_string = slcp::Expr(slcp::OpType::BinPlus);
  head_string.add_children("some ", "string");
  auto result_string = slce::evaluate_expression(head_string, sts);
  test_expr(result_string, slcp::Expr("some string"));
}

TEST(evaluation, evaluate_expression_test_2) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::BinMinus);
  head_int.add_children(1, 15);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(-14));
  // double
  auto head_double = slcp::Expr(slcp::OpType::BinMinus);
  head_double.add_children(1.0, 15.0);
  auto result_double = slce::evaluate_expression(head_double, sts);
  test_expr(result_double, slcp::Expr(-14.0));
}

TEST(evaluation, evaluate_expression_test_3) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::BinMult);
  head_int.add_children(2, 15);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(30));
  // double
  auto head_double = slcp::Expr(slcp::OpType::BinMult);
  head_double.add_children(2.0, 15.0);
  auto result_double = slce::evaluate_expression(head_double, sts);
  test_expr(result_double, slcp::Expr(30.0));
}

TEST(evaluation, evaluate_expression_test_4) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::BinDivide);
  head_int.add_children(2, 15);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(0));
  // double
  auto head_double = slcp::Expr(slcp::OpType::BinDivide);
  head_double.add_children(15, 2);
  auto result_double = slce::evaluate_expression(head_double, sts);
  test_expr(result_double, slcp::Expr(7.5));
}

TEST(evaluation, evaluate_expression_test_5) {
  auto sts = std::stack<slce::SymbolTable>();
  // int
  auto head_int = slcp::Expr(slcp::OpType::BinMod);
  head_int.add_children(15, 2);
  auto result_int = slce::evaluate_expression(head_int, sts);
  test_expr(result_int, slcp::Expr(1));
}

TEST(evaluation, evaluate_expression_test_6) {
  slcp::Expr expr;
  test_result_from_string(expr, "(((1 - - 2 * 3)))", 7);
}

TEST(evaluation, evaluate_expression_test_7) {
  slcp::Expr expr;
  test_result_from_string(expr, "2 ** 2 ** 3", 256);
}

TEST(evaluation, evaluate_expression_test_8) {
  slcp::Expr expr;
  test_result_from_string(expr, "(1.0 + 2.0) ** -(1.0 + 2.0)", pow(3.0, -3.0));
}

TEST(evaluation, evaluate_expression_test_9) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 == 2.0", false);
}

TEST(evaluation, evaluate_expression_test_10) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 != 2.0", true);
}

TEST(evaluation, evaluate_expression_test_11) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 >= 2.0", false);
}

TEST(evaluation, evaluate_expression_test_12) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 > 2.0", false);
}

TEST(evaluation, evaluate_expression_test_13) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 <= 2.0", true);
}

TEST(evaluation, evaluate_expression_test_14) {
  slcp::Expr expr;
  test_result_from_string(expr, "1.0 < 2.0", true);
}

TEST(evaluation, evaluate_expression_test_15) {
  slcp::Expr expr;
  test_result_from_string(expr, "true == false", false);
}

TEST(evaluation, evaluate_expression_test_16) {
  slcp::Expr expr;
  test_result_from_string(expr, "1 < 3 == 2 > 1", true);
}

TEST(evaluation, evaluate_expression_test_17) {
  slcp::Expr expr;
  test_result_from_string(expr, "\"some string\" == \"some string\"", true);
}

TEST(evaluation, evaluate_expression_test_18) {
  slcp::Expr expr;
  test_result_from_string(expr, "\"some other string\" == \"some string\"", false);
}

TEST(evaluation, evaluate_expression_test_19) {
  slcp::Expr expr;
  test_double_expr(expr, "sin(3.1415926 / 6.0)", 0.5);
}

TEST(evaluation, evaluate_expression_test_20) {
  slcp::Expr expr;
  test_double_expr(expr, "cos(3.1415926 / 3.0)", 0.5);
}

TEST(evaluation, evaluate_expression_test_21) {
  slcp::Expr expr;
  test_double_expr(expr, "tan(3.1415926 / 4.0)", 1.0);
}

TEST(evaluation, evaluate_expression_test_22) {
  slcp::Expr expr;
  test_double_expr(expr, "arcsin(0.5)", M_PI / 6.0);
}

TEST(evaluation, evaluate_expression_test_23) {
  slcp::Expr expr;
  test_double_expr(expr, "arccos(0.5)", M_PI / 3.0);
}

TEST(evaluation, evaluate_expression_test_24) {
  slcp::Expr expr;
  test_double_expr(expr, "arctan(1.0)", M_PI / 4.0);
}

TEST(evaluation, evaluate_expression_test_25) {
  slcp::Expr expr;
  test_double_expr(expr, "log(2.0)", 1.0);
}

TEST(evaluation, evaluate_expression_test_26) {
  slcp::Expr expr;
  test_double_expr(expr, "ln(0.5)", -0.6931);
}

TEST(evaluation, evaluate_expression_test_27) {
  slcp::Expr expr;
  test_result_from_string(expr, "-ln(0.5) + 1.0 * 2.0 < 3.0 && 1 == 1", true);
}

TEST(evaluation, evaluate_expression_test_28) {
  slcp::Expr expr;
  test_result_from_string(expr, "-ln(0.5) + 1.0 * 2.0 < 2.0 && 1 == 1", false);
}

TEST(evaluation, evaluate_expression_test_29) {
  slcp::Expr expr;
  test_result_from_string(expr, "1 <= 2 && 1 == 2 || 2 == 3", false);
}

TEST(evaluation, evaluate_expression_test_30) {
  slcp::Expr expr;
  test_result_from_string(expr, "1 <= 2 && 1 == 1 || 2 == 3", true);
}

TEST(evaluation, evaluate_expression_test_31) {
  slcp::Expr expr;
  test_result_from_string(expr, "1 <= 2 && 1 == 2 || 2 == 2", true);
}

TEST(evaluation, evaluate_expression_test_32) {
  slcp::Expr expr;
  test_result_from_string(expr, "!true || 9 == 9 && !(31 - 2 < 30)", false);
}

TEST(evaluation, evaluate_expression_test_33) {
  slcp::Expr expr;
  test_result_from_string(expr, "!true || 9 == 9 && (31 - 2 < 30)", true);
}

// TEST(evaluation, evaluate_shape_test_0) {
//   symbol_table st = {0};
//   const char * input = "rectangle(thickness 1 + 2, center_x 2.0, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1)";
//   parsed_shape the_shape = {0};
//   const char * remainder = parse_shape(input, &the_shape);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value value_result = evaluate_shape(the_shape, &st);
//   shape result = value_result.value.the_shape;
//   validate_rectangle((rectangle){(coord_2d){2.0, 1.0},
//       (pixel){1, 35, 66}, 2, 1, 3}, result.value.the_rectangle);
//   free_parsed_shape(the_shape);
// }
// 
// TEST(evaluation, evaluate_shape_test_1) {
//   symbol_table st = {0};
//   const char * input = "line(thickness 1 + 2, pixel_r 1, to_x 2.0, from_x 2.0, to_y 2.0, from_y 2.0 pixel_b 66, pixel_g 35)";
//   parsed_shape the_shape = {0};
//   const char * remainder = parse_shape(input, &the_shape);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value value_result = evaluate_shape(the_shape, &st);
//   shape result = value_result.value.the_shape;
//   validate_line((line){(coord_2d){2.0, 2.0},
//       (coord_2d){2.0, 2.0}, (pixel){1, 35, 66}, 3}, result.value.the_line);
//   free_parsed_shape(the_shape);
// }
// 
// TEST(evaluation, evaluate_shape_test_2) {
//   symbol_table st = {0};
//   const char * input = "ellipse(thickness 1 + 2, pixel_r 1, center_x 2.0, minor_axis 2, center_y 2.0, pixel_b 66, major_axis 3, pixel_g 35)";
//   parsed_shape the_shape = {0};
//   const char * remainder = parse_shape(input, &the_shape);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value value_result = evaluate_shape(the_shape, &st);
//   shape result = value_result.value.the_shape;
//   validate_ellipse((ellipse){(coord_2d){2.0, 2.0},
//       (pixel){1, 35, 66}, 3, 2, 3}, result.value.the_ellipse);
//   free_parsed_shape(the_shape);
// }
// 
// TEST(evaluation, evaluate_shape_test_3) {
//   symbol_table st = {0};
//   const char * input = "ellipse()";
//   parsed_shape the_shape = {0};
//   const char * remainder = parse_shape(input, &the_shape);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value value_result = evaluate_shape(the_shape, &st);
//   shape result = value_result.value.the_shape;
//   validate_ellipse((ellipse){(coord_2d){0.0, 0.0},
//       (pixel){DEFAULT_ELLIPSE_PIXEL_R, DEFAULT_ELLIPSE_PIXEL_G,
//               DEFAULT_ELLIPSE_PIXEL_B, DEFAULT_ELLIPSE_PIXEL_A},
//       DEFAULT_ELLIPSE_MAJOR_AXIS, DEFAULT_ELLIPSE_MINOR_AXIS, DEFAULT_ELLIPSE_THICKNESS},
//       result.value.the_ellipse);
//   free_parsed_shape(the_shape);
// }
// 
// TEST(evaluation, evaluate_shape_test_4) {
//   symbol_table st = {0};
//   const char * input = "canvas(pixel_r 1, pixel_b 66 - 66 + 66, pixel_g 35, pixel_a 255, width 1100, height 1200)";
//   parsed_shape the_shape = {0};
//   const char * remainder = parse_shape(input, &the_shape);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value value_result = evaluate_shape(the_shape, &st);
//   shape result = value_result.value.the_shape;
//   canvas truth = init_canvas(1200, 1100, 1, 35, 66, 255);
//   validate_canvas(truth, result.value.the_canvas);
//   free_canvas(truth);
//   free_parsed_shape(the_shape);
//   free_slc_value(value_result);
// }
// 
// TEST(evaluation, array_test_0) {
//   symbol_table st = {0};
//   const char * input = "[1 < 3 == 2 > 1, -(((1 - - 2)))]";
//   parsed_array the_parsed_array = {0};
//   const char * remainder = parse_array(input, &the_parsed_array);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value the_value = evaluate_array(the_parsed_array, &st);
//   bool value_one = true;
//   int value_two = -3;
//   test_expression(the_value.value.the_array[0].value[0].the_expr, BOOL, &value_one);
//   test_expression(the_value.value.the_array[0].value[1].the_expr, INT, &value_two);
//   free_parsed_array(the_parsed_array);
//   free_slc_value(the_value);
// }
// 
// TEST(evaluation, array_test_1) {
//   symbol_table st = {0};
//   const char * input = "[1 < 3 == 2 > 1, -(((1 - - 2))), rectangle(center_x 1.0, center_y 1.0, pixel_r 1, pixel_g 35, pixel_b 66)]";
//   parsed_array the_parsed_array = {0};
//   const char * remainder = parse_array(input, &the_parsed_array);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value the_value = evaluate_array(the_parsed_array, &st);
//   bool value_one = true;
//   int value_two = -3;
//   test_expression(the_value.value.the_array[0].value[0].the_expr, BOOL, &value_one);
//   test_expression(the_value.value.the_array[0].value[1].the_expr, INT, &value_two);
//   validate_rectangle((rectangle){(coord_2d){1.0, 1.0}, (pixel){1, 35, 66, 255},
//       DEFAULT_RECTANGLE_HEIGHT, DEFAULT_RECTANGLE_WIDTH, DEFAULT_RECTANGLE_THICKNESS},
//       the_value.value.the_array[0].value[2].the_shape.value.the_rectangle);
//   free_parsed_array(the_parsed_array);
//   free_slc_value(the_value);
// }
// 
// TEST(evaluation, array_test_2) {
//   symbol_table st = {0};
//   const char * input = "[[1 < 3 == 2 > 1], [-(((1 - - 2)))]]";
//   parsed_array the_parsed_array = {0};
//   const char * remainder = parse_array(input, &the_parsed_array);
//   ASSERT_EQ(remainder[0], '\0');
//   slc_value the_value = evaluate_array(the_parsed_array, &st);
//   bool value_one = true;
//   int value_two = -3;
//   array sub_array_one = the_value.value.the_array[0].value[0].the_array[0];
//   array sub_array_two = the_value.value.the_array[0].value[1].the_array[0];
//   test_expression(sub_array_one.value[0].the_expr, BOOL, &value_one);
//   test_expression(sub_array_two.value[0].the_expr, INT, &value_two);
//   free_parsed_array(the_parsed_array);
//   free_slc_value(the_value);
// }
// 
// TEST(evaluation, symbol_table_test_0) {
//   symbol_table st = {0};
//   const char * input = "some_value = rectangle(thickness 1 + 2, center_x 2.0, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1);";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(input, &the_lline);
//   evaluate_lline(the_lline, &st);
//   expression symbol = {0};
//   symbol.type = VAR;
//   symbol.value.string_value = (char *)calloc(sizeof("some_value"), sizeof(char));
//   strncpy(symbol.value.string_value, "some_value", sizeof("some_value"));
//   slc_value the_value = find_symbol(st, symbol);
//   ASSERT_EQ(the_value.type, SHAPE);
//   ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
//   validate_rectangle((rectangle){(coord_2d){2.0, 1.0},
//       (pixel){1, 35, 66}, 2, 1, 3}, the_value.value.the_shape.value.the_rectangle);
//   free_expression(symbol);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, symbol_table_test_1) {
//   symbol_table st = {0};
//   st = add_slc_value_to_table(st, "x", slc_value{expression{{.int_value = 5}, NULL, 0, INT}, EXPR});
//   st = add_slc_value_to_table(st, "y", slc_value{expression{{.double_value = 3.0}, NULL, 0, DOUBLE}, EXPR});
//   const char * input = "some_value = rectangle(thickness x, center_x y, pixel_b 66, center_y 1.0, width 1, pixel_g 35, height 2, pixel_r 1);";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(input, &the_lline);
//   evaluate_lline(the_lline, &st);
//   expression symbol = {0};
//   symbol.type = VAR;
//   symbol.value.string_value = (char *)calloc(sizeof("some_value"), sizeof(char));
//   strncpy(symbol.value.string_value, "some_value", sizeof("some_value"));
//   slc_value the_value = find_symbol(st, symbol);
//   ASSERT_EQ(the_value.type, SHAPE);
//   ASSERT_EQ(the_value.value.the_shape.type, RECTANGLE);
//   validate_rectangle((rectangle){(coord_2d){3.0, 1.0},
//       (pixel){1, 35, 66}, 2, 1, 5}, the_value.value.the_shape.value.the_rectangle);
//   free_expression(symbol);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, symbol_table_test_2) {
//   symbol_table st = {0};
//   const char * setup_input = "x = [1 < 3 == 2 > 1, -(((1 - - 2)))];";
//   const char * evaluation_input_one = "x[13 - 13]";
//   // I just asked chatdpt for "a complicated expression which evaluated to 1"
//   // lol, but good test
//   const char * evaluation_input_two = "x[((((3 ^ 4 - 2 ^ 6) * (7 - 3) + 5 ^ 2) - (8 ^ 2 - 9)) - 17) / ((6 * 4 - 2 ^ 3) - 5)]";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(setup_input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   expression accessor_one = {0};
//   const char * evaluation_remainer_one = parse_precedence_7_expr(evaluation_input_one, &accessor_one);
//   ASSERT_EQ(evaluation_remainer_one[0], '\0');
//   expression accessor_two = {0};
//   const char * evaluation_remainer_two = parse_precedence_7_expr(evaluation_input_two, &accessor_two);
//   ASSERT_EQ(evaluation_remainer_two[0], '\0');
//   bool value_one = true;
//   int value_two = -3;
//   evaluate_lline(the_lline, &st);
//   test_expression(accessor_one, VAR, (void *)"x");
//   slc_value the_value_one = find_symbol(st, accessor_one);
//   ASSERT_EQ(the_value_one.type, EXPR);
//   test_expression(the_value_one.value.the_expr, BOOL, &value_one);
//   slc_value the_value_two = find_symbol(st, accessor_two);
//   ASSERT_EQ(the_value_two.type, EXPR);
//   test_expression(the_value_two.value.the_expr, INT, &value_two);
//   free_expression(accessor_one);
//   free_expression(accessor_two);
//   free_parsed_lline(the_lline);
//   free_slc_value(the_value_one);
//   free_slc_value(the_value_two);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, symbol_table_test_3) {
//   symbol_table st = {0};
//   const char * setup_input = "x = [[1 < 3 == 2 > 1]];";
//   const char * evaluation_input_one = "x[0][0]";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(setup_input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   expression accessor_one = {0};
//   const char * evaluation_remainer_one = parse_precedence_7_expr(evaluation_input_one, &accessor_one);
//   ASSERT_EQ(evaluation_remainer_one[0], '\0');
//   bool value_one = true;
//   evaluate_lline(the_lline, &st);
//   test_expression(accessor_one, VAR, (void *)"x");
//   slc_value the_value_one = find_symbol(st, accessor_one);
//   ASSERT_EQ(the_value_one.type, EXPR);
//   test_expression(the_value_one.value.the_expr, BOOL, &value_one);
//   free_expression(accessor_one);
//   free_parsed_lline(the_lline);
//   free_slc_value(the_value_one);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_0) {
//   symbol_table st = {0};
//   const char * input = "draw(rectangle());";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_1) {
//   symbol_table st = {0};
//   const char * input = "draw(ellipse());";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_2) {
//   symbol_table st = {0};
//   const char * input = "draw(line());";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_3) {
//   symbol_table st = {0};
//   const char * input = "draw(canvas());";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_4) {
//   symbol_table st = {0};
//   const char * input = "draw(canvas()) -> \"test.png\";";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, draw_test_5) {
//   symbol_table st = {0};
//   const char * input = "the_canvas = canvas(height 1000, width 1200);";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   the_lline = {0};
// 
//   input = "the_rect = rectangle(thickness 20, center_x 200.0, pixel_b 66, center_y 100.0, width 50, pixel_g 35, height 50, pixel_r 1);";
//   remainder = parse_assignment(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   the_lline = {0};
// 
//   input = "draw(the_rect) -> the_canvas;";
//   remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   the_lline = {0};
// 
//   input = "draw(the_canvas) -> \"rect_test.png\";";
//   remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   the_lline = {0};
// 
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, lline_test_0) {
//   symbol_table st = {0};
//   const char * input = "draw(rectangle());";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_lline(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, lline_test_1) {
//   symbol_table st = {0};
//   const char * input = "x = 18;"
//   "if 1 < 3 == 2 > 1 {"
//   "  x = 19;"
//   "}";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_lline(input, &the_lline);
//   evaluate_lline(the_lline, &st);
//   free_parsed_lline(the_lline);
//   the_lline = {0};
// 
//   remainder = parse_lline(remainder, &the_lline);
//   evaluate_lline(the_lline, &st);
//   ASSERT_EQ(remainder[0], '\0');
// 
//   int value_one = 19;
//   expression symbol = {0};
//   symbol.type = VAR;
//   symbol.value.string_value = (char *)calloc(sizeof("x"), sizeof(char));
//   strncpy(symbol.value.string_value, "x", sizeof("x"));
//   test_expression(find_symbol(st, symbol).value.the_expr, INT, &value_one);
//   free_expression(symbol);
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, lline_test_2) {
//   symbol_table st = {0};
//   const char * input = "for i in range(3) {"
//   "  draw(rectangle(center_x i * 35, center_y i * 35));"
//   "}";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_lline(input, &the_lline);
//   evaluate_lline(the_lline, &st);
// 
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
// 
// TEST(evaluation, lline_test_3) {
//   symbol_table st = {0};
//   const char * input = "for i in range(3, 7) {"
//   "  draw(rectangle(center_x i * 35, center_y i * 35));"
//   "}";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_lline(input, &the_lline);
//   evaluate_lline(the_lline, &st);
// 
//   free_parsed_lline(the_lline);
//   free_symbol_table(st);
// }
