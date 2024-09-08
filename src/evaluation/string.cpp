#include "string.h"

namespace SLCEvaluation {

auto string_addition(slcp::Expr left, slcp::Expr right) -> std::string {
  return std::get<std::string>(left.value()) + std::get<std::string>(right.value());
}

auto string_eq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<std::string>(left.value()) == std::get<std::string>(right.value());
}

auto string_neq(slcp::Expr left, slcp::Expr right) -> bool {
  return std::get<std::string>(left.value()) != std::get<std::string>(right.value());
}

} // namespace SLCEvaluation
