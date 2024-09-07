#include "test_helper.h"

namespace slcp = SLCParsing;

TEST(parsing, variable_name_test_0) {
  const char * input = "some_string";
  slcp::Expr expr;
  auto remainder = slcp::parse_variable_name(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(slcp::Expr::Variable{"some_string"}));
}

TEST(parsing, number_test_0) {
  const char * input = "123";
  slcp::Expr expr;
  auto remainder = slcp::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(123));
}

TEST(parsing, number_test_1) {
  const char * input = "123.123";
  slcp::Expr expr;
  auto remainder = slcp::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(123.123));
}

TEST(parsing, number_test_2) {
  const char * input = "1e-2";
  slcp::Expr expr;
  auto remainder = slcp::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(0.01));
}

TEST(parsing, number_test_3) {
  const char * input = "1E-2";
  slcp::Expr expr;
  auto remainder = slcp::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(0.01));
}

TEST(parsing, string_test_0) {
  const char * input = "\"hello world\"";
  slcp::Expr expr;
  auto remainder = slcp::parse_string(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr("hello world"));
}

TEST(parsing, string_test_1) {
  const char * input = "\"hello world";
  slcp::Expr expr;
  auto remainder = parse_string(input, expr);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, word_test_0) {
  const char * input = ".\\";
  auto remainder = slcp::parse_word(input, ".\\");
  ASSERT_EQ(remainder[0], '\0');
}

TEST(parsing, factor_test_0) {
  const char * input = "(((((-1e-2)))))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_1_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::UnMinus);
  result.add_children(0.01);
  test_expr(expr, result);
}

TEST(parsing, factor_test_1) {
  const char * input = "-(((((-1e-2)))))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_1_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::UnMinus);
  result_child.add_children(0.01);
  auto result = slcp::Expr(slcp::OpType::UnMinus);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, term_test_0) {
  const char * input = "1e-2 * 1e-2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinMult);
  result.add_children(0.01, 0.01);
  test_expr(expr, result);
}

TEST(parsing, term_test_1) {
  const char * input = "1e-2 * 1e-2 * 1e-2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinMult);
  result_child.add_children(0.01, 0.01);
  auto result = slcp::Expr(slcp::OpType::BinMult);
  result.add_children(0.01, result_child);
  test_expr(expr, result);
}

TEST(parsing, term_test_2) {
  const char * input = "1 / 2 % 3";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinMod);
  result_child.add_children(2, 3);
  auto result = slcp::Expr(slcp::OpType::BinDivide);
  result.add_children(1, result_child);
  test_expr(expr, result);
}

TEST(parsing, term_test_3) {
  const char * input = "\"some string\" / -1e-2 % var_name";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_child = slcp::Expr(slcp::OpType::UnMinus);
  result_child_child.add_children(0.01);
  auto result_child = slcp::Expr(slcp::OpType::BinMod);
  result_child.add_children(result_child_child, slcp::Expr::Variable{"var_name"});
  auto result = slcp::Expr(slcp::OpType::BinDivide);
  result.add_children("some string", result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_0) {
  const char * input = "-123";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::UnMinus);
  result.add_children(123);
  test_expr(expr, result);
}

TEST(parsing, expression_test_1) {
  const char * input = "-1e-2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::UnMinus);
  result.add_children(0.01);
  test_expr(expr, result);
}

TEST(parsing, expression_test_2) {
  const char * input = "\"hello world\"";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr("hello world"));
}

TEST(parsing, expression_test_3) {
  const char * input = "\"hello world";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, expression_test_4) {
  const char * input = "1 + 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinPlus);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_5) {
  const char * input = "1 + 2 * 3";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinMult);
  result_child.add_children(2, 3);
  auto result = slcp::Expr(slcp::OpType::BinPlus);
  result.add_children(1, result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_6) {
  const char * input = "(1 + 2) * 3";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::BinMult);
  result.add_children(result_child, 3);
  test_expr(expr, result);
}

