#pragma once

#include "../parsing/parsing.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto string_addition(slcp::Expr left, slcp::Expr right) -> std::string;
auto string_eq(slcp::Expr left, slcp::Expr right) -> bool;
auto string_neq(slcp::Expr left, slcp::Expr right) -> bool;

} // namespace SLCEvaluation
