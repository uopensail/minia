//
// `Minia` - A C++ tool for feature transformation and hashing
// Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
// This software is distributed under the GNU Affero General Public License
// (AGPL3.0) For more information, please visit:
// https://www.gnu.org/licenses/agpl-3.0.html
//
// This program is free software: you are free to redistribute and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
// GNU Affero General Public License for more details.
//

#ifndef MINIA_GRAMMAR_H_
#define MINIA_GRAMMAR_H_

#include <stack>
#include <unordered_map>

#include "../feature.h"
#include "miniaListener.h"

namespace minia {

/**
 * @brief Enumeration for expression types.
 */
enum ExprType : int8_t {
  kExprTypeError = 0, ///< Error expression type.
  kExprTypeLiteral,   ///< Literal expression type.
  kExprTypeVariable,  ///< Variable expression type.
  kExprTypeColumn,    ///< Column expression type.
};

/**
 * @brief Base structure for an expression.
 */
struct Expr {
  std::string name; ///< Name of the expression.
  ExprType type;    ///< Type of the expression.
  Expr(const std::string &name, const ExprType type = ExprType::kExprTypeError)
      : name(name), type(type) {}
  virtual ~Expr() = default;
};

/**
 * @brief Structure for a literal expression.
 */
struct Literal : Expr {
  FeaturePtr value; ///< Value of the literal.
  Literal(const std::string &name, const FeaturePtr &value)
      : Expr{name, ExprType::kExprTypeLiteral}, value(value) {}
};

/**
 * @brief Structure for a column expression.
 */
struct Column : Expr {
  Column(const std::string &name) : Expr{name, ExprType::kExprTypeColumn} {}
};

/**
 * @brief Structure for a variable expression.
 */
struct Variable : Expr {
  std::string func;                        ///< Function name for the variable.
  std::vector<std::shared_ptr<Expr>> args; ///< Arguments for the function.

  // Constructor
  Variable(const std::string &name, const std::string &func,
           const std::vector<std::shared_ptr<Expr>> &args)
      : Expr{name, ExprType::kExprTypeVariable}, func(func), args(args) {}
};

class MiniaListener : public miniaListener {
public:
  MiniaListener() : node_count_(0) {}
  ~MiniaListener() = default;

  // Override functions for parser rules
  virtual void enterProg([[maybe_unused]] miniaParser::ProgContext *ctx) {}
  virtual void exitProg([[maybe_unused]] miniaParser::ProgContext *ctx) {}

  virtual void enterStart([[maybe_unused]] miniaParser::StartContext *ctx) {}
  virtual void exitStart([[maybe_unused]] miniaParser::StartContext *ctx);

  virtual void enterExpr([[maybe_unused]] miniaParser::ExprContext *ctx) {}
  virtual void exitExpr([[maybe_unused]] miniaParser::ExprContext *ctx) {}

  virtual void enterOrExpr([[maybe_unused]] miniaParser::OrExprContext *ctx) {}
  virtual void exitOrExpr(miniaParser::OrExprContext *ctx);

  virtual void enterTrivialLogicalAndExpr([
      [maybe_unused]] miniaParser::TrivialLogicalAndExprContext *ctx) {}
  virtual void exitTrivialLogicalAndExpr([
      [maybe_unused]] miniaParser::TrivialLogicalAndExprContext *ctx) {}

  virtual void enterAndExpr([[maybe_unused]] miniaParser::AndExprContext *ctx) {
  }
  virtual void exitAndExpr(miniaParser::AndExprContext *ctx);

  virtual void enterTrivialEqualityExpr([
      [maybe_unused]] miniaParser::TrivialEqualityExprContext *ctx) {}
  virtual void exitTrivialEqualityExpr([
      [maybe_unused]] miniaParser::TrivialEqualityExprContext *ctx) {}

  virtual void enterEqualExpr([
      [maybe_unused]] miniaParser::EqualExprContext *ctx) {}
  virtual void exitEqualExpr(miniaParser::EqualExprContext *ctx);

