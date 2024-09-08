#pragma once

#include <gtest/gtest.h>

#include "evaluation/evaluation.h"
#include "parsing/parsing.h"

namespace slcp = SLCParsing;
namespace slce = SLCEvaluation;

auto test_expr(const slcp::Expr& expr, const slcp::Expr& value) -> void;
auto test_result_from_string(slcp::Expr& expr, const char * input,
    const slcp::Expr::ExprVariant result_value) -> void;
auto test_double_expr(slcp::Expr& expr, const char * input,
    const double& result_double) -> void;
// void validate_rectangle(rectangle truth, rectangle test);
// void validate_line(line truth, line test);
// void validate_ellipse(ellipse truth, ellipse test);
// void validate_canvas(canvas truth, canvas test);
