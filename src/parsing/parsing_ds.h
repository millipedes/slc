#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace SLCParsing {

enum class OpType {
  UnMinus,
  Sin,
  Cos,
  Tan,
  ArcSin,
  ArcCos,
  ArcTan,
  Log,
  Ln,
  Array,
  ArrayAccessor,
  BinPlus,
  BinMinus,
  BinMult,
  BinDivide,
  BinMod,
  BinPow,
  BinEq,
  BinNeq,
  BinGeq,
  BinGt,
  BinLeq,
  BinLt,
  BinBoolAnd,
  BinBoolOr,
  BoolNot,
  BinAssignment,
  BinComma,
  Shape,
};

struct Expr {
  using Exprs = std::vector<Expr>;
  struct Variable { std::string value; };
  using ExprVariant = std::variant<int,         // Integer
                                   double,      // Double
                                   std::string, // String
                                   Variable,    // Variable
                                   bool,        // Bool
                                   OpType>;     // Operator

  public:
    Expr() = default;
    ~Expr() = default;

    Expr(const ExprVariant& value) : value_(value), child_(nullptr) {}

    Expr(const Expr& other) : value_(other.value_),
      child_(other.child_ ? std::make_unique<Exprs>(*other.child_) : nullptr) {}

    auto operator=(const Expr& other) -> Expr& {
      if (this != &other) {
        value_ = other.value_;
        child_ = other.child_ ? std::make_unique<Exprs>(*other.child_) : nullptr;
      }
      return *this;
    }

    auto operator=(Expr&& other) noexcept -> Expr& {
      if (this != &other) {
        value_ = std::move(other.value_);
        child_ = std::move(other.child_);
      }
      return *this;
    }

    auto operator==(const Expr& other) const -> bool;
    auto operator!=(const Expr& other) const -> bool;

    auto debug_expr(int indent) -> void;

    auto set_value(const ExprVariant& value) -> void { value_ = value; }
    auto value() -> ExprVariant { return value_; }

    auto set_child(std::unique_ptr<Exprs> child) -> void { child_ = std::move(child); }
    auto child() -> Exprs { return *child_; }

    auto add_children(Expr child) -> void {
      if (!child_) {
        child_ = std::make_unique<Exprs>(Exprs());
      }
      child_->push_back(child);
    }

    template <typename... Rest>
    auto add_children(Expr child, Rest... children) -> void {
      if (!child_) {
        child_ = std::make_unique<Exprs>(Exprs());
      }
      child_->push_back(child);
      add_children(children...);
    }

    auto add_children(ExprVariant child) -> void {
      if (!child_) {
        child_ = std::make_unique<Exprs>(Exprs());
      }
      child_->push_back(Expr(child));
    }

    template <typename... Rest>
    auto add_children(ExprVariant child, Rest... children) -> void {
      if (!child_) {
        child_ = std::make_unique<Exprs>(Exprs());
      }
      child_->push_back(Expr(child));
      add_children(children...);
    }

  private:
    ExprVariant value_;
    std::unique_ptr<Exprs> child_;
};

using Exprs = std::vector<Expr>;

enum class LLineType {
  Assignment,
  DrawStmt,
  IfStmt,
  ForLoop,
};

struct ParsedLLine {
  public:
    ParsedLLine() = default;
    ~ParsedLLine() = default;

    ParsedLLine(const ParsedLLine& other) : value_(other.value_),
      child_(other.child_ ? std::make_unique<ParsedLLine>(*other.child_) : nullptr),
      type_(other.type_) {}

    auto operator=(const ParsedLLine& other) -> ParsedLLine& {
      if (this != &other) {
        value_ = other.value_;
        child_ = other.child_ ? std::make_unique<ParsedLLine>(*other.child_) : nullptr;
        type_ = other.type_;
      }
      return *this;
    }

    auto operator=(ParsedLLine&& other) noexcept -> ParsedLLine& {
      if (this != &other) {
        value_ = std::move(other.value_);
        child_ = std::move(other.child_);
        type_ = other.type_;
      }
      return *this;
    }

    auto operator==(const ParsedLLine& other) const -> bool;

    auto set_value(const Exprs& value) -> void { value_ = value; }
    auto value() -> Exprs { return value_; }

    auto set_child(std::unique_ptr<ParsedLLine> child) -> void { child_ = std::move(child); }
    auto child() -> ParsedLLine { return *child_; }

    auto set_type(const LLineType& type) -> void { type_ = type; }
    auto type() -> LLineType { return type_; }

  private:
    Exprs value_;
    std::unique_ptr<ParsedLLine> child_;
    LLineType type_;
};

} // namespace SLCParsing