TEST(parsing, expression_test_7) {
  const char * input = "-(1 + 2)";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::UnMinus);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_8) {
  const char * input = "(((((1 - - 2)))))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::UnMinus);
  result_child.add_children(2);
  auto result = slcp::Expr(slcp::OpType::BinMinus);
  result.add_children(1, result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_9) {
  const char * input = "1 ^ 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinPow);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_10) {
  const char * input = "(1 + 2) ^ -(1 + 2)";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_one = slcp::Expr(slcp::OpType::BinPlus);
  result_child_one.add_children(1, 2);
  auto result_child_two_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child_two_child.add_children(1, 2);
  auto result_child_two = slcp::Expr(slcp::OpType::UnMinus);
  result_child_two.add_children(result_child_two_child);
  auto result = slcp::Expr(slcp::OpType::BinPow);
  result.add_children(result_child_one, result_child_two);
  test_expr(expr, result);
}

TEST(parsing, expression_test_11) {
  const char * input = "1 == 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinEq);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_12) {
  const char * input = "1 != 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinNeq);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_13) {
  const char * input = "1 >= 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinGeq);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_14) {
  const char * input = "1 > 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinGt);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_15) {
  const char * input = "1 <= 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinLeq);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_16) {
  const char * input = "1 < 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slcp::Expr(slcp::OpType::BinLt);
  result.add_children(1, 2);
  test_expr(expr, result);
}

TEST(parsing, expression_test_17) {
  const char * input = "true";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(true));
}

TEST(parsing, expression_test_18) {
  const char * input = "false";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, slcp::Expr(false));
}

TEST(parsing, expression_test_19) {
  const char * input = "sin((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::Sin);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_20) {
  const char * input = "cos((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::Cos);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_21) {
  const char * input = "tan((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::Tan);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_22) {
  const char * input = "arcsin((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::ArcSin);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_23) {
  const char * input = "arccos((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::ArcCos);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_24) {
  const char * input = "arctan((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::ArcTan);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_25) {
  const char * input = "log((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::Log);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_26) {
  const char * input = "ln((1 + 2))";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::BinPlus);
  result_child.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::Ln);
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_27) {
  const char * input = "x[0]";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child = slcp::Expr(slcp::OpType::ArrayAccessor);
  result_child.add_children(0);
  auto result = slcp::Expr(slcp::Expr::Variable{"x"});
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_28) {
  const char * input = "x[9 * 1][1 + 2]";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_child_one = slcp::Expr(slcp::OpType::BinMult);
  result_child_child_one.add_children(9, 1);
  auto result_child_child_two = slcp::Expr(slcp::OpType::BinPlus);
  result_child_child_two.add_children(1, 2);
  auto result_child = slcp::Expr(slcp::OpType::ArrayAccessor);
  result_child.add_children(result_child_child_one, result_child_child_two);
  auto result = slcp::Expr(slcp::Expr::Variable{"x"});
  result.add_children(result_child);
  test_expr(expr, result);
}

TEST(parsing, expression_test_29) {
  const char * input = "1 <= 2 && 1 == 2";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_one = slcp::Expr(slcp::OpType::BinLeq);
  result_child_one.add_children(1, 2);
  auto result_child_two = slcp::Expr(slcp::OpType::BinEq);
  result_child_two.add_children(1, 2);
  auto result = slcp::Expr(slcp::OpType::BinBoolAnd);
  result.add_children(result_child_one, result_child_two);
  test_expr(expr, result);
}

TEST(parsing, expression_test_30) {
  const char * input = "-ln(0.5) + 1.0 * 2.0";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_child_one = slcp::Expr(slcp::OpType::Ln);
  result_child_child_one.add_children(0.5);
  auto result_child_one = slcp::Expr(slcp::OpType::UnMinus);
  result_child_one.add_children(result_child_child_one);
  auto result_child_two = slcp::Expr(slcp::OpType::BinMult);
  result_child_two.add_children(1.0, 2.0);
  auto result = slcp::Expr(slcp::OpType::BinPlus);
  result.add_children(result_child_one, result_child_two);
  test_expr(expr, result);
}

TEST(parsing, expression_test_31) {
  const char * input = "1 <= 2 && 1 == 2 || 2 == 3";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_child_one = slcp::Expr(slcp::OpType::BinLeq);
  result_child_child_one.add_children(1, 2);
  auto result_child_child_two = slcp::Expr(slcp::OpType::BinEq);
  result_child_child_two.add_children(1, 2);
  auto result_child_one = slcp::Expr(slcp::OpType::BinBoolAnd);
  result_child_one.add_children(result_child_child_one, result_child_child_two);
  auto result_child_two = slcp::Expr(slcp::OpType::BinEq);
  result_child_two.add_children(2, 3);
  auto result = slcp::Expr(slcp::OpType::BinBoolOr);
  result.add_children(result_child_one, result_child_two);
  test_expr(expr, result);
}

