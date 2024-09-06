#include "test_helper.h"

TEST(parsing, variable_name_test_0) {
  const char * input = "some_string";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_variable_name(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::Expr::Variable{"some_string"}));
}

TEST(parsing, number_test_0) {
  const char * input = "123";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  int value = 123;
  test_expr(expr, SLCParsing::Expr(123));
}

TEST(parsing, number_test_1) {
  const char * input = "123.123";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(123.123));
}

TEST(parsing, number_test_2) {
  const char * input = "1e-2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(0.01));
}

TEST(parsing, number_test_3) {
  const char * input = "1E-2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_number(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(0.01));
}

TEST(parsing, string_test_0) {
  const char * input = "\"hello world\"";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_string(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr("hello world"));
}

TEST(parsing, string_test_1) {
  const char * input = "\"hello world";
  SLCParsing::Expr expr;
  const char * remainder = parse_string(input, expr);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, word_test_0) {
  const char * input = ".\\";
  const char * remainder = SLCParsing::parse_word(input, ".\\");
  ASSERT_EQ(remainder[0], '\0');
}

TEST(parsing, factor_test_0) {
  const char * input = "(((((-1e-2)))))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_1_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(0.01));
}

TEST(parsing, factor_test_1) {
  const char * input = "-(((((-1e-2)))))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_1_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(0.01));
}

TEST(parsing, term_test_0) {
  const char * input = "1e-2 * 1e-2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[0], SLCParsing::Expr(0.01));
  test_expr(expr.child()[1], SLCParsing::Expr(0.01));
}

TEST(parsing, term_test_1) {
  const char * input = "1e-2 * 1e-2 * 1e-2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[0], SLCParsing::Expr(0.01));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(0.01));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(0.01));
}

TEST(parsing, term_test_2) {
  const char * input = "1 / 2 % 3";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinDivide));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMod));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(2));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(3));
}

TEST(parsing, term_test_3) {
  const char * input = "\"some string\" / -1e-2 % var_name";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_3_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinDivide));
  test_expr(expr.child()[0], SLCParsing::Expr("some string"));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMod));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[1].child()[0].child()[0], SLCParsing::Expr(0.01));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(SLCParsing::Expr::Variable{"var_name"}));
}

TEST(parsing, expression_test_0) {
  const char * input = "-123";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(123));
}

TEST(parsing, expression_test_1) {
  const char * input = "-1e-2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(0.01));
}

TEST(parsing, expression_test_2) {
  const char * input = "\"hello world\"";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr("hello world"));
}

TEST(parsing, expression_test_3) {
  const char * input = "\"hello world";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_TRUE(remainder == NULL);
}

TEST(parsing, expression_test_4) {
  const char * input = "1 + 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_5) {
  const char * input = "1 + 2 * 3";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(2));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(3));
}

TEST(parsing, expression_test_6) {
  const char * input = "(1 + 2) * 3";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
  test_expr(expr.child()[1], SLCParsing::Expr(3));
}

TEST(parsing, expression_test_7) {
  const char * input = "-(1 + 2)";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_8) {
  const char * input = "(((((1 - - 2)))))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinMinus));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_9) {
  const char * input = "1 ^ 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPow));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_10) {
  const char * input = "(1 + 2) ^ -(1 + 2)";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPow));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[1].child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1].child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_11) {
  const char * input = "1 == 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinEq));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_12) {
  const char * input = "1 != 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinNeq));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_13) {
  const char * input = "1 >= 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinGeq));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_14) {
  const char * input = "1 > 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinGt));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_15) {
  const char * input = "1 <= 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinLeq));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_16) {
  const char * input = "1 < 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinLt));
  test_expr(expr.child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_17) {
  const char * input = "true";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(true));
}

TEST(parsing, expression_test_18) {
  const char * input = "false";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(false));
}

TEST(parsing, expression_test_19) {
  const char * input = "sin((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::Sin));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_20) {
  const char * input = "cos((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::Cos));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_21) {
  const char * input = "tan((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::Tan));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_22) {
  const char * input = "arcsin((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::ArcSin));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_23) {
  const char * input = "arccos((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::ArcCos));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_24) {
  const char * input = "arctan((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::ArcTan));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_25) {
  const char * input = "log((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::Log));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_26) {
  const char * input = "ln((1 + 2))";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::Ln));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_27) {
  const char * input = "x[0]";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::Expr::Variable{"x"}));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::ArrayAccessor));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(0));
}

