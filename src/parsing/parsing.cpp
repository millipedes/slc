#include "parsing.h"

namespace SLCParsing {

auto parse_ws(const char * input) -> const char * {
  if (input) {
    uint32_t inc = 0;
    while (is_whitespace(*(input + inc)) || *(input + inc) == '#') {
      if (*(input + inc) == '#') {
        while(*(input + inc) != '\n') {
          inc++;
        }
      }
      if (is_whitespace(*(input + inc))) {
        inc++;
      }
    }
    return input + inc;
  } else return NULL;
}

auto parse_variable_name(const char * input, Expr& expr) -> const char * {
  uint32_t inc = 0;
  while (isalpha(*(input + inc)) || *(input + inc) == '_') inc++;
  if (inc > 0) {
    expr.set_value(Expr::Variable{std::string(input, inc)});
    return input + inc;
  } else return NULL;
}

auto parse_number(const char * input, Expr& expr) -> const char * {
  uint32_t inc = 0;
  bool is_double = false;

  // decimal
  while (isdigit(*(input + inc))) inc++;

  if (*(input + inc) == '.') {
    is_double = true;
    inc++;
  } else if ((*(input + inc) == 'e' || *(input + inc) == 'E')
      && (*(input + inc + 1) == '-' || isdigit(*input + inc + 1))) {
    is_double = true;
    inc++;
    if (*(input + inc) == '-') inc++;
  }

  // fractional
  while (isdigit(*(input + inc))) inc++;

  if (is_double && inc > 0) {
    expr.set_value((double)strtod(input, NULL));
    return input + inc;
  } else if (inc > 0) {
    expr.set_value((int)strtol(input, NULL, 10));
    return input + inc;
  } else return NULL;
}

auto parse_string(const char * input, Expr& expr) -> const char * {
  uint32_t inc = 1;
  if (input[0] != '\"') {
    return NULL;
  }
  while (*(input + inc) != '\"') {
    if (*(input + inc) == '\0') return NULL;
    inc++;
  }
  inc++;
  expr.set_value(std::string(input + 1, inc - 2));
  return input + inc;
}

auto parse_word(const char * input, const char * word) -> const char * {
  if (input) {
    size_t len = strnlen(word, max_word_len);
    if (!strncmp(input, word, len)) {
      return input + len;
    } else return NULL;
  } else return NULL;
}

auto parse_bool(const char * input, Expr& expr) -> const char * {
  const char * true_str = "true";
  const size_t true_len = 4;
  const char * false_str = "false";
  const size_t false_len = 5;
  if (input) {
    if (!strncmp(input, true_str, true_len)) {
      expr.set_value(true);
      return input + true_len;
    } else if (!strncmp(input, false_str, false_len)) {
      expr.set_value(false);
      return input + false_len;
    } else return NULL;
  } else return NULL;
}

auto parse_array(const char * input, Expr& expr) -> const char * {
  const char * remainder = parse_word(parse_ws(input), "[");
  if (!remainder) return NULL;
  const char * delimiter;
  const char * maybe_array;
  const char * maybe_shape;
  const char * maybe_expr;
  Exprs child;
  uint32_t i = 0;
  while((delimiter = parse_word(parse_ws(remainder), "]")) == NULL) {
    child.push_back(Expr());
    if (maybe_array = parse_word(parse_ws(remainder), "[")) {
      remainder = parse_array(parse_ws(remainder), child[i]);
    } else if ((maybe_shape = parse_shape(parse_ws(remainder), child[i])) != NULL) {
      remainder = maybe_shape;
    } else if (maybe_expr = parse_precedence_12_expr(parse_ws(remainder), child[i])) {
      remainder = maybe_expr;
    }

    if (delimiter = parse_word(parse_ws(remainder), ",")) {
      remainder = delimiter;
    }
    i++;
  }
  expr.set_value(Expr::Array{child});
  return delimiter;
}

auto parse_shape(const char * input, Expr& expr) -> const char * {
  Exprs child;
  child.push_back(Expr());
  const char * remainder;
  if (!((remainder = parse_word(parse_ws(input), "rectangle"))
    || (remainder = parse_word(parse_ws(input), "ellipse"))
    || (remainder = parse_word(parse_ws(input), "line"))
    || (remainder = parse_word(parse_ws(input), "canvas")))) {
    return NULL;
  }
  const char * delimiter;
  uint32_t i = 1;

  if (remainder = parse_word(parse_ws(remainder), "(")) {
    while ((delimiter = parse_word(parse_ws(remainder), ")")) == NULL) {
      child.push_back(Expr());
      remainder = parse_precedence_4_expr(parse_ws(remainder), child[i]);
      i++;
      child.push_back(Expr());
      remainder = parse_precedence_4_expr(parse_ws(remainder), child[i]);
      i++;
      if (delimiter = parse_word(parse_ws(remainder), ",")) {
        remainder = delimiter;
      }
    }
    expr.set_value(Expr::Shape{child});
    return delimiter;
  } else return NULL;
}

auto parse_axiom(const char * input, Expr& expr) -> const char * {
  const char * maybe_axiom;
  if (maybe_axiom = parse_number(parse_ws(input), expr)) {
    return maybe_axiom;
  } else if (maybe_axiom = parse_bool(parse_ws(input), expr)) {
    return maybe_axiom;
  } else if (maybe_axiom = parse_shape(parse_ws(input), expr)) {
    return maybe_axiom;
  } else if (maybe_axiom = parse_string(parse_ws(input), expr)) {
    return maybe_axiom;
  } else if (maybe_axiom = parse_variable_name(parse_ws(input), expr)) {
    return maybe_axiom;
  } else if (maybe_axiom = parse_array(parse_ws(input), expr)) {
    return maybe_axiom;
  } else return NULL;
}

auto make_unary_tree(const char * input, Expr& expr, Exprs& child,
    OpType type, std::function<const char *(const char *, Expr&)> parser) -> const char * {
  expr = Expr(type);
  input = parser(parse_ws(input), child[0]);
  if (!input) return NULL;
  expr.set_child(std::make_unique<Exprs>(child));
  return input;
}

auto make_binary_tree(const char * input, Expr& expr, Exprs& child,
    OpType type, std::function<const char *(const char *, Expr&)> parser) -> const char * {
    Expr parent = Expr(type);
    child[0] = expr;
    child.push_back(Expr());
    input = parser(parse_ws(input), child[1]);
    if (!input) return NULL;
    parent.set_child(std::make_unique<Exprs>(child));
    expr = parent;
    return input;
}

auto parse_precedence_1_expr(const char * input, Expr& expr) -> const char * {
  const char * factor;
  Exprs child;
  child.push_back(Expr());
  if (factor = parse_word(parse_ws(input), "-")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::UnMinus, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "!")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::BoolNot, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "sin")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::Sin, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "cos")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::Cos, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "tan")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::Tan, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "arcsin")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::ArcSin, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "arccos")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::ArcCos, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "arctan")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::ArcTan, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "log")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::Log, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "ln")) {
    return make_unary_tree(parse_ws(factor), expr, child,
        OpType::Ln, parse_precedence_1_expr);
  } else if (factor = parse_word(parse_ws(input), "(")) {
    factor = parse_precedence_12_expr(parse_ws(factor), expr);
    factor = parse_word(parse_ws(factor), ")");
  } else {
    factor = parse_axiom(parse_ws(input), expr);
  }
  const char * maybe_factor;
  if (maybe_factor = parse_word(parse_ws(factor), "^")) {
    return make_binary_tree(parse_ws(maybe_factor), expr, child,
        OpType::BinPow, parse_precedence_3_expr);
  }
  const char * maybe_accessors;
  if (maybe_accessors = parse_word(parse_ws(factor), "[")) {
    Expr parent = expr;
    Expr accessor_parent = Expr(OpType::ArrayAccessor);
    maybe_accessors = parse_precedence_4_expr(parse_ws(maybe_accessors), child[0]);
    maybe_accessors = parse_word(parse_ws(maybe_accessors), "]");
    factor = maybe_accessors;
    uint32_t i = 1;
    while (maybe_accessors = parse_word(parse_ws(factor), "[")) {
      child.push_back(Expr());
      maybe_accessors = parse_precedence_4_expr(parse_ws(maybe_accessors), child[i]);
      maybe_accessors = parse_word(parse_ws(maybe_accessors), "]");
      factor = maybe_accessors;
      i++;
    }
    accessor_parent.set_child(std::make_unique<Exprs>(child));
    parent.set_child(std::make_unique<Exprs>(Exprs{accessor_parent}));
    expr = parent;
  }
  return factor;
}

