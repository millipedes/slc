#pragma once

#include <cmath>

#include "../parsing/parsing.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto double_unary_minus(slcp::Expr expr) -> double;
auto double_addition(slcp::Expr left, slcp::Expr right) -> double;
auto double_subtraction(slcp::Expr left, slcp::Expr right) -> double;
auto double_multiplication(slcp::Expr left, slcp::Expr right) -> double;
auto double_division(slcp::Expr left, slcp::Expr right) -> double;
auto double_pow(slcp::Expr left, slcp::Expr right) -> double;
auto double_eq(slcp::Expr left, slcp::Expr right) -> bool;
auto double_neq(slcp::Expr left, slcp::Expr right) -> bool;
auto double_geq(slcp::Expr left, slcp::Expr right) -> bool;
auto double_gt(slcp::Expr left, slcp::Expr right) -> bool;
auto double_leq(slcp::Expr left, slcp::Expr right) -> bool;
auto double_lt(slcp::Expr left, slcp::Expr right) -> bool;
auto double_sin(slcp::Expr expr) -> double;
auto double_cos(slcp::Expr expr) -> double;
auto double_tan(slcp::Expr expr) -> double;
auto double_arcsin(slcp::Expr expr) -> double;
auto double_arccos(slcp::Expr expr) -> double;
auto double_arctan(slcp::Expr expr) -> double;
auto double_log(slcp::Expr expr) -> double;
auto double_ln(slcp::Expr expr) -> double;

} // namespace SLCEvaluation