TEST(parsing, expression_test_28) {
  const char * input = "x[9 * 1][1 + 2]";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_7_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::Expr::Variable{"x"}));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::ArrayAccessor));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[0].child()[0].child()[0], SLCParsing::Expr(9));
  test_expr(expr.child()[0].child()[0].child()[1], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0].child()[1].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_29) {
  const char * input = "1 <= 2 && 1 == 2";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinBoolAnd));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinLeq));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(2));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinEq));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(2));
}

TEST(parsing, expression_test_30) {
  const char * input = "-ln(0.5) + 1.0 * 2.0";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(SLCParsing::OpType::Ln));
  test_expr(expr.child()[0].child()[0].child()[0], SLCParsing::Expr(0.5));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(1.0));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(2.0));
}

TEST(parsing, expression_test_31) {
  const char * input = "1 <= 2 && 1 == 2 || 2 == 3";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_12_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinBoolOr));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BinBoolAnd));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(SLCParsing::OpType::BinLeq));
  test_expr(expr.child()[0].child()[0].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[0].child()[1], SLCParsing::Expr(2));
  test_expr(expr.child()[0].child()[1], SLCParsing::Expr(SLCParsing::OpType::BinEq));
  test_expr(expr.child()[0].child()[1].child()[0], SLCParsing::Expr(1));
  test_expr(expr.child()[0].child()[1].child()[1], SLCParsing::Expr(2));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinEq));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(2));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(3));
}

TEST(parsing, expression_test_32) {
  const char * input = "!-ln(0.5) + 1.0 * 2.0";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_precedence_11_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  test_expr(expr, SLCParsing::Expr(SLCParsing::OpType::BinPlus));
  test_expr(expr.child()[0], SLCParsing::Expr(SLCParsing::OpType::BoolNot));
  test_expr(expr.child()[0].child()[0], SLCParsing::Expr(SLCParsing::OpType::UnMinus));
  test_expr(expr.child()[0].child()[0].child()[0], SLCParsing::Expr(SLCParsing::OpType::Ln));
  test_expr(expr.child()[0].child()[0].child()[0].child()[0], SLCParsing::Expr(0.5));
  test_expr(expr.child()[1], SLCParsing::Expr(SLCParsing::OpType::BinMult));
  test_expr(expr.child()[1].child()[0], SLCParsing::Expr(1.0));
  test_expr(expr.child()[1].child()[1], SLCParsing::Expr(2.0));
}

TEST(parsing, shape_test_0) {
  const char * input = "rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_shape(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  SLCParsing::Expr thickness_expr = SLCParsing::Expr(SLCParsing::OpType::BinPlus);
  thickness_expr.set_child(std::make_unique<std::vector<SLCParsing::Expr>>(
        std::vector<SLCParsing::Expr>{SLCParsing::Expr(1), SLCParsing::Expr(2)}));
  SLCParsing::Expr values = SLCParsing::Expr(SLCParsing::Expr::Shape{
    std::vector<SLCParsing::Expr>{
    SLCParsing::Expr(SLCParsing::Expr::Variable{"rectangle"}),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"thickness"}), thickness_expr,
    SLCParsing::Expr(SLCParsing::Expr::Variable{"center_x"}), SLCParsing::Expr(2),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"center_y"}), SLCParsing::Expr(1),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"width"}), SLCParsing::Expr(1),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"height"}), SLCParsing::Expr(2)}});
  test_expr(expr, values);
}

TEST(parsing, shape_test_1) {
  const char * input = "canvas(width 1, height 2)";
  SLCParsing::Expr expr;
  const char * remainder = SLCParsing::parse_shape(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  SLCParsing::Expr values = SLCParsing::Expr(SLCParsing::Expr::Shape{
    std::vector<SLCParsing::Expr>{
    SLCParsing::Expr(SLCParsing::Expr::Variable{"canvas"}),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"width"}), SLCParsing::Expr(1),
    SLCParsing::Expr(SLCParsing::Expr::Variable{"height"}), SLCParsing::Expr(2)}});
  test_expr(expr, values);
}

