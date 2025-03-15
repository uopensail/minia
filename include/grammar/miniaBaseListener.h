
// Generated from minia.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "miniaListener.h"


/**
 * This class provides an empty implementation of miniaListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  miniaBaseListener : public miniaListener {
public:

  virtual void enterProg(miniaParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(miniaParser::ProgContext * /*ctx*/) override { }

  virtual void enterStart(miniaParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(miniaParser::StartContext * /*ctx*/) override { }

  virtual void enterMulExpr(miniaParser::MulExprContext * /*ctx*/) override { }
  virtual void exitMulExpr(miniaParser::MulExprContext * /*ctx*/) override { }

  virtual void enterStringExpr(miniaParser::StringExprContext * /*ctx*/) override { }
  virtual void exitStringExpr(miniaParser::StringExprContext * /*ctx*/) override { }

  virtual void enterDecimalLISTExpr(miniaParser::DecimalLISTExprContext * /*ctx*/) override { }
  virtual void exitDecimalLISTExpr(miniaParser::DecimalLISTExprContext * /*ctx*/) override { }

  virtual void enterPlainExpr(miniaParser::PlainExprContext * /*ctx*/) override { }
  virtual void exitPlainExpr(miniaParser::PlainExprContext * /*ctx*/) override { }

  virtual void enterColumnExpr(miniaParser::ColumnExprContext * /*ctx*/) override { }
  virtual void exitColumnExpr(miniaParser::ColumnExprContext * /*ctx*/) override { }

  virtual void enterSubExpr(miniaParser::SubExprContext * /*ctx*/) override { }
  virtual void exitSubExpr(miniaParser::SubExprContext * /*ctx*/) override { }

  virtual void enterAddExpr(miniaParser::AddExprContext * /*ctx*/) override { }
  virtual void exitAddExpr(miniaParser::AddExprContext * /*ctx*/) override { }

  virtual void enterFuncExpr(miniaParser::FuncExprContext * /*ctx*/) override { }
  virtual void exitFuncExpr(miniaParser::FuncExprContext * /*ctx*/) override { }

  virtual void enterDecimalExpr(miniaParser::DecimalExprContext * /*ctx*/) override { }
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext * /*ctx*/) override { }

  virtual void enterStringLISTExpr(miniaParser::StringLISTExprContext * /*ctx*/) override { }
  virtual void exitStringLISTExpr(miniaParser::StringLISTExprContext * /*ctx*/) override { }

  virtual void enterRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext * /*ctx*/) override { }
  virtual void exitRuntTimeFuncExpr(miniaParser::RuntTimeFuncExprContext * /*ctx*/) override { }

  virtual void enterIntegerExpr(miniaParser::IntegerExprContext * /*ctx*/) override { }
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext * /*ctx*/) override { }

  virtual void enterDivExpr(miniaParser::DivExprContext * /*ctx*/) override { }
  virtual void exitDivExpr(miniaParser::DivExprContext * /*ctx*/) override { }

  virtual void enterModExpr(miniaParser::ModExprContext * /*ctx*/) override { }
  virtual void exitModExpr(miniaParser::ModExprContext * /*ctx*/) override { }

  virtual void enterIntegerLISTExpr(miniaParser::IntegerLISTExprContext * /*ctx*/) override { }
  virtual void exitIntegerLISTExpr(miniaParser::IntegerLISTExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

