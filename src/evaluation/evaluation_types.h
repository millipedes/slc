#pragma once

// #include "ellipse.h"
// #include "rectangle.h"
#include "canvas.h"

namespace slcp = SLCParsing;

namespace SLCEvaluation {

using Shape = std::variant<Canvas>;
using ValueVariant = std::variant<slcp::Expr, Shape>;

struct Value {
  Value(const ValueVariant& value) : value(value) {}

  ValueVariant value;
};

} // namespace SLCEvaluation
