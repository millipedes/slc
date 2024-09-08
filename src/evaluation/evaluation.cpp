#include "evaluation.h"

namespace SLCEvaluation {

auto evaluate_expression(slcp::Expr expr, SymbolTableStack& sts) -> slcp::Expr {
  if (std::holds_alternative<int>(expr.value())
      || std::holds_alternative<double>(expr.value())
      || std::holds_alternative<std::string>(expr.value())
      || std::holds_alternative<bool>(expr.value())) {
    return slcp::Expr(expr);
  } else if (std::holds_alternative<slcp::Expr::Variable>(expr.value())) {
    auto it = sts.top().find(std::get<slcp::Expr::Variable>(expr.value()).value);
    if (it != sts.top().end()) {
      return sts.top()[std::get<slcp::Expr::Variable>(expr.value()).value];
    } else {
      throw std::runtime_error("[evaluate_expression]: variable "
          + std::get<slcp::Expr::Variable>(expr.value()).value + " not defined");
    }
  } else if (std::holds_alternative<slcp::OpType>(expr.value())) {
    auto type = std::get<slcp::OpType>(expr.value());
    switch(type) {
      case slcp::OpType::UnMinus:
        return expr_unary_minus(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::Sin:
        return expr_sin(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::Cos:
        return expr_cos(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::Tan:
        return expr_tan(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::ArcSin:
        return expr_arcsin(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::ArcCos:
        return expr_arccos(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::ArcTan:
        return expr_arctan(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::Log:
        return expr_log(evaluate_expression(expr.child()[0], sts));
      case slcp::OpType::Ln:
        return expr_ln(evaluate_expression(expr.child()[0], sts));
      // case slcp::OpType::Array:
      // case slcp::OpType::ArrayAccessor:
      case slcp::OpType::BinPlus:
        return expr_addition(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinMinus:
        return expr_subtraction(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinMult:
        return expr_multiplication(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinDivide:
        return expr_division(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinMod:
        return expr_modulus(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinPow:
        return expr_pow(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinEq:
        return expr_eq(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinNeq:
        return expr_neq(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinGeq:
        return expr_geq(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinGt:
        return expr_gt(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinLeq:
        return expr_leq(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinLt:
        return expr_lt(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinBoolAnd:
        return expr_and(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BinBoolOr:
        return expr_or(evaluate_expression(expr.child()[0], sts),
            evaluate_expression(expr.child()[1], sts));
      case slcp::OpType::BoolNot:
        return expr_not(evaluate_expression(expr.child()[0], sts));
      // case slcp::OpType::BinAssignment:
      // case slcp::OpType::BinComma:
      // case slcp::OpType::Rectangle:
      // case slcp::OpType::Line:
      // case slcp::OpType::Ellipse:
      // case slcp::OpType::Canvas:
    }
  } else {
    throw std::runtime_error("[evaluate_expression]: something went very wrong");
  }
}

auto expr_unary_minus(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<int>(expr.value())) {
    return slcp::Expr(int_unary_minus(expr));
  } else if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_unary_minus(expr));
  } else {
    throw std::runtime_error("[expression_unary_minus]: unsupported type passed");
  }
}

auto expr_addition(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_addition(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_addition(left, right));
  } else if (std::holds_alternative<std::string>(left.value())
      && std::holds_alternative<std::string>(right.value())) {
    return slcp::Expr(string_addition(left, right));
  } else {
    throw std::runtime_error("[expression_addition]: unsupported type passed");
  }
}

auto expr_subtraction(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_subtraction(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_subtraction(left, right));
  } else {
    throw std::runtime_error("[expression_subtraction]: unsupported type passed");
  }
}

auto expr_multiplication(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_multiplication(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_multiplication(left, right));
  } else {
    throw std::runtime_error("[expression_multiplication]: unsupported type passed");
  }
}

auto expr_division(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_division(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_division(left, right));
  } else {
    throw std::runtime_error("[expression_division]: unsupported type passed");
  }
}

auto expr_modulus(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_modulus(left, right));
  } else {
    throw std::runtime_error("[expression_modulus]: unsupported type passed");
  }
}

auto expr_pow(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_pow(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_pow(left, right));
  } else {
    throw std::runtime_error("[expression_pow]: unsupported type passed");
  }
}

auto expr_eq(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_eq(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_eq(left, right));
  } else if (std::holds_alternative<std::string>(left.value())
      && std::holds_alternative<std::string>(right.value())) {
    return slcp::Expr(string_eq(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_eq(left, right));
  } else {
    throw std::runtime_error("[expression_eq]: unsupported type passed");
  }
}

auto expr_neq(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_neq(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_neq(left, right));
  } else if (std::holds_alternative<std::string>(left.value())
      && std::holds_alternative<std::string>(right.value())) {
    return slcp::Expr(string_neq(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_neq(left, right));
  } else {
    throw std::runtime_error("[expression_neq]: unsupported type passed");
  }
}

auto expr_geq(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_geq(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_geq(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_geq(left, right));
  } else {
    throw std::runtime_error("[expression_geq]: unsupported type passed");
  }
}

auto expr_gt(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_gt(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_gt(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_gt(left, right));
  } else {
    throw std::runtime_error("[expression_gt]: unsupported type passed");
  }
}

auto expr_leq(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_leq(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_leq(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_leq(left, right));
  } else {
    throw std::runtime_error("[expression_leq]: unsupported type passed");
  }
}

auto expr_lt(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<int>(left.value())
      && std::holds_alternative<int>(right.value())) {
    return slcp::Expr(int_lt(left, right));
  } else if (std::holds_alternative<double>(left.value())
      && std::holds_alternative<double>(right.value())) {
    return slcp::Expr(double_lt(left, right));
  } else if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_lt(left, right));
  } else {
    throw std::runtime_error("[expression_lt]: unsupported type passed");
  }
}

auto expr_sin(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_sin(expr));
  } else {
    throw std::runtime_error("[expression_sin]: unsupported type passed");
  }
}

auto expr_cos(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_cos(expr));
  } else {
    throw std::runtime_error("[expression_cos]: unsupported type passed");
  }
}

auto expr_tan(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_tan(expr));
  } else {
    throw std::runtime_error("[expression_tan]: unsupported type passed");
  }
}

auto expr_arcsin(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_arcsin(expr));
  } else {
    throw std::runtime_error("[expression_arcsin]: unsupported type passed");
  }
}

