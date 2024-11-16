#include "shape_helpers.h"

namespace SLCEvaluation {

auto read_in_values(slcp::Expr& expr, SymbolTableStack& sts) -> void {
  auto not_pertinent = opaque_eval_expr(expr.child()[0], sts);
  // avoid the extra copy :(
  auto child_two = expr.child()[1];
  auto child_two_type = std::get<slcp::OpType>(child_two.value());
  switch (child_two_type) {
    case slcp::OpType::BinAssignment:
      not_pertinent = opaque_eval_expr(child_two, sts);
      break;
    case slcp::OpType::BinComma:
      read_in_values(child_two, sts);
      break;
    default:
      throw std::runtime_error("[local_canvas_sts]: something went very wrong");
  }
}

} // namespace SLCEvaluation