  virtual void enterNotEqualExpr([
      [maybe_unused]] miniaParser::NotEqualExprContext *ctx) {}
  virtual void exitNotEqualExpr(miniaParser::NotEqualExprContext *ctx);

  virtual void enterTrivialRelationalExpr([
      [maybe_unused]] miniaParser::TrivialRelationalExprContext *ctx) {}
  virtual void exitTrivialRelationalExpr([
      [maybe_unused]] miniaParser::TrivialRelationalExprContext *ctx) {}

  virtual void enterGreaterThanExpr([
      [maybe_unused]] miniaParser::GreaterThanExprContext *ctx) {}
  virtual void exitGreaterThanExpr(miniaParser::GreaterThanExprContext *ctx);

  virtual void enterGreaterThanEqualExpr([
      [maybe_unused]] miniaParser::GreaterThanEqualExprContext *ctx) {}
  virtual void
  exitGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext *ctx);

  virtual void enterLessThanExpr([
      [maybe_unused]] miniaParser::LessThanExprContext *ctx) {}
  virtual void exitLessThanExpr(miniaParser::LessThanExprContext *ctx);

  virtual void enterLessThanEqualExpr([
      [maybe_unused]] miniaParser::LessThanEqualExprContext *ctx) {}
  virtual void
  exitLessThanEqualExpr(miniaParser::LessThanEqualExprContext *ctx);

  virtual void enterTrivialAdditiveExpr([
      [maybe_unused]] miniaParser::TrivialAdditiveExprContext *ctx) {}
  virtual void exitTrivialAdditiveExpr([
      [maybe_unused]] miniaParser::TrivialAdditiveExprContext *ctx) {}

  virtual void enterAddExpr([[maybe_unused]] miniaParser::AddExprContext *ctx) {
  }
  virtual void exitAddExpr(miniaParser::AddExprContext *ctx);

  virtual void enterSubExpr([[maybe_unused]] miniaParser::SubExprContext *ctx) {
  }
  virtual void exitSubExpr(miniaParser::SubExprContext *ctx);

  virtual void enterTrivialMultiplicativeExpr([
      [maybe_unused]] miniaParser::TrivialMultiplicativeExprContext *ctx) {}
  virtual void exitTrivialMultiplicativeExpr([
      [maybe_unused]] miniaParser::TrivialMultiplicativeExprContext *ctx) {}

  virtual void enterMulExpr([[maybe_unused]] miniaParser::MulExprContext *ctx) {
  }
  virtual void exitMulExpr(miniaParser::MulExprContext *ctx);

  virtual void enterDivExpr([[maybe_unused]] miniaParser::DivExprContext *ctx) {
  }
  virtual void exitDivExpr(miniaParser::DivExprContext *ctx);

  virtual void enterModExpr([[maybe_unused]] miniaParser::ModExprContext *ctx) {
  }
  virtual void exitModExpr(miniaParser::ModExprContext *ctx);

  virtual void enterTrivialUnaryExpr([
      [maybe_unused]] miniaParser::TrivialUnaryExprContext *ctx) {}
  virtual void exitTrivialUnaryExpr([
      [maybe_unused]] miniaParser::TrivialUnaryExprContext *ctx) {}

  virtual void enterNotExpr([[maybe_unused]] miniaParser::NotExprContext *ctx) {
  }
  virtual void exitNotExpr(miniaParser::NotExprContext *ctx);

  virtual void enterNegExpr([[maybe_unused]] miniaParser::NegExprContext *ctx) {
  }
  virtual void exitNegExpr(miniaParser::NegExprContext *ctx);

  virtual void enterTrivialPrimaryExpr([
      [maybe_unused]] miniaParser::TrivialPrimaryExprContext *ctx) {}
  virtual void exitTrivialPrimaryExpr([
      [maybe_unused]] miniaParser::TrivialPrimaryExprContext *ctx) {}

