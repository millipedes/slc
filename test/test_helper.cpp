#include "test_helper.h"

auto test_expr(const slcp::Expr& expr, const slcp::Expr& value) -> void {
  ASSERT_EQ(expr, value);
}

auto test_result_from_string(slcp::Expr& expr, const char * input,
    const slcp::Expr::ExprVariant result_value) -> void {
  auto sts = std::stack<slce::SymbolTable>();
  auto remainder = slcp::parse_precedence_14_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slce::evaluate_expression(expr, sts);
  test_expr(result, slcp::Expr(result_value));
}

auto test_double_expr(slcp::Expr& expr, const char * input,
    const double& result_double) -> void {
  auto sts = std::stack<slce::SymbolTable>();
  auto remainder = slcp::parse_precedence_14_expr(input, expr);
  ASSERT_EQ(remainder[0], '\0');
  auto result = slce::evaluate_expression(expr, sts);
  ASSERT_NEAR(std::get<double>(result.value()), result_double, 0.001);
}

// void validate_ellipse(ellipse truth, ellipse test) {
//   ASSERT_EQ(truth.center.x, test.center.x);
//   ASSERT_EQ(truth.center.y, test.center.y);
//   ASSERT_EQ(truth.color.r, test.color.r);
//   ASSERT_EQ(truth.color.b, test.color.b);
//   ASSERT_EQ(truth.color.g, test.color.g);
//   ASSERT_EQ(truth.major_axis, test.major_axis);
//   ASSERT_EQ(truth.minor_axis, test.minor_axis);
//   ASSERT_EQ(truth.thickness, test.thickness);
// }
// 
// void validate_line(line truth, line test) {
//   ASSERT_EQ(truth.to.x, test.to.x);
//   ASSERT_EQ(truth.to.y, test.to.y);
//   ASSERT_EQ(truth.from.x, test.from.x);
//   ASSERT_EQ(truth.from.y, test.from.y);
//   ASSERT_EQ(truth.color.r, test.color.r);
//   ASSERT_EQ(truth.color.g, test.color.g );
//   ASSERT_EQ(truth.color.b, test.color.b);
//   ASSERT_EQ(truth.thickness, test.thickness);
// }
// 
// void validate_rectangle(rectangle truth, rectangle test) {
//   ASSERT_EQ(truth.center.x, test.center.x);
//   ASSERT_EQ(truth.center.y, test.center.y);
//   ASSERT_EQ(truth.color.r, test.color.r);
//   ASSERT_EQ(truth.color.g, test.color.g);
//   ASSERT_EQ(truth.color.b, test.color.b);
//   ASSERT_EQ(truth.height, test.height);
//   ASSERT_EQ(truth.width, test.width);
//   ASSERT_EQ(truth.thickness, test.thickness);
// }
// 
// void validate_canvas(canvas truth, canvas test) {
//   ASSERT_EQ(truth.height, test.height);
//   ASSERT_EQ(truth.width, test.width);
//   // probably should find a better solution to this (weigh performance vs
//   // accuracy)
//   for(int i = 0; i < truth.height % 100; i++) {
//     for(int j = 0; j < truth.width % 100; j++) {
//       ASSERT_EQ(truth.values[i][j].r, test.values[i][j].r);
//       ASSERT_EQ(truth.values[i][j].g, test.values[i][j].g);
//       ASSERT_EQ(truth.values[i][j].b, test.values[i][j].b);
//       ASSERT_EQ(truth.values[i][j].a, test.values[i][j].a);
//     }
//   }
// }
