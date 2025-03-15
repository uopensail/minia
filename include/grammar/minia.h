//
// `Minia` - A C++ tool for feature transformation and hashing
// Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
// This software is distributed under the GNU Affero General Public License (AGPL3.0)
// For more information, please visit: https://www.gnu.org/licenses/agpl-3.0.html
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

#include "../feature.h"
#include "miniaListener.h"
#include <stack>
#include <unordered_map>

namespace minia {

static int32_t g_node_count = 0; ///< Static count for expression tracking.

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
    Expr(const std::string &name,
         const ExprType type = ExprType::kExprTypeError)
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
    std::string func; ///< Function name for the variable.
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

    virtual void enterMulExpr(miniaParser::MulExprContext *ctx) {}
    virtual void exitMulExpr(miniaParser::MulExprContext *ctx);

    virtual void enterStringExpr(miniaParser::StringExprContext *ctx) {}
    virtual void exitStringExpr(miniaParser::StringExprContext *ctx);

    virtual void
    enterDecimalLISTExpr(miniaParser::DecimalLISTExprContext *ctx) {}
    virtual void exitDecimalLISTExpr(miniaParser::DecimalLISTExprContext *ctx);

    virtual void enterPlainExpr(miniaParser::PlainExprContext *ctx) {}
    virtual void exitPlainExpr(miniaParser::PlainExprContext *ctx) {}

    virtual void enterColumnExpr(miniaParser::ColumnExprContext *ctx) {}
    virtual void exitColumnExpr(miniaParser::ColumnExprContext *ctx);

    virtual void enterSubExpr(miniaParser::SubExprContext *ctx) {}
    virtual void exitSubExpr(miniaParser::SubExprContext *ctx);

    virtual void enterAddExpr(miniaParser::AddExprContext *ctx) {}
    virtual void exitAddExpr(miniaParser::AddExprContext *ctx);

    virtual void enterFuncExpr(miniaParser::FuncExprContext *ctx) {}
    virtual void exitFuncExpr(miniaParser::FuncExprContext *ctx);

    virtual void enterDecimalExpr(miniaParser::DecimalExprContext *ctx) {}
    virtual void exitDecimalExpr(miniaParser::DecimalExprContext *ctx);

    virtual void enterStringLISTExpr(miniaParser::StringLISTExprContext *ctx) {}
    virtual void exitStringLISTExpr(miniaParser::StringLISTExprContext *ctx);

    virtual void
    enterRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext *ctx) {}
    virtual void
    exitRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext *ctx);

    virtual void enterIntegerExpr(miniaParser::IntegerExprContext *ctx) {}
    virtual void exitIntegerExpr(miniaParser::IntegerExprContext *ctx);

    virtual void enterDivExpr(miniaParser::DivExprContext *ctx) {}
    virtual void exitDivExpr(miniaParser::DivExprContext *ctx);

    virtual void enterModExpr(miniaParser::ModExprContext *ctx) {}
    virtual void exitModExpr(miniaParser::ModExprContext *ctx);

    virtual void
    enterIntegerLISTExpr(miniaParser::IntegerLISTExprContext *ctx) {}
    virtual void exitIntegerLISTExpr(miniaParser::IntegerLISTExprContext *ctx);

    virtual void visitTerminal(antlr4::tree::TerminalNode *node) {}
    virtual void visitErrorNode(antlr4::tree::ErrorNode *node) {}
    virtual void enterEveryRule(antlr4::ParserRuleContext *ctx) {}
    virtual void exitEveryRule(antlr4::ParserRuleContext *ctx) {}

  private:
    std::stack<std::shared_ptr<Expr>> exprs_; ///< Stack to hold expressions.
  public:
    std::vector<std::shared_ptr<Expr>>
        nodes_; ///< Vector to hold expression nodes.
};

} // namespace minia

#endif // MINIA_GRAMMAR_H_