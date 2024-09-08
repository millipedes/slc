#include "double.h"

namespace SLCEvaluation {

auto double_unary_minus(slcp::Expr expr) -> double {
  return -std::get<double>(expr.value());
}

auto double_addition(slcp::Expr left, slcp::Expr right) -> double {
  return std::get<double>(left.value()) + std::get<double>(right.value());
}

auto double_subtraction(slcp::Expr left, slcp::Expr right) -> double {
  return std::get<double>(left.value()) - std::get<double>(right.value());
}

auto double_multiplication(slcp::Expr left, slcp::Expr right) -> double {
  return std::get<double>(left.value()) * std::get<double>(right.value());
}

auto double_division(slcp::Expr left, slcp::Expr right) -> double {
  return std::get<double>(left.value()) / std::get<double>(right.value());
}

auto double_pow(slcp::Expr left, slcp::Expr right) -> double {
  return pow(std::get<double>(left.value()), std::get<double>(right.value()));
}

auto double_eq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) == std::get<double>(right.value());
}

auto double_neq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) != std::get<double>(right.value());
}

auto double_geq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) >= std::get<double>(right.value());
}

auto double_gt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) > std::get<double>(right.value());
}

auto double_leq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) <= std::get<double>(right.value());
}

auto double_lt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<double>(left.value()) < std::get<double>(right.value());
}

auto double_sin(slcp::Expr expr) -> double {
  return sin(std::get<double>(expr.value()));
}

auto double_cos(slcp::Expr expr) -> double {
  return cos(std::get<double>(expr.value()));
}

auto double_tan(slcp::Expr expr) -> double {
  return tan(std::get<double>(expr.value()));
}

auto double_arcsin(slcp::Expr expr) -> double {
  return asin(std::get<double>(expr.value()));
}

auto double_arccos(slcp::Expr expr) -> double {
  return acos(std::get<double>(expr.value()));
}

auto double_arctan(slcp::Expr expr) -> double {
  return atan(std::get<double>(expr.value()));
}

auto double_log(slcp::Expr expr) -> double {
  return log(std::get<double>(expr.value())) / log(2);
}

auto double_ln(slcp::Expr expr) -> double {
  return log(std::get<double>(expr.value()));
}

} // namespace SLCEvaluation
