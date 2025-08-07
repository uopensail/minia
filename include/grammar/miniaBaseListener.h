
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

  virtual void enterExpr(miniaParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(miniaParser::ExprContext * /*ctx*/) override { }

  virtual void enterOrExpr(miniaParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(miniaParser::OrExprContext * /*ctx*/) override { }

  virtual void enterTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext * /*ctx*/) override { }
  virtual void exitTrivialLogicalAndExpr(miniaParser::TrivialLogicalAndExprContext * /*ctx*/) override { }

  virtual void enterAndExpr(miniaParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(miniaParser::AndExprContext * /*ctx*/) override { }

  virtual void enterTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext * /*ctx*/) override { }
  virtual void exitTrivialEqualityExpr(miniaParser::TrivialEqualityExprContext * /*ctx*/) override { }

  virtual void enterEqualExpr(miniaParser::EqualExprContext * /*ctx*/) override { }
  virtual void exitEqualExpr(miniaParser::EqualExprContext * /*ctx*/) override { }

  virtual void enterNotEqualExpr(miniaParser::NotEqualExprContext * /*ctx*/) override { }
  virtual void exitNotEqualExpr(miniaParser::NotEqualExprContext * /*ctx*/) override { }

  virtual void enterTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext * /*ctx*/) override { }
  virtual void exitTrivialRelationalExpr(miniaParser::TrivialRelationalExprContext * /*ctx*/) override { }

  virtual void enterGreaterThanExpr(miniaParser::GreaterThanExprContext * /*ctx*/) override { }
  virtual void exitGreaterThanExpr(miniaParser::GreaterThanExprContext * /*ctx*/) override { }

  virtual void enterGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext * /*ctx*/) override { }
  virtual void exitGreaterThanEqualExpr(miniaParser::GreaterThanEqualExprContext * /*ctx*/) override { }

  virtual void enterLessThanExpr(miniaParser::LessThanExprContext * /*ctx*/) override { }
  virtual void exitLessThanExpr(miniaParser::LessThanExprContext * /*ctx*/) override { }

  virtual void enterLessThanEqualExpr(miniaParser::LessThanEqualExprContext * /*ctx*/) override { }
  virtual void exitLessThanEqualExpr(miniaParser::LessThanEqualExprContext * /*ctx*/) override { }

  virtual void enterTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext * /*ctx*/) override { }
  virtual void exitTrivialAdditiveExpr(miniaParser::TrivialAdditiveExprContext * /*ctx*/) override { }

  virtual void enterAddExpr(miniaParser::AddExprContext * /*ctx*/) override { }
  virtual void exitAddExpr(miniaParser::AddExprContext * /*ctx*/) override { }

  virtual void enterSubExpr(miniaParser::SubExprContext * /*ctx*/) override { }
  virtual void exitSubExpr(miniaParser::SubExprContext * /*ctx*/) override { }

  virtual void enterTrivialMultiplicativeExpr(miniaParser::TrivialMultiplicativeExprContext * /*ctx*/) override { }
  virtual void exitTrivialMultiplicativeExpr(miniaParser::TrivialMultiplicativeExprContext * /*ctx*/) override { }

  virtual void enterMulExpr(miniaParser::MulExprContext * /*ctx*/) override { }
  virtual void exitMulExpr(miniaParser::MulExprContext * /*ctx*/) override { }

  virtual void enterDivExpr(miniaParser::DivExprContext * /*ctx*/) override { }
  virtual void exitDivExpr(miniaParser::DivExprContext * /*ctx*/) override { }

  virtual void enterModExpr(miniaParser::ModExprContext * /*ctx*/) override { }
  virtual void exitModExpr(miniaParser::ModExprContext * /*ctx*/) override { }

  virtual void enterTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext * /*ctx*/) override { }
  virtual void exitTrivialUnaryExpr(miniaParser::TrivialUnaryExprContext * /*ctx*/) override { }

  virtual void enterNotExpr(miniaParser::NotExprContext * /*ctx*/) override { }
  virtual void exitNotExpr(miniaParser::NotExprContext * /*ctx*/) override { }

  virtual void enterNegExpr(miniaParser::NegExprContext * /*ctx*/) override { }
  virtual void exitNegExpr(miniaParser::NegExprContext * /*ctx*/) override { }

  virtual void enterTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext * /*ctx*/) override { }
  virtual void exitTrivialPrimaryExpr(miniaParser::TrivialPrimaryExprContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpr(miniaParser::ParenthesizedExprContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpr(miniaParser::ParenthesizedExprContext * /*ctx*/) override { }

  virtual void enterFunctionCallExpr(miniaParser::FunctionCallExprContext * /*ctx*/) override { }
  virtual void exitFunctionCallExpr(miniaParser::FunctionCallExprContext * /*ctx*/) override { }

  virtual void enterColumnExpr(miniaParser::ColumnExprContext * /*ctx*/) override { }
  virtual void exitColumnExpr(miniaParser::ColumnExprContext * /*ctx*/) override { }

  virtual void enterLiteralExpr(miniaParser::LiteralExprContext * /*ctx*/) override { }
  virtual void exitLiteralExpr(miniaParser::LiteralExprContext * /*ctx*/) override { }

  virtual void enterListExpr(miniaParser::ListExprContext * /*ctx*/) override { }
  virtual void exitListExpr(miniaParser::ListExprContext * /*ctx*/) override { }

  virtual void enterTrueExpr(miniaParser::TrueExprContext * /*ctx*/) override { }
  virtual void exitTrueExpr(miniaParser::TrueExprContext * /*ctx*/) override { }

  virtual void enterFalseExpr(miniaParser::FalseExprContext * /*ctx*/) override { }
  virtual void exitFalseExpr(miniaParser::FalseExprContext * /*ctx*/) override { }

  virtual void enterStringListExpr(miniaParser::StringListExprContext * /*ctx*/) override { }
  virtual void exitStringListExpr(miniaParser::StringListExprContext * /*ctx*/) override { }

  virtual void enterIntegerListExpr(miniaParser::IntegerListExprContext * /*ctx*/) override { }
  virtual void exitIntegerListExpr(miniaParser::IntegerListExprContext * /*ctx*/) override { }

  virtual void enterDecimalListExpr(miniaParser::DecimalListExprContext * /*ctx*/) override { }
  virtual void exitDecimalListExpr(miniaParser::DecimalListExprContext * /*ctx*/) override { }

  virtual void enterFuncCall(miniaParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(miniaParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterExprList(miniaParser::ExprListContext * /*ctx*/) override { }
  virtual void exitExprList(miniaParser::ExprListContext * /*ctx*/) override { }

  virtual void enterStringExpr(miniaParser::StringExprContext * /*ctx*/) override { }
  virtual void exitStringExpr(miniaParser::StringExprContext * /*ctx*/) override { }

  virtual void enterIntegerExpr(miniaParser::IntegerExprContext * /*ctx*/) override { }
  virtual void exitIntegerExpr(miniaParser::IntegerExprContext * /*ctx*/) override { }

  virtual void enterDecimalExpr(miniaParser::DecimalExprContext * /*ctx*/) override { }
  virtual void exitDecimalExpr(miniaParser::DecimalExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

