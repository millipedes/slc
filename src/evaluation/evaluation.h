#pragma once

#include "bool.h"
#include "double.h"
// #include "evaluation_drawing.h"
// #include "evaluation_types.h"
#include "integer.h"
#include "string.h"
#include "symbol_table.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto evaluate_expression(slcp::Expr expr, SymbolTableStack& sts) -> slcp::Expr;
auto expr_unary_minus(slcp::Expr expr) -> slcp::Expr;
auto expr_addition(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_subtraction(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_multiplication(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_division(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_modulus(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_pow(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_eq(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_neq(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_geq(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_gt(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_leq(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_lt(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_sin(slcp::Expr expr) -> slcp::Expr;
auto expr_cos(slcp::Expr expr) -> slcp::Expr;
auto expr_tan(slcp::Expr expr) -> slcp::Expr;
auto expr_arcsin(slcp::Expr expr) -> slcp::Expr;
auto expr_arccos(slcp::Expr expr) -> slcp::Expr;
auto expr_arctan(slcp::Expr expr) -> slcp::Expr;
auto expr_log(slcp::Expr expr) -> slcp::Expr;
auto expr_ln(slcp::Expr expr) -> slcp::Expr;
auto expr_and(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_or(slcp::Expr left, slcp::Expr right) -> slcp::Expr;
auto expr_not(slcp::Expr expr) -> slcp::Expr;

auto expr_shape(slcp::Expr expr, SymbolTableStack& sts) -> slcp::Expr;

// slc_value evaluate_array(parsed_array the_array, symbol_table * st);
// 
// slc_value evaluate_slc_primitive(slc_primitive value, slc_primitive_type type, symbol_table * st);
// 
// slc_value evaluate_lline_union(slc_primitive value, slc_primitive_type type);
// void evaluate_lline(parsed_lline the_lline, symbol_table * st);

} // namespace SLCEvaluation
