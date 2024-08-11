#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <gtest/gtest.h>

#include "evaluation/evaluation.h"
#include "parsing/parsing.h"

void test_expression(expression the_expression, expression_type type, void * value);
void validate_rectangle(rectangle truth, rectangle test);
void validate_line(line truth, line test);
void validate_ellipse(ellipse truth, ellipse test);
void validate_canvas(canvas truth, canvas test);

#endif
