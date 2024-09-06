#include "parsing_ds.h"

namespace SLCParsing {

auto Expr::operator==(const Expr& other) const -> bool {
  if (std::holds_alternative<int>(other.value_)
      && std::holds_alternative<int>(value_)) {
    return std::get<int>(other.value_) == std::get<int>(value_);
  } else if (std::holds_alternative<double>(other.value_)
      && std::holds_alternative<double>(value_)) {
    return std::get<double>(other.value_) == std::get<double>(value_);
  } else if (std::holds_alternative<std::string>(other.value_)
      && std::holds_alternative<std::string>(value_)) {
    return std::get<std::string>(other.value_) == std::get<std::string>(value_);
  } else if (std::holds_alternative<Variable>(other.value_)
      && std::holds_alternative<Variable>(value_)) {
    return std::get<Variable>(other.value_).value == std::get<Variable>(value_).value;
  } else if (std::holds_alternative<bool>(other.value_)
      && std::holds_alternative<bool>(value_)) {
    return std::get<bool>(other.value_) == std::get<bool>(value_);
  } else if (std::holds_alternative<OpType>(other.value_)
      && std::holds_alternative<OpType>(value_)) {
    return std::get<OpType>(other.value_) == std::get<OpType>(value_);
  } else if (std::holds_alternative<Shape>(other.value_)
      && std::holds_alternative<Shape>(value_)) {
    auto other_shape = std::get<Shape>(other.value_).value;
    auto shape = std::get<Shape>(value_).value;
    if (other_shape.size() != shape.size()) {
      return false;
    }
    for (uint32_t i = 0; i < shape.size(); i++) {
      if (!(shape[i] == other_shape[i])) {
        return false;
      }
    }
    return true;
  } else if (std::holds_alternative<Array>(other.value_)
      && std::holds_alternative<Array>(value_)) {
    auto other_array = std::get<Array>(other.value_).value;
    auto array = std::get<Array>(value_).value;
    if (other_array.size() != array.size()) {
      return false;
    }
    for (uint32_t i = 0; i < array.size(); i++) {
      if (!(array[i] == other_array[i])) {
        return false;
      }
    }
    return true;
  }
  return false;
}

auto Expr::debug_expr(int indent) -> void {
  for (uint32_t i = 0; i < 2 * indent; i++) {
    std::cout << " ";
  }
  if (std::holds_alternative<int>(value_)) {
    std::cout << std::get<int>(value_) << std::endl;
  } else if (std::holds_alternative<double>(value_)) {
    std::cout << std::get<double>(value_) << std::endl;
  } else if (std::holds_alternative<std::string>(value_)) {
    std::cout << std::get<std::string>(value_) << std::endl;
  } else if (std::holds_alternative<Variable>(value_)) {
    std::cout << std::get<Variable>(value_).value << std::endl;
  } else if (std::holds_alternative<bool>(value_)) {
    std::cout << std::get<bool>(value_) << std::endl;
  } else if (std::holds_alternative<OpType>(value_)) {
    switch(std::get<OpType>(value_)) {
      case OpType::UnMinus:
        std::cout << "-" << std::endl;
        break;
      case OpType::Sin:
        std::cout << "sin" << std::endl;
        break;
      case OpType::Cos:
        std::cout << "cos" << std::endl;
        break;
      case OpType::Tan:
        std::cout << "tan" << std::endl;
        break;
      case OpType::ArcSin:
        std::cout << "arcsin" << std::endl;
        break;
      case OpType::ArcCos:
        std::cout << "arccos" << std::endl;
        break;
      case OpType::ArcTan:
        std::cout << "arctan" << std::endl;
        break;
      case OpType::Log:
        std::cout << "log" << std::endl;
        break;
      case OpType::Ln:
        std::cout << "ln" << std::endl;
        break;
      case OpType::ArrayAccessor:
        std::cout << "[x]" << std::endl;
        break;
      case OpType::BinPlus:
        std::cout << "+" << std::endl;
        break;
      case OpType::BinMinus:
        std::cout << "-" << std::endl;
        break;
      case OpType::BinMult:
        std::cout << "*" << std::endl;
        break;
      case OpType::BinDivide:
        std::cout << "/" << std::endl;
        break;
      case OpType::BinMod:
        std::cout << "%" << std::endl;
        break;
      case OpType::BinPow:
        std::cout << "^" << std::endl;
        break;
      case OpType::BinEq:
        std::cout << "==" << std::endl;
        break;
      case OpType::BinNeq:
        std::cout << "!=" << std::endl;
        break;
      case OpType::BinGeq:
        std::cout << ">=" << std::endl;
        break;
      case OpType::BinGt:
        std::cout << ">" << std::endl;
        break;
      case OpType::BinLeq:
        std::cout << "<=" << std::endl;
        break;
      case OpType::BinLt:
        std::cout << "<" << std::endl;
        break;
      case OpType::BinBoolAnd:
        std::cout << "&&" << std::endl;
        break;
      case OpType::BinBoolOr:
        std::cout << "||" << std::endl;
        break;
      case OpType::BoolNot:
        std::cout << "!" << std::endl;
        break;
    }
  } else if (std::holds_alternative<Shape>(value_)) {
    for (auto& shape_mems : std::get<Shape>(value_).value) {
      shape_mems.debug_expr(indent);
    }
  } else if (std::holds_alternative<Array>(value_)) {
    for (auto& array_mems : std::get<Array>(value_).value) {
      array_mems.debug_expr(indent);
    }
  }
  if (child_) {
    for(auto& children : *child_) {
      children.debug_expr(indent + 1);
    }
  }
}

auto Expr::set_value(const ExprVariant& value) -> void {
  value_ = value;
}

auto Expr::set_child(std::unique_ptr<Exprs> child) -> void {
  child_ = std::move(child);
}

auto Expr::child() -> Exprs {
  return *child_;
}

} // namespace SLCParsing
