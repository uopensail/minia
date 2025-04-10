
// Generated from minia.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "miniaParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by miniaParser.
 */
class  miniaListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(miniaParser::ProgContext *ctx) = 0;
  virtual void exitProg(miniaParser::ProgContext *ctx) = 0;

  virtual void enterStart(miniaParser::StartContext *ctx) = 0;
  virtual void exitStart(miniaParser::StartContext *ctx) = 0;

  virtual void enterExpr(miniaParser::ExprContext *ctx) = 0;
  virtual void exitExpr(miniaParser::ExprContext *ctx) = 0;

  virtual void enterOrExpr(miniaParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(miniaParser::OrExprContext *ctx) = 0;

  virtual void enterTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext *ctx) = 0;
  virtual void exitTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext *ctx) = 0;

  virtual void enterAndExpr(miniaParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(miniaParser::AndExprContext *ctx) = 0;

  virtual void enterTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext *ctx) = 0;
  virtual void exitTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext *ctx) = 0;

  virtual void enterEqualExpr(miniaParser::EqualExprContext *ctx) = 0;
  virtual void exitEqualExpr(miniaParser::EqualExprContext *ctx) = 0;

  virtual void enterNotEqualExpr(miniaParser::NotEqualExprContext *ctx) = 0;
  virtual void exitNotEqualExpr(miniaParser::NotEqualExprContext *ctx) = 0;

  virtual void enterTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext *ctx) = 0;
  virtual void exitTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext *ctx) = 0;

  virtual void enterGreaterThanExpr(miniaParser::GreaterThanExprContext *ctx) = 0;
  virtual void exitGreaterThanExpr(miniaParser::GreaterThanExprContext *ctx) = 0;

  virtual void enterGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext *ctx) = 0;
  virtual void exitGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext *ctx) = 0;

  virtual void enterLessThanExpr(miniaParser::LessThanExprContext *ctx) = 0;
  virtual void exitLessThanExpr(miniaParser::LessThanExprContext *ctx) = 0;

  virtual void enterLessThanEqualExpr(miniaParser::LessThanEqualExprContext *ctx) = 0;
  virtual void exitLessThanEqualExpr(miniaParser::LessThanEqualExprContext *ctx) = 0;

  virtual void enterTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext *ctx) = 0;
  virtual void exitTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext *ctx) = 0;

  virtual void enterAddExpr(miniaParser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(miniaParser::AddExprContext *ctx) = 0;

  virtual void enterSubExpr(miniaParser::SubExprContext *ctx) = 0;
  virtual void exitSubExpr(miniaParser::SubExprContext *ctx) = 0;

  virtual void enterTrivialMultiplicativeExpr(miniaParser::TrivialMultiplicativeExprContext *ctx) = 0;
  virtual void exitTrivialMultiplicativeExpr(miniaParser::TrivialMultiplicativeExprContext *ctx) = 0;

  virtual void enterMulExpr(miniaParser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(miniaParser::MulExprContext *ctx) = 0;

  virtual void enterDivExpr(miniaParser::DivExprContext *ctx) = 0;
  virtual void exitDivExpr(miniaParser::DivExprContext *ctx) = 0;

  virtual void enterModExpr(miniaParser::ModExprContext *ctx) = 0;
  virtual void exitModExpr(miniaParser::ModExprContext *ctx) = 0;

  virtual void enterTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext *ctx) = 0;
  virtual void exitTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext *ctx) = 0;

  virtual void enterNotExpr(miniaParser::NotExprContext *ctx) = 0;
  virtual void exitNotExpr(miniaParser::NotExprContext *ctx) = 0;

  virtual void enterTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext *ctx) = 0;
  virtual void exitTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext *ctx) = 0;

  virtual void enterParenthesizedExpr(miniaParser::ParenthesizedExprContext *ctx) = 0;
  virtual void exitParenthesizedExpr(miniaParser::ParenthesizedExprContext *ctx) = 0;

  virtual void enterFunctionCallExpr(miniaParser::FunctionCallExprContext *ctx) = 0;
  virtual void exitFunctionCallExpr(miniaParser::FunctionCallExprContext *ctx) = 0;

  virtual void enterColumnExpr(miniaParser::ColumnExprContext *ctx) = 0;
  virtual void exitColumnExpr(miniaParser::ColumnExprContext *ctx) = 0;

  virtual void enterLiteralExpr(miniaParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(miniaParser::LiteralExprContext *ctx) = 0;

  virtual void enterListExpr(miniaParser::ListExprContext *ctx) = 0;
  virtual void exitListExpr(miniaParser::ListExprContext *ctx) = 0;

  virtual void enterTrueExpr(miniaParser::TrueExprContext *ctx) = 0;
  virtual void exitTrueExpr(miniaParser::TrueExprContext *ctx) = 0;

  virtual void enterFalseExpr(miniaParser::FalseExprContext *ctx) = 0;
  virtual void exitFalseExpr(miniaParser::FalseExprContext *ctx) = 0;

  virtual void enterStringListExpr(miniaParser::StringListExprContext *ctx) = 0;
  virtual void exitStringListExpr(miniaParser::StringListExprContext *ctx) = 0;

  virtual void enterIntegerListExpr(miniaParser::IntegerListExprContext *ctx) = 0;
  virtual void exitIntegerListExpr(miniaParser::IntegerListExprContext *ctx) = 0;

  virtual void enterDecimalListExpr(miniaParser::DecimalListExprContext *ctx) = 0;
  virtual void exitDecimalListExpr(miniaParser::DecimalListExprContext *ctx) = 0;

  virtual void enterFuncCall(miniaParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(miniaParser::FuncCallContext *ctx) = 0;

  virtual void enterExprList(miniaParser::ExprListContext *ctx) = 0;
  virtual void exitExprList(miniaParser::ExprListContext *ctx) = 0;

  virtual void enterStringExpr(miniaParser::StringExprContext *ctx) = 0;
  virtual void exitStringExpr(miniaParser::StringExprContext *ctx) = 0;

  virtual void enterIntegerExpr(miniaParser::IntegerExprContext *ctx) = 0;
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext *ctx) = 0;

  virtual void enterDecimalExpr(miniaParser::DecimalExprContext *ctx) = 0;
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext *ctx) = 0;


};