auto expr_arccos(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_arccos(expr));
  } else {
    throw std::runtime_error("[expression_arccos]: unsupported type passed");
  }
}

auto expr_arctan(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_arctan(expr));
  } else {
    throw std::runtime_error("[expression_arctan]: unsupported type passed");
  }
}

auto expr_log(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_log(expr));
  } else {
    throw std::runtime_error("[expression_log]: unsupported type passed");
  }
}

auto expr_ln(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<double>(expr.value())) {
    return slcp::Expr(double_ln(expr));
  } else {
    throw std::runtime_error("[expression_ln]: unsupported type passed");
  }
}

auto expr_and(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_and(left, right));
  } else {
    throw std::runtime_error("[expression_and]: unsupported type passed");
  }
}

auto expr_or(slcp::Expr left, slcp::Expr right) -> slcp::Expr {
  if (std::holds_alternative<bool>(left.value())
      && std::holds_alternative<bool>(right.value())) {
    return slcp::Expr(bool_or(left, right));
  } else {
    throw std::runtime_error("[expression_or]: unsupported type passed");
  }
}

auto expr_not(slcp::Expr expr) -> slcp::Expr {
  if (std::holds_alternative<bool>(expr.value())) {
    return slcp::Expr(bool_not(expr));
  } else {
    throw std::runtime_error("[expression_not]: unsupported type passed");
  }
}

// auto expr_shape(slcp::Expr expr, SymbolTableStack& sts) -> slcp::Expr {
//   slc_value result = {0};
//   result.type = SHAPE;
//   switch(the_shape.type) {
//     case ELLIPSE:
//       result.value.the_shape.type = ELLIPSE;
//       result.value.the_shape.value.the_ellipse = evaluate_ellipse(the_shape, st);
//       break;
//     case LINE:
//       result.value.the_shape.type = LINE;
//       result.value.the_shape.value.the_line = evaluate_line(the_shape, st);
//       break;
//     case RECTANGLE:
//       result.value.the_shape.type = RECTANGLE;
//       result.value.the_shape.value.the_rectangle = evaluate_rectangle(the_shape, st);
//       break;
//     case CANVAS:
//       result.value.the_shape.type = CANVAS;
//       result.value.the_shape.value.the_canvas = evaluate_canvas(the_shape, st);
//       break;
//   }
//   return result;
// }

