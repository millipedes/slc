#pragma once

#include <cstdarg>
#include <cstring>
#include <functional>
#include <optional>

#include "parsing_ds.h"

namespace SLCParsing {

constexpr static auto max_word_len = 1024;

auto parse_ws(const char * input) -> const char *;

auto parse_variable_name(const char * input, Expr& data) -> const char *;
auto parse_number(const char * input, Expr& data) -> const char *;
auto parse_string(const char * input, Expr& expr) -> const char *;
auto parse_word(const char * input, const char * word) -> const char *;
auto parse_bool(const char * input, Expr& expr) -> const char *;

auto parse_precedence_1_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_3_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_4_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_6_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_7_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_11_expr(const char * input, Expr& expr) -> const char *;
auto parse_precedence_12_expr(const char * input, Expr& expr) -> const char *;

auto is_double_delineator(char c) -> bool;
auto is_whitespace(char c) -> bool;

// const char * parse_shape(const char * input, void * data);
// 
// const char * parse_assignment(const char * input, void * data);
// const char * parse_draw_statement(const char * input, void * data);
// const char * parse_if_statement(const char * input, void * data);
// const char * parse_for_loop(const char * input, void * data);
// 
// const char * parse_lline(const char * input, void * data);

} // namespace SLCParsing
