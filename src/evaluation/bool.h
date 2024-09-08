#pragma once

#include "../parsing/parsing.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto bool_eq(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_neq(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_geq(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_gt(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_leq(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_lt(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_and(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_or(slcp::Expr left, slcp::Expr right) -> bool;
auto bool_not(slcp::Expr expr) -> bool;

} // namespace SLCEvaluation