// slc_value evaluate_array(parsed_array the_array, symbol_table * st) {
//   slc_value result = {0};
//   result.value.the_array = (array *)calloc(1, sizeof(struct ARRAY_T));
//   result.type = ARRAY;
//   for(uint32_t i = 0; i < the_array.qty_values; i++) {
//     switch(the_array.value_type[i]) {
//       case EXPR:
//         result.value.the_array[0]
//           = add_to_array(result.value.the_array[0], EXPR, &the_array.value[i].the_expr, st);
//         break;
//       case SHAPE:
//         result.value.the_array[0]
//           = add_to_array(result.value.the_array[0], SHAPE, &the_array.value[i].the_shape, st);
//         break;
//       case ARRAY:
//         result.value.the_array[0]
//           = add_to_array(result.value.the_array[0], ARRAY, the_array.value[i].the_array, st);
//         break;
//     }
//   }
//   return result;
// }
// 
// slc_value evaluate_slc_primitive(slc_primitive value, slc_primitive_type type, symbol_table * st) {
//   switch(type) {
//     case EXPR:
//       return evaluate_expression(value.the_expr, st);
//     case SHAPE:
//       return evaluate_shape(value.the_shape, st);
//     case ARRAY:
//       return evaluate_array(value.the_array[0], st);
//     default:
//       fprintf(stderr, "[EVALUATE_SLC_PRIMITIVE]: Unknown slc_primitive_type\n");
//       exit(1);
//   }
// }
// 
// void evaluate_lline(parsed_lline the_lline, symbol_table * st) {
//   // if
//   expression truth = {0};
//   // for
//   expression init = {0};
//   expression top_ex = {0};
//   expression bottom_ex = {0};
//   switch(the_lline.type) {
//     case ASSIGNMENT:
//       *st = add_slc_value_to_table(*st,
//           the_lline.value[0].the_expr.value.string_value,
//           evaluate_slc_primitive(the_lline.value[1], the_lline.value_type[1], st));
//       break;
//     case DRAW_STMT:
//       draw_shape(the_lline, st);
//       break;
//     case IF_STMT:
//       truth = evaluate_expression(the_lline.value[0].the_expr, st).value.the_expr;
//       if(truth.type == BOOL) {
//         if(truth.value.bool_value) {
//           for(uint32_t i = 0; i < the_lline.qty_children; i++) {
//             evaluate_lline(the_lline.child[i], st);
//           }
//         }
//       } else {
//         fprintf(stderr, "[EVALUATE_LLINE]: if statements only accepts boolean "
//             "values\n");
//         exit(1);
//       }
//       break;
//     case FOR_LOOP:
//       init = the_lline.value[0].the_expr;
//       top_ex = the_lline.qty_values == 2
//         ? evaluate_expression(the_lline.value[1].the_expr, st).value.the_expr
//         : evaluate_expression(the_lline.value[2].the_expr, st).value.the_expr;
//       bottom_ex = the_lline.qty_values == 2
//         ? (expression){0}
//         : evaluate_expression(the_lline.value[1].the_expr, st).value.the_expr;
//       if(top_ex.type == INT) {
//         for(int i = bottom_ex.value.int_value; i < top_ex.value.int_value; i++) {
//           *st = add_slc_value_to_table(*st, init.value.string_value,
//               (slc_value){(expression){{.int_value = i}, NULL, 0, INT}, EXPR});
//           for(uint32_t j = 0; j < the_lline.qty_children; j++) {
//             evaluate_lline(the_lline.child[j], st);
//           }
//         }
//       } else {
//         fprintf(stderr, "[EVALUATE_LLINE]: for loops only accepts integer "
//             "values\n");
//         exit(1);
//       }
//       break;
//   }
// }

auto opaque_eval_expr(slcp::Expr& value, SymbolTableStack& sts) -> slcp::Expr {
  return evaluate_expression(value, sts);
}

} // namespace SLCEvaluation