auto parse_precedence_3_expr(const char * input, Expr& expr) -> const char * {
  const char * factor = parse_precedence_1_expr(parse_ws(input), expr);
  const char * maybe_term;
  Exprs child;
  child.push_back(Expr());
  if (factor) {
    if (maybe_term = parse_word(parse_ws(factor), "*")) {
      return make_binary_tree(parse_ws(maybe_term), expr, child,
          OpType::BinMult, parse_precedence_3_expr);
    } else if (maybe_term = parse_word(parse_ws(factor), "/")) {
      return make_binary_tree(parse_ws(maybe_term), expr, child,
          OpType::BinDivide, parse_precedence_3_expr);
    } else if (maybe_term = parse_word(parse_ws(factor), "%")) {
      return make_binary_tree(parse_ws(maybe_term), expr, child,
          OpType::BinMod, parse_precedence_3_expr);
    } else return factor;
  } else return NULL;
}

auto parse_precedence_4_expr(const char * input, Expr& expr) -> const char * {
  const char * term = parse_precedence_3_expr(parse_ws(input), expr);
  const char * maybe_expression;
  Exprs child;
  child.push_back(Expr());
  if (term) {
    if (maybe_expression = parse_word(parse_ws(term), "+")) {
      return make_binary_tree(parse_ws(maybe_expression), expr, child,
          OpType::BinPlus, parse_precedence_4_expr);
    } else if (maybe_expression = parse_word(parse_ws(term), "-")) {
      return make_binary_tree(parse_ws(maybe_expression), expr, child,
          OpType::BinMinus, parse_precedence_4_expr);
    } else return term;
  } else return NULL;
}