TEST(parsing, expression_test_32) {
  const char * input = "!-ln(0.5) + 1.0 * 2.0";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result_child_child_child_one = slcp::Expr(slcp::OpType::Ln);
  result_child_child_child_one.add_children(0.5);
  auto result_child_child_one = slcp::Expr(slcp::OpType::UnMinus);
  result_child_child_one.add_children(result_child_child_child_one);
  auto result_child_one = slcp::Expr(slcp::OpType::BoolNot);
  result_child_one.add_children(result_child_child_one);
  auto result_child_two = slcp::Expr(slcp::OpType::BinMult);
  result_child_two.add_children(1.0, 2.0);
  auto result = slcp::Expr(slcp::OpType::BinPlus);
  result.add_children(result_child_one, result_child_two);
  test_expr(expr, result);
}

TEST(parsing, shape_test_0) {
  const char * input = "rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto thickness_expr = slcp::Expr(slcp::OpType::BinPlus);
  thickness_expr.add_children(1, 2);
  slcp::Expr values = slcp::Expr(slcp::Expr::Shape{
    slcp::Exprs{
    slcp::Expr(slcp::Expr::Variable{"rectangle"}),
    slcp::Expr(slcp::Expr::Variable{"thickness"}), thickness_expr,
    slcp::Expr(slcp::Expr::Variable{"center_x"}), slcp::Expr(2),
    slcp::Expr(slcp::Expr::Variable{"center_y"}), slcp::Expr(1),
    slcp::Expr(slcp::Expr::Variable{"width"}), slcp::Expr(1),
    slcp::Expr(slcp::Expr::Variable{"height"}), slcp::Expr(2)}});
  test_expr(expr, values);
}

TEST(parsing, shape_test_1) {
  const char * input = "canvas(width 1, height 2)";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  slcp::Expr values = slcp::Expr(slcp::Expr::Shape{
    slcp::Exprs{ 
    slcp::Expr(slcp::Expr::Variable{"canvas"}),
    slcp::Expr(slcp::Expr::Variable{"width"}), slcp::Expr(1),
    slcp::Expr(slcp::Expr::Variable{"height"}), slcp::Expr(2)}});
  test_expr(expr, values);
}

