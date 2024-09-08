#include "bool.h"

namespace SLCEvaluation {

auto bool_eq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) == std::get<bool>(right.value());
}

auto bool_neq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) != std::get<bool>(right.value());
}

auto bool_geq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) >= std::get<bool>(right.value());
}

auto bool_gt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) > std::get<bool>(right.value());
}

auto bool_leq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) <= std::get<bool>(right.value());
}

auto bool_lt(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) < std::get<bool>(right.value());
}

auto bool_and(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) && std::get<bool>(right.value());
}

auto bool_or(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<bool>(left.value()) || std::get<bool>(right.value());
}

auto bool_not(slcp::Expr expr) -> bool {
  return !std::get<bool>(expr.value());
}

} // namespace SLCEvaluation
