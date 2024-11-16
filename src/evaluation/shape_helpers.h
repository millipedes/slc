#pragma once

#include "../parsing/parsing_ds.h"
#include "symbol_table.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

auto read_in_values(slcp::Expr& expr, SymbolTableStack& sts) -> void;

extern auto opaque_eval_expr(slcp::Expr& value, SymbolTableStack& sts) -> slcp::Expr;

} // namespace SLCEvaluation
