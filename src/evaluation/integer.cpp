#include "integer.h"

namespace SLCEvaluation {

auto int_unary_minus(slcp::Expr expr) -> int {
  return -std::get<int>(expr.value());
}

auto int_addition(slcp::Expr left, slcp::Expr right) -> int {
  return std::get<int>(left.value()) + std::get<int>(right.value());
}

auto int_subtraction(slcp::Expr left, slcp::Expr right) -> int {
  return std::get<int>(left.value()) - std::get<int>(right.value());
}

auto int_multiplication(slcp::Expr left, slcp::Expr right) -> int {
  return std::get<int>(left.value()) * std::get<int>(right.value());
}

auto int_division(slcp::Expr left, slcp::Expr right) -> int {
  return std::get<int>(left.value()) / std::get<int>(right.value());
}

auto int_modulus(slcp::Expr left, slcp::Expr right) -> int {
  return std::get<int>(left.value()) % std::get<int>(right.value());
}

auto int_pow(slcp::Expr left, slcp::Expr right) -> int {
  return pow(std::get<int>(left.value()), std::get<int>(right.value()));
}

auto int_eq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) == std::get<int>(right.value());
}

auto int_neq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) != std::get<int>(right.value());
}

auto int_geq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) >= std::get<int>(right.value());
}

auto int_gt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) > std::get<int>(right.value());
}

auto int_leq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) <= std::get<int>(right.value());
}

auto int_lt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<int>(left.value()) < std::get<int>(right.value());
}

} // namespace SLCEvaluation
