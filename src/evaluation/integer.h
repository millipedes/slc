#pragma once

#include <cmath>

#include "../parsing/parsing.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto int_unary_minus(slcp::Expr expr) -> int;
auto int_addition(slcp::Expr left, slcp::Expr right) -> int;
auto int_subtraction(slcp::Expr left, slcp::Expr right) -> int;
auto int_multiplication(slcp::Expr left, slcp::Expr right) -> int;
auto int_division(slcp::Expr left, slcp::Expr right) -> int;
auto int_modulus(slcp::Expr left, slcp::Expr right) -> int;
auto int_pow(slcp::Expr left, slcp::Expr right) -> int;
auto int_eq(slcp::Expr left, slcp::Expr right) -> bool;
auto int_neq(slcp::Expr left, slcp::Expr right) -> bool;
auto int_geq(slcp::Expr left, slcp::Expr right) -> bool;
auto int_gt(slcp::Expr left, slcp::Expr right) -> bool;
auto int_leq(slcp::Expr left, slcp::Expr right) -> bool;
auto int_lt(slcp::Expr left, slcp::Expr right) -> bool;

} // namespace SLCEvaluation