auto parse_precedence_6_expr(const char * input, Expr& expr) -> const char * {
  const char * expression = parse_precedence_4_expr(parse_ws(input), expr);
  const char * maybe_boolean_expr;
  Exprs child;
  child.push_back(Expr());
  if (expression) {
    if (maybe_boolean_expr = parse_word(parse_ws(expression), ">=")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinGeq, parse_precedence_4_expr);
    } else if (maybe_boolean_expr = parse_word(parse_ws(expression), ">")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinGt, parse_precedence_4_expr);
    } else if (maybe_boolean_expr = parse_word(parse_ws(expression), "<=")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinLeq, parse_precedence_4_expr);
    } else if (maybe_boolean_expr = parse_word(parse_ws(expression), "<")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinLt, parse_precedence_4_expr);
    } else return expression;

  } else return NULL;
}

auto parse_precedence_7_expr(const char * input, Expr& expr) -> const char * {
  const char * expression = parse_precedence_6_expr(parse_ws(input), expr);
  const char * maybe_boolean_expr;
  Exprs child;
  child.push_back(Expr());
  if (expression) {
    if (maybe_boolean_expr = parse_word(parse_ws(expression), "==")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinEq, parse_precedence_4_expr);
    } else if (maybe_boolean_expr = parse_word(parse_ws(expression), "!=")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinNeq, parse_precedence_4_expr);
    } else return expression;
  } else return NULL;
}

