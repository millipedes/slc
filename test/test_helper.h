#pragma once

#include <gtest/gtest.h>

// #include "evaluation/evaluation.h"
#include "parsing/parsing.h"

auto test_expr(const SLCParsing::Expr& the_expr, const SLCParsing::Expr& value) -> void;
// void validate_rectangle(rectangle truth, rectangle test);
// void validate_line(line truth, line test);
// void validate_ellipse(ellipse truth, ellipse test);
// void validate_canvas(canvas truth, canvas test);