  virtual void enterParenthesizedExpr([
      [maybe_unused]] miniaParser::ParenthesizedExprContext *ctx) {}
  virtual void exitParenthesizedExpr([
      [maybe_unused]] miniaParser::ParenthesizedExprContext *ctx) {}

  virtual void enterFunctionCallExpr([
      [maybe_unused]] miniaParser::FunctionCallExprContext *ctx) {}
  virtual void exitFunctionCallExpr([
      [maybe_unused]] miniaParser::FunctionCallExprContext *ctx) {}

  virtual void enterColumnExpr([
      [maybe_unused]] miniaParser::ColumnExprContext *ctx) {}
  virtual void exitColumnExpr(miniaParser::ColumnExprContext *ctx);

  virtual void enterLiteralExpr([
      [maybe_unused]] miniaParser::LiteralExprContext *ctx) {}
  virtual void exitLiteralExpr([
      [maybe_unused]] miniaParser::LiteralExprContext *ctx) {}

  virtual void enterListExpr([
      [maybe_unused]] miniaParser::ListExprContext *ctx) {}
  virtual void exitListExpr([
      [maybe_unused]] miniaParser::ListExprContext *ctx) {}

  virtual void enterTrueExpr([
      [maybe_unused]] miniaParser::TrueExprContext *ctx) {}
  virtual void exitTrueExpr(miniaParser::TrueExprContext *ctx);

  virtual void enterFalseExpr([
      [maybe_unused]] miniaParser::FalseExprContext *ctx) {}
  virtual void exitFalseExpr(miniaParser::FalseExprContext *ctx);

  virtual void enterStringListExpr([
      [maybe_unused]] miniaParser::StringListExprContext *ctx) {}
  virtual void exitStringListExpr(miniaParser::StringListExprContext *ctx);

  virtual void enterIntegerListExpr([
      [maybe_unused]] miniaParser::IntegerListExprContext *ctx) {}
  virtual void exitIntegerListExpr(miniaParser::IntegerListExprContext *ctx);

  virtual void enterDecimalListExpr([
      [maybe_unused]] miniaParser::DecimalListExprContext *ctx) {}
  virtual void exitDecimalListExpr(miniaParser::DecimalListExprContext *ctx);

  virtual void enterFuncCall([
      [maybe_unused]] miniaParser::FuncCallContext *ctx) {}
  virtual void exitFuncCall(miniaParser::FuncCallContext *ctx);

  virtual void enterExprList([
      [maybe_unused]] miniaParser::ExprListContext *ctx) {}
  virtual void exitExprList([
      [maybe_unused]] miniaParser::ExprListContext *ctx) {}

  virtual void enterStringExpr([
      [maybe_unused]] miniaParser::StringExprContext *ctx) {}
  virtual void exitStringExpr(miniaParser::StringExprContext *ctx);

  virtual void enterIntegerExpr([
      [maybe_unused]] miniaParser::IntegerExprContext *ctx) {}
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext *ctx);

  virtual void enterDecimalExpr([
      [maybe_unused]] miniaParser::DecimalExprContext *ctx) {}
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext *ctx);

  // others
  virtual void visitTerminal([
      [maybe_unused]] antlr4::tree::TerminalNode *node) {}
  virtual void visitErrorNode([[maybe_unused]] antlr4::tree::ErrorNode *node) {}
  virtual void enterEveryRule([[maybe_unused]] antlr4::ParserRuleContext *ctx) {
  }
  virtual void exitEveryRule([[maybe_unused]] antlr4::ParserRuleContext *ctx) {}

private:
  std::shared_ptr<Expr> caluc(std::shared_ptr<Expr> expr);

private:
  std::stack<std::shared_ptr<Expr>> exprs_; ///< Stack to hold expressions.

public:
  int32_t node_count_; ///< Static count for expression tracking.
  std::vector<std::shared_ptr<Expr>>
      nodes_;                         ///< Vector to hold expression nodes.
  std::vector<std::string> features_; ///< Output features of the expressions
};

} // namespace minia

#endif // MINIA_GRAMMAR_H_