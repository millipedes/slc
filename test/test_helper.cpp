#include "test_helper.h"

auto test_expr(const slcp::Expr& expr, const slcp::Expr& value) -> void {
  ASSERT_EQ(expr, value);
}

auto test_result_from_string(slcp::Expr& expr, const char * input,
    const slcp::Expr::ExprVariant result_value) -> void {
  auto sts = std::stack<slce::SymbolTable>();
  auto remainder = slcp::parse_precedence_15_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slce::evaluate_expression(expr, sts);
  test_expr(result, slcp::Expr(result_value));
}

auto test_double_expr(slcp::Expr& expr, const char * input,
    const double& result_double) -> void {
  auto sts = std::stack<slce::SymbolTable>();
  auto remainder = slcp::parse_precedence_15_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slce::evaluate_expression(expr, sts);
  ASSERT_NEAR(std::get<double>(result.value()), result_double, 0.001);
}
