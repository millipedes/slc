#pragma once

#include <stack>
#include <unordered_map>

#include "../parsing/parsing.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

using SymbolTable = std::unordered_map<std::string, slcp::Expr>;
using SymbolTableStack = std::stack<SymbolTable>;

} // namespace SLCEvaluation