TEST(parsing, array_test_0) {
  const char * input = "[1, 2.0, \"hello\", world]";
  slcp::Expr expr;
  auto remainder = slcp::parse_array(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  slcp::Expr values = slcp::Expr(slcp::Expr::Array{
    slcp::Exprs{ 
    slcp::Expr(1), slcp::Expr(2.0), slcp::Expr("hello"),
    slcp::Expr(slcp::Expr::Variable{"world"})}
  });
  test_expr(expr, values);
}

TEST(parsing, array_test_1) {
  const char * input = "[1, 2.0, \"hello\", world, rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)]";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  slcp::Expr thickness_expr = slcp::Expr(slcp::OpType::BinPlus);
  thickness_expr.add_children(1, 2);
  slcp::Expr values = slcp::Expr(slcp::Expr::Array{
    slcp::Exprs{ 
    slcp::Expr(1), slcp::Expr(2.0), slcp::Expr("hello"),
    slcp::Expr(slcp::Expr::Variable{"world"}),
    slcp::Expr(slcp::Expr::Shape{slcp::Exprs{ 
    slcp::Expr(slcp::Expr::Variable{"rectangle"}),
    slcp::Expr(slcp::Expr::Variable{"thickness"}), thickness_expr,
    slcp::Expr(slcp::Expr::Variable{"center_x"}), slcp::Expr(2),
    slcp::Expr(slcp::Expr::Variable{"center_y"}), slcp::Expr(1),
    slcp::Expr(slcp::Expr::Variable{"width"}), slcp::Expr(1),
    slcp::Expr(slcp::Expr::Variable{"height"}), slcp::Expr(2)}})}
  });
  test_expr(expr, values);
}

TEST(parsing, array_test_2) {
  const char * input = "[[1, 2.0], [\"hello\", world]]";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  slcp::Expr values = slcp::Expr(slcp::Expr::Array{
      slcp::Exprs{ 
      slcp::Expr(slcp::Expr::Array{
        slcp::Exprs{slcp::Expr(1), slcp::Expr(2.0)}
      }),
      slcp::Expr(slcp::Expr::Array{slcp::Exprs{ 
        slcp::Expr("hello"), slcp::Expr(slcp::Expr::Variable{"world"})}
      })
      }});
}

TEST(parsing, assignment_test_0) {
  const char * input = "x = rectangle()";
  slcp::Expr expr;
  auto remainder = slcp::parse_precedence_14_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');

  auto result = slcp::Expr(slcp::OpType::BinAssignment);
  result.add_children(slcp::Expr::Variable{"x"}, slcp::Expr::Shape{slcp::Exprs{slcp::Expr(slcp::Expr::Variable{"rectangle"})}});
  test_expr(expr, result);

}

// TEST(parsing, assignment_test_1) {
//   const char * input = "some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_assignment(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   ASSERT_EQ(the_lline.type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.value_type[0], EXPR);
//   ASSERT_EQ(the_lline.value_type[1], SHAPE);
//   test_expression(the_lline.value[0].the_expr, VAR, (void *)"some_value");
//   parsed_shape the_shape = the_lline.value[1].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, assignment_test_2) {
//   const char * input = "x = [1 < 3 == 2 > 1, -(((1 - - 2)))];";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_assignment(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   ASSERT_EQ(the_lline.type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.value_type[0], EXPR);
//   ASSERT_EQ(the_lline.value_type[1], ARRAY);
//   test_expression(the_lline.value[0].the_expr, VAR, (void *)"x");
//   expression head_one = the_lline.value[1].the_array[0].value[0].the_expr;
//   int value_one = 1;
//   int value_two = 2;
//   int value_three = 3;
//   test_expression(head_one, BIN_EQ, NULL);
//   test_expression(head_one.child[0], BIN_LT, NULL);
//   test_expression(head_one.child[0].child[0], INT, &value_one);
//   test_expression(head_one.child[0].child[1], INT, &value_three);
//   test_expression(head_one.child[1], BIN_GT, NULL);
//   test_expression(head_one.child[1].child[0], INT, &value_two);
//   test_expression(head_one.child[1].child[1], INT, &value_one);
//   expression head_two = the_lline.value[1].the_array[0].value[1].the_expr;
//   test_expression(head_two, UN_MINUS, NULL);
//   test_expression(head_two.child[0], BIN_MINUS, NULL);
//   test_expression(head_two.child[0].child[0], INT, &value_one);
//   test_expression(head_two.child[0].child[1], UN_MINUS, NULL);
//   test_expression(head_two.child[0].child[1].child[0], INT, &value_two);
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, draw_test_0) {
//   const char * input = "draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   ASSERT_EQ(the_lline.type, DRAW_STMT);
//   ASSERT_EQ(the_lline.value_type[0], SHAPE);
//   parsed_shape the_shape = the_lline.value[0].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, draw_test_1) {
//   const char * input = "draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)) -> \"some_place\";";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_draw_statement(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   ASSERT_EQ(the_lline.type, DRAW_STMT);
//   ASSERT_EQ(the_lline.value_type[0], SHAPE);
//   parsed_shape the_shape = the_lline.value[0].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.value_type[1], EXPR);
//   test_expression(the_lline.value[1].the_expr, STRING, (void *)"some_place");
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, if_test_0) {
//   const char * input = "if 1 == 2 {"
//                            "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
//                            "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
//                            "}";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_lline(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
// 
//   ASSERT_EQ(the_lline.type, IF_STMT);
//   ASSERT_EQ(the_lline.qty_children, 2);
//   ASSERT_EQ(the_lline.qty_values, 1);
// 
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_lline.value[0].the_expr, BIN_EQ, NULL);
//   test_expression(the_lline.value[0].the_expr.child[0], INT, &value_one);
//   test_expression(the_lline.value[0].the_expr.child[1], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
//   ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
//   parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
//   ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
//   test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
//   parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
//   ASSERT_EQ(the_shape_two.type, RECTANGLE);
//   test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape_two.values[1].child[0], INT, &value_one);
//   test_expression(the_shape_two.values[1].child[1], INT, &value_two);
//   test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape_two.values[3], INT, &value_two);
//   test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape_two.values[5], INT, &value_one);
//   test_expression(the_shape_two.values[6], VAR, (void *)"width");
//   test_expression(the_shape_two.values[7], INT, &value_one);
//   test_expression(the_shape_two.values[8], VAR, (void *)"height");
//   test_expression(the_shape_two.values[9], INT, &value_two);
// 
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, for_test_0) {
//   const char * the_input = "for i in range(1 + 2) {"
//                            "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
//                            "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
//                            "}";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_lline(the_input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
// 
//   ASSERT_EQ(the_lline.type, FOR_LOOP);
//   ASSERT_EQ(the_lline.qty_children, 2);
//   ASSERT_EQ(the_lline.qty_values, 2);
// 
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_lline.value[0].the_expr, VAR, (void *)"i");
//   test_expression(the_lline.value[1].the_expr, BIN_PLUS, NULL);
//   test_expression(the_lline.value[1].the_expr.child[0], INT, &value_one);
//   test_expression(the_lline.value[1].the_expr.child[1], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
//   ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
//   parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
//   ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
//   test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
//   parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
//   ASSERT_EQ(the_shape_two.type, RECTANGLE);
//   test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape_two.values[1].child[0], INT, &value_one);
//   test_expression(the_shape_two.values[1].child[1], INT, &value_two);
//   test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape_two.values[3], INT, &value_two);
//   test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape_two.values[5], INT, &value_one);
//   test_expression(the_shape_two.values[6], VAR, (void *)"width");
//   test_expression(the_shape_two.values[7], INT, &value_one);
//   test_expression(the_shape_two.values[8], VAR, (void *)"height");
//   test_expression(the_shape_two.values[9], INT, &value_two);
// 
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, for_test_1) {
//   const char * the_input = "for i in range(1, 2) {"
//                            "    draw(rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2));"
//                            "    some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);"
//                            "}";
//   parsed_lline the_lline = {0};
//   auto remainder = parse_lline(the_input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
// 
//   ASSERT_EQ(the_lline.type, FOR_LOOP);
//   ASSERT_EQ(the_lline.qty_children, 2);
//   ASSERT_EQ(the_lline.qty_values, 3);
// 
//   int value_one = 1;
//   int value_two = 2;
//   test_expression(the_lline.value[0].the_expr, VAR, (void *)"i");
//   test_expression(the_lline.value[1].the_expr, INT, &value_one);
//   test_expression(the_lline.value[2].the_expr, INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[0].type, DRAW_STMT);
//   ASSERT_EQ(the_lline.child[0].value_type[0], SHAPE);
//   parsed_shape the_shape = the_lline.child[0].value[0].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape.values[1].child[0], INT, &value_one);
//   test_expression(the_shape.values[1].child[1], INT, &value_two);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_two);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_one);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_one);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_two);
// 
//   ASSERT_EQ(the_lline.child[1].type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.child[1].value_type[0], EXPR);
//   ASSERT_EQ(the_lline.child[1].value_type[1], SHAPE);
//   test_expression(the_lline.child[1].value[0].the_expr, VAR, (void *)"some_value");
//   parsed_shape the_shape_two = the_lline.child[1].value[1].the_shape;
//   ASSERT_EQ(the_shape_two.type, RECTANGLE);
//   test_expression(the_shape_two.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape_two.values[1], BIN_PLUS, NULL);
//   test_expression(the_shape_two.values[1].child[0], INT, &value_one);
//   test_expression(the_shape_two.values[1].child[1], INT, &value_two);
//   test_expression(the_shape_two.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape_two.values[3], INT, &value_two);
//   test_expression(the_shape_two.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape_two.values[5], INT, &value_one);
//   test_expression(the_shape_two.values[6], VAR, (void *)"width");
//   test_expression(the_shape_two.values[7], INT, &value_one);
//   test_expression(the_shape_two.values[8], VAR, (void *)"height");
//   test_expression(the_shape_two.values[9], INT, &value_two);
// 
//   free_parsed_lline(the_lline);
// }
