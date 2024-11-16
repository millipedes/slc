#pragma once

#include <optional>

#include "../parsing/parsing_ds.h"
#include "symbol_table.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

template <typename T>
auto extract_value(slcp::Expr& expr) -> std::optional<T> {
  if (std::holds_alternative<T>(expr.value())) {
    return std::get<T>(expr.value());
  }
  return std::nullopt;
}

template <typename T, typename... Ts>
auto extract_value(SymbolTableStack& sts, const std::string& name) -> std::optional<T> {
  auto name_it = sts.top().find(name);
  if (name_it != sts.top().end()) {
    if (auto value = extract_value<T>(sts.top().at(name))) {
      return value;
    }
    if constexpr (sizeof...(Ts) > 0) {
      return extract_value<Ts...>(sts, name);
    }
  }
  return std::nullopt;
}

auto read_in_values(slcp::Expr& expr, SymbolTableStack& sts) -> void;

extern auto opaque_eval_expr(slcp::Expr& value, SymbolTableStack& sts) -> slcp::Expr;

} // namespace SLCEvaluation