// TEST(parsing, array_test_0) {
//   const char * input = "[1, 2.0, \"hello\", world]";
//   parsed_array the_array = {0};
//   const char * remainder = parse_array(input, &the_array);
//   ASSERT_EQ(remainder[0], '\0');
//   int value_one = 1;
//   double value_two = 2.0;
//   test_expression(the_array.value[0].the_expr, INT, &value_one);
//   test_expression(the_array.value[1].the_expr, DOUBLE, &value_two);
//   test_expression(the_array.value[2].the_expr, STRING, (void *)"hello");
//   test_expression(the_array.value[3].the_expr, VAR, (void *)"world");
//   free_parsed_array(the_array);
// }
// 
// TEST(parsing, array_test_1) {
//   const char * input = "[1, 2.0, \"hello\", world, rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2)]";
//   parsed_array the_array = {0};
//   const char * remainder = parse_array(input, &the_array);
//   ASSERT_EQ(remainder[0], '\0');
//   int value_one = 1;
//   double value_two = 2.0;
//   test_expression(the_array.value[0].the_expr, INT, &value_one);
//   test_expression(the_array.value[1].the_expr, DOUBLE, &value_two);
//   test_expression(the_array.value[2].the_expr, STRING, (void *)"hello");
//   test_expression(the_array.value[3].the_expr, VAR, (void *)"world");
//   ASSERT_EQ(the_array.value_type[4], SHAPE);
//   parsed_shape the_shape = the_array.value[4].the_shape;
//   ASSERT_EQ(the_shape.type, RECTANGLE);
//   test_expression(the_shape.values[0], VAR, (void *)"thickness");
//   test_expression(the_shape.values[1], BIN_PLUS, NULL);
//   int value_three = 1;
//   int value_four = 2;
//   test_expression(the_shape.values[1].child[0], INT, &value_three);
//   test_expression(the_shape.values[1].child[1], INT, &value_four);
//   test_expression(the_shape.values[2], VAR, (void *)"center_x");
//   test_expression(the_shape.values[3], INT, &value_four);
//   test_expression(the_shape.values[4], VAR, (void *)"center_y");
//   test_expression(the_shape.values[5], INT, &value_three);
//   test_expression(the_shape.values[6], VAR, (void *)"width");
//   test_expression(the_shape.values[7], INT, &value_three);
//   test_expression(the_shape.values[8], VAR, (void *)"height");
//   test_expression(the_shape.values[9], INT, &value_four);
//   free_parsed_array(the_array);
// }
// 
// TEST(parsing, array_test_2) {
//   const char * input = "[[1, 2.0], [\"hello\", world]]";
//   parsed_array the_array = {0};
//   const char * remainder = parse_array(input, &the_array);
//   ASSERT_EQ(remainder[0], '\0');
//   int value_one = 1;
//   double value_two = 2.0;
//   ASSERT_EQ(the_array.value_type[0], ARRAY);
//   ASSERT_EQ(the_array.value_type[1], ARRAY);
//   parsed_array sub_array_one = the_array.value[0].the_array[0];
//   parsed_array sub_array_two = the_array.value[1].the_array[0];
//   test_expression(sub_array_one.value[0].the_expr, INT, &value_one);
//   test_expression(sub_array_one.value[1].the_expr, DOUBLE, &value_two);
//   test_expression(sub_array_two.value[0].the_expr, STRING, (void *)"hello");
//   test_expression(sub_array_two.value[1].the_expr, VAR, (void *)"world");
//   free_parsed_array(the_array);
// }
// 
// TEST(parsing, assignment_test_0) {
//   const char * input = "x = rectangle();";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(input, &the_lline);
//   ASSERT_EQ(remainder[0], '\0');
//   ASSERT_EQ(the_lline.type, ASSIGNMENT);
//   ASSERT_EQ(the_lline.value_type[0], EXPR);
//   ASSERT_EQ(the_lline.value_type[1], SHAPE);
//   test_expression(the_lline.value[0].the_expr, VAR, (void *)"x");
//   ASSERT_EQ(the_lline.value[1].the_shape.type, RECTANGLE);
//   ASSERT_EQ(the_lline.value[1].the_shape.qty_values, 0);
//   ASSERT_TRUE(the_lline.value[1].the_shape.values == NULL);
//   free_parsed_lline(the_lline);
// }
// 
// TEST(parsing, assignment_test_1) {
//   const char * input = "some_value = rectangle(thickness 1 + 2, center_x 2, center_y 1, width 1, height 2);";
//   parsed_lline the_lline = {0};
//   const char * remainder = parse_assignment(input, &the_lline);
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
//   const char * remainder = parse_assignment(input, &the_lline);
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
//   const char * remainder = parse_draw_statement(input, &the_lline);
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
//   const char * remainder = parse_draw_statement(input, &the_lline);
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
//   const char * remainder = parse_lline(input, &the_lline);
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
//   const char * remainder = parse_lline(the_input, &the_lline);
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
//   const char * remainder = parse_lline(the_input, &the_lline);
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
