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

static int32_t g_node_count; ///< Static count for expression tracking.

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
  MiniaListener() = default;
  ~MiniaListener() = default;

  // Override functions for parser rules
  virtual void enterProg(miniaParser::ProgContext *ctx) {}
  virtual void exitProg(miniaParser::ProgContext *ctx) {}

  virtual void enterStart(miniaParser::StartContext *ctx) {}
  virtual void exitStart(miniaParser::StartContext *ctx);

  virtual void enterExpr(miniaParser::ExprContext *ctx) {}
  virtual void exitExpr(miniaParser::ExprContext *ctx) {}

  virtual void enterOrExpr(miniaParser::OrExprContext *ctx) {}
  virtual void exitOrExpr(miniaParser::OrExprContext *ctx);

  virtual void
  enterTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext *ctx) {}
  virtual void
  exitTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext *ctx) {}

  virtual void enterAndExpr(miniaParser::AndExprContext *ctx) {}
  virtual void exitAndExpr(miniaParser::AndExprContext *ctx);

  virtual void
  enterTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext *ctx) {}
  virtual void
  exitTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext *ctx) {}

  virtual void enterEqualExpr(miniaParser::EqualExprContext *ctx) {}
  virtual void exitEqualExpr(miniaParser::EqualExprContext *ctx);

  virtual void enterNotEqualExpr(miniaParser::NotEqualExprContext *ctx) {}
  virtual void exitNotEqualExpr(miniaParser::NotEqualExprContext *ctx);

  virtual void
  enterTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext *ctx) {}
  virtual void
  exitTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext *ctx) {}

  virtual void enterGreaterThanExpr(miniaParser::GreaterThanExprContext *ctx) {}
  virtual void exitGreaterThanExpr(miniaParser::GreaterThanExprContext *ctx);

  virtual void
  enterGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext *ctx) {}
  virtual void
  exitGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext *ctx);

  virtual void enterLessThanExpr(miniaParser::LessThanExprContext *ctx) {}
  virtual void exitLessThanExpr(miniaParser::LessThanExprContext *ctx);

  virtual void
  enterLessThanEqualExpr(miniaParser::LessThanEqualExprContext *ctx) {}
  virtual void
  exitLessThanEqualExpr(miniaParser::LessThanEqualExprContext *ctx);

  virtual void
  enterTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext *ctx) {}
  virtual void
  exitTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext *ctx) {}

  virtual void enterAddExpr(miniaParser::AddExprContext *ctx) {}
  virtual void exitAddExpr(miniaParser::AddExprContext *ctx);

  virtual void enterSubExpr(miniaParser::SubExprContext *ctx) {}
  virtual void exitSubExpr(miniaParser::SubExprContext *ctx);

  virtual void enterTrivialMultiplicativeExpr(
      miniaParser::TrivialMultiplicativeExprContext *ctx) {}
  virtual void exitTrivialMultiplicativeExpr(
      miniaParser::TrivialMultiplicativeExprContext *ctx) {}

  virtual void enterMulExpr(miniaParser::MulExprContext *ctx) {}
  virtual void exitMulExpr(miniaParser::MulExprContext *ctx);

  virtual void enterDivExpr(miniaParser::DivExprContext *ctx) {}
  virtual void exitDivExpr(miniaParser::DivExprContext *ctx);

  virtual void enterModExpr(miniaParser::ModExprContext *ctx) {}
  virtual void exitModExpr(miniaParser::ModExprContext *ctx);

  virtual void
  enterTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext *ctx) {}
  virtual void exitTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext *ctx) {
  }

  virtual void enterNotExpr(miniaParser::NotExprContext *ctx) {}
  virtual void exitNotExpr(miniaParser::NotExprContext *ctx);

  virtual void enterNegExpr(miniaParser::NegExprContext *ctx) {}
  virtual void exitNegExpr(miniaParser::NegExprContext *ctx);

  virtual void
  enterTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext *ctx) {}
  virtual void
  exitTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext *ctx) {}

  virtual void
  enterParenthesizedExpr(miniaParser::ParenthesizedExprContext *ctx) {}
  virtual void
  exitParenthesizedExpr(miniaParser::ParenthesizedExprContext *ctx) {}

  virtual void
  enterFunctionCallExpr(miniaParser::FunctionCallExprContext *ctx) {}
  virtual void exitFunctionCallExpr(miniaParser::FunctionCallExprContext *ctx) {
  }

  virtual void enterColumnExpr(miniaParser::ColumnExprContext *ctx) {}
  virtual void exitColumnExpr(miniaParser::ColumnExprContext *ctx);

  virtual void enterLiteralExpr(miniaParser::LiteralExprContext *ctx) {}
  virtual void exitLiteralExpr(miniaParser::LiteralExprContext *ctx) {}

  virtual void enterListExpr(miniaParser::ListExprContext *ctx) {}
  virtual void exitListExpr(miniaParser::ListExprContext *ctx) {}

  virtual void enterTrueExpr(miniaParser::TrueExprContext *ctx) {}
  virtual void exitTrueExpr(miniaParser::TrueExprContext *ctx);

  virtual void enterFalseExpr(miniaParser::FalseExprContext *ctx) {}
  virtual void exitFalseExpr(miniaParser::FalseExprContext *ctx);

  virtual void enterStringListExpr(miniaParser::StringListExprContext *ctx) {}
  virtual void exitStringListExpr(miniaParser::StringListExprContext *ctx);

  virtual void enterIntegerListExpr(miniaParser::IntegerListExprContext *ctx) {}
  virtual void exitIntegerListExpr(miniaParser::IntegerListExprContext *ctx);

  virtual void enterDecimalListExpr(miniaParser::DecimalListExprContext *ctx) {}
  virtual void exitDecimalListExpr(miniaParser::DecimalListExprContext *ctx);

  virtual void enterFuncCall(miniaParser::FuncCallContext *ctx) {}
  virtual void exitFuncCall(miniaParser::FuncCallContext *ctx);

  virtual void enterExprList(miniaParser::ExprListContext *ctx) {}
  virtual void exitExprList(miniaParser::ExprListContext *ctx) {}

  virtual void enterStringExpr(miniaParser::StringExprContext *ctx) {}
  virtual void exitStringExpr(miniaParser::StringExprContext *ctx);

  virtual void enterIntegerExpr(miniaParser::IntegerExprContext *ctx) {}
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext *ctx);

  virtual void enterDecimalExpr(miniaParser::DecimalExprContext *ctx) {}
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext *ctx);

  // others
  virtual void visitTerminal(antlr4::tree::TerminalNode *node) {}
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) {}
  virtual void enterEveryRule(antlr4::ParserRuleContext *ctx) {}
  virtual void exitEveryRule(antlr4::ParserRuleContext *ctx) {}

private:
  std::shared_ptr<Expr> caluc(std::shared_ptr<Expr> expr);

private:
  std::stack<std::shared_ptr<Expr>> exprs_; ///< Stack to hold expressions.

public:
  std::vector<std::shared_ptr<Expr>>
      nodes_;                         ///< Vector to hold expression nodes.
  std::vector<std::string> features_; ///< Output features of the expressions
};

} // namespace minia

#endif // MINIA_GRAMMAR_H_