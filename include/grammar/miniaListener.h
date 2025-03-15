
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

  virtual void enterMulExpr(miniaParser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(miniaParser::MulExprContext *ctx) = 0;

  virtual void enterStringExpr(miniaParser::StringExprContext *ctx) = 0;
  virtual void exitStringExpr(miniaParser::StringExprContext *ctx) = 0;

  virtual void enterDecimalLISTExpr(miniaParser::DecimalLISTExprContext *ctx) = 0;
  virtual void exitDecimalLISTExpr(miniaParser::DecimalLISTExprContext *ctx) = 0;

  virtual void enterPlainExpr(miniaParser::PlainExprContext *ctx) = 0;
  virtual void exitPlainExpr(miniaParser::PlainExprContext *ctx) = 0;

  virtual void enterColumnExpr(miniaParser::ColumnExprContext *ctx) = 0;
  virtual void exitColumnExpr(miniaParser::ColumnExprContext *ctx) = 0;

  virtual void enterSubExpr(miniaParser::SubExprContext *ctx) = 0;
  virtual void exitSubExpr(miniaParser::SubExprContext *ctx) = 0;

  virtual void enterAddExpr(miniaParser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(miniaParser::AddExprContext *ctx) = 0;

  virtual void enterFuncExpr(miniaParser::FuncExprContext *ctx) = 0;
  virtual void exitFuncExpr(miniaParser::FuncExprContext *ctx) = 0;

  virtual void enterDecimalExpr(miniaParser::DecimalExprContext *ctx) = 0;
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext *ctx) = 0;

  virtual void enterStringLISTExpr(miniaParser::StringLISTExprContext *ctx) = 0;
  virtual void exitStringLISTExpr(miniaParser::StringLISTExprContext *ctx) = 0;

  virtual void enterRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext *ctx) = 0;
  virtual void exitRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext *ctx) = 0;

  virtual void enterIntegerExpr(miniaParser::IntegerExprContext *ctx) = 0;
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext *ctx) = 0;

  virtual void enterDivExpr(miniaParser::DivExprContext *ctx) = 0;
  virtual void exitDivExpr(miniaParser::DivExprContext *ctx) = 0;

  virtual void enterModExpr(miniaParser::ModExprContext *ctx) = 0;
  virtual void exitModExpr(miniaParser::ModExprContext *ctx) = 0;

  virtual void enterIntegerLISTExpr(miniaParser::IntegerLISTExprContext *ctx) = 0;
  virtual void exitIntegerLISTExpr(miniaParser::IntegerLISTExprContext *ctx) = 0;


};