auto parse_precedence_11_expr(const char * input, Expr& expr) -> const char * {
  const char * expression = parse_precedence_7_expr(parse_ws(input), expr);
  const char * maybe_boolean_expr;
  Exprs child;
  child.push_back(Expr());
  if (expression) {
    if (maybe_boolean_expr = parse_word(parse_ws(expression), "&&")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinBoolAnd, parse_precedence_11_expr);
    } else return expression;
  } else return NULL;
}

auto parse_precedence_12_expr(const char * input, Expr& expr) -> const char * {
  const char * expression = parse_precedence_11_expr(parse_ws(input), expr);
  const char * maybe_boolean_expr;
  Exprs child;
  child.push_back(Expr());
  if (expression) {
    if (maybe_boolean_expr = parse_word(parse_ws(expression), "||")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinBoolOr, parse_precedence_12_expr);
    } else return expression;
  } else return NULL;
}

auto parse_precedence_14_expr(const char * input, Expr& expr) -> const char * {
  const char * expression = parse_precedence_12_expr(parse_ws(input), expr);
  const char * maybe_boolean_expr;
  Exprs child;
  child.push_back(Expr());
  if (expression) {
    if (maybe_boolean_expr = parse_word(parse_ws(expression), "=")) {
      return make_binary_tree(parse_ws(maybe_boolean_expr), expr, child,
          OpType::BinAssignment, parse_precedence_14_expr);
    } else return expression;
  } else return NULL;
}

auto is_double_delineator(char c) -> bool {
  return c == '.' || c == 'e' || c == 'E';
}

auto is_whitespace(char c) -> bool {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f';
}

auto parse_top_level_expr(const char * input, Expr& expr) -> const char * {
  // Array?
  const char * maybe_array_remainder;
  if (maybe_array_remainder = parse_array(parse_ws(input), expr)) {
    return maybe_array_remainder;
  }
  // Shape?
  const char * maybe_shape_remainder;
  if (maybe_shape_remainder = parse_shape(parse_ws(input), expr)) {
    return maybe_shape_remainder;
  }
  // Expression?
  const char * maybe_expr_remainder;
  if (maybe_expr_remainder = parse_precedence_12_expr(parse_ws(input), expr)) {
    return maybe_expr_remainder;
  } else return NULL;
}

auto parse_assignment(const char * input, ParsedLLine& lline) -> const char * {
  Exprs values;
  values.push_back(Expr());
  const char * remainder = parse_variable_name(parse_ws(input), values[0]);
  if (remainder) {
    if (remainder = parse_word(parse_ws(remainder), "=")) {
      values.push_back(Expr());
      if (remainder = parse_top_level_expr(parse_ws(remainder), values[1])) {
        if (remainder = parse_word(parse_ws(remainder), ";")) {
          lline.set_type(LLineType::Assignment);
          lline.set_value(values);
          return remainder;
        } else return NULL;
      } else return NULL;
    } else return NULL;
  } else return NULL;
}

