#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <gtest/gtest.h>

#include "parsing/parsing.h"

void test_expression(expression the_expression, expression_type type, void * value);

#endif