// const char * parse_draw_statement(const char * input, void * data) {
//   const char * remainder;
//   if (remainder = parse_word(parse_ws(input), (void *)"draw")) {
//     if (remainder = parse_word(parse_ws(remainder), (void *)"(")) {
//       remainder = parse_slc_primitive(parse_ws(remainder), data);
//       const char * maybe_into;
//       parsed_lline * the_lline = (parsed_lline *)data;
//       the_lline->type = DRAW_STMT;
//       remainder = parse_word(parse_ws(remainder), (void *)")");
//       if (maybe_into = parse_word(parse_ws(remainder), (void *)";")) {
//         return parse_word(parse_ws(remainder), (void *)";");
//       } else if (maybe_into = parse_word(parse_ws(remainder), (void *)"->")) {
//         remainder = maybe_into;
//         remainder = parse_slc_primitive(parse_ws(remainder), data);
//         return parse_word(parse_ws(remainder), (void *)";");
//       } else return NULL;
//     } else return NULL;
//   } else return NULL;
// }
// 
// const char * parse_if_statement(const char * input, void * data) {
//   const char * remainder;
//   if (remainder = parse_word(parse_ws(input), (void *)"if")) {
//     expression truth = {0};
//     if (remainder = parse_precedence_12_expr(parse_ws(remainder), &truth)) {
//       if (remainder = parse_word(parse_ws(remainder), (void *)"{")) {
//         parsed_lline new_child = {0};
//         parsed_lline * parent = (parsed_lline *)data;
//         const char * close_squirrely_brace;
//         while((close_squirrely_brace = parse_word(parse_ws(remainder), (void *)"}")) == NULL) {
//           remainder = parse_lline(parse_ws(remainder), &new_child);
//           *parent = add_child_to_lline(*parent, new_child);
//           new_child = (parsed_lline){0};
//         }
//         *parent = add_primitive_to_lline(*parent, EXPR, &truth);
//         parent->type = IF_STMT;
//         return close_squirrely_brace;
//       } else return NULL;
//     } else return NULL;
//   } else return NULL;
// }
// 
// const char * parse_for_loop(const char * input, void * data) {
//   const char * remainder;
//   if (remainder = parse_word(parse_ws(input), (void *)"for")) {
//     expression init = {0};
//     if (!(remainder = parse_variable_name(parse_ws(remainder), &init))) return NULL;
//     if (!(remainder = parse_word(parse_ws(remainder), (void *)"in"))) return NULL;
//     if (!(remainder = parse_word(parse_ws(remainder), (void *)"range"))) return NULL;
//     // "range (" -> we should accept this
//     if (!(remainder = parse_word(parse_ws(remainder), (void *)"("))) return NULL;
//     expression top_ex = {0};
//     if (!(remainder = parse_precedence_12_expr(parse_ws(remainder), &top_ex))) return NULL;
//     parsed_lline * parent = (parsed_lline *)data;
//     const char * maybe_comma;
//     if (maybe_comma = parse_word(parse_ws(remainder), (void *)",")) {
//       expression bottom_ex = {0};
//       if (maybe_comma = parse_precedence_12_expr(parse_ws(maybe_comma), &bottom_ex)) {
//         *parent = add_primitive_to_lline(*parent, EXPR, &init);
//         *parent = add_primitive_to_lline(*parent, EXPR, &top_ex);
//         *parent = add_primitive_to_lline(*parent, EXPR, &bottom_ex);
//         remainder = maybe_comma;
//       } else return NULL;
//     } else {
//       *parent = add_primitive_to_lline(*parent, EXPR, &init);
//       *parent = add_primitive_to_lline(*parent, EXPR, &top_ex);
//     }
//     if (!(remainder = parse_word(parse_ws(remainder), (void *)")"))) return NULL;
//     if (remainder = parse_word(parse_ws(remainder), (void *)"{")) {
//       parsed_lline new_child = {0};
//       const char * close_squirrely_brace;
//       while((close_squirrely_brace = parse_word(parse_ws(remainder), (void *)"}")) == NULL) {
//         remainder = parse_lline(parse_ws(remainder), &new_child);
//         *parent = add_child_to_lline(*parent, new_child);
//         new_child = (parsed_lline){0};
//       }
//       parent->type = FOR_LOOP;
//       return close_squirrely_brace;
//     } else return NULL;
//   } else return NULL;
// }
// 
// const char * parse_lline(const char * input, void * data) {
//   return or_p(input, data, 4,
//       parse_for_loop,
//       parse_if_statement,
//       parse_assignment,
//       parse_draw_statement);
// }

} // namespace SLCParsing
