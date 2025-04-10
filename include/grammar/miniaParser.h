
// Generated from minia.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  miniaParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T_AND = 3, T_OR = 4, T_NOT = 5, T_TRUE = 6, T_FALSE = 7, 
    T_EQ = 8, T_NEQ = 9, T_GT = 10, T_GTE = 11, T_LT = 12, T_LTE = 13, T_ADD = 14, 
    T_SUB = 15, T_MUL = 16, T_DIV = 17, T_MOD = 18, COMMA = 19, SEMI = 20, 
    T_EQUAL = 21, QUOTA = 22, STRING_LIST = 23, INTEGER_LIST = 24, DECIMAL_LIST = 25, 
    IDENTIFIER = 26, INTEGER = 27, DECIMAL = 28, STRING = 29, WS = 30
  };

  enum {
    RuleProg = 0, RuleStart = 1, RuleExpr = 2, RuleLogicalOrExpr = 3, RuleLogicalAndExpr = 4, 
    RuleEqualityExpr = 5, RuleRelationalExpr = 6, RuleAdditiveExpr = 7, 
    RuleMultiplicativeExpr = 8, RuleUnaryExpr = 9, RulePrimaryExpr = 10, 
    RuleListLiteral = 11, RuleFuncCall = 12, RuleExprList = 13, RuleLiteral = 14
  };

  explicit miniaParser(antlr4::TokenStream *input);

  miniaParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~miniaParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgContext;
  class StartContext;
  class ExprContext;
  class LogicalOrExprContext;
  class LogicalAndExprContext;
  class EqualityExprContext;
  class RelationalExprContext;
  class AdditiveExprContext;
  class MultiplicativeExprContext;
  class UnaryExprContext;
  class PrimaryExprContext;
  class ListLiteralContext;
  class FuncCallContext;
  class ExprListContext;
  class LiteralContext; 

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StartContext *> start();
    StartContext* start(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgContext* prog();

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *T_EQUAL();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartContext* start();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExprContext *logicalOrExpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();

  class  LogicalOrExprContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalOrExprContext() = default;
    void copyFrom(LogicalOrExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  OrExprContext : public LogicalOrExprContext {
  public:
    OrExprContext(LogicalOrExprContext *ctx);

    std::vector<LogicalOrExprContext *> logicalOrExpr();
    LogicalOrExprContext* logicalOrExpr(size_t i);
    antlr4::tree::TerminalNode *T_OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  TrivialLogicalAndExprContext : public LogicalOrExprContext {
  public:
    TrivialLogicalAndExprContext(LogicalOrExprContext *ctx);

    LogicalAndExprContext *logicalAndExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicalOrExprContext* logicalOrExpr();
  LogicalOrExprContext* logicalOrExpr(int precedence);
  class  LogicalAndExprContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalAndExprContext() = default;
    void copyFrom(LogicalAndExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AndExprContext : public LogicalAndExprContext {
  public:
    AndExprContext(LogicalAndExprContext *ctx);

    std::vector<LogicalAndExprContext *> logicalAndExpr();
    LogicalAndExprContext* logicalAndExpr(size_t i);
    antlr4::tree::TerminalNode *T_AND();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  TrivialEqualityExprContext : public LogicalAndExprContext {
  public:
    TrivialEqualityExprContext(LogicalAndExprContext *ctx);

    EqualityExprContext *equalityExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicalAndExprContext* logicalAndExpr();
  LogicalAndExprContext* logicalAndExpr(int precedence);
  class  EqualityExprContext : public antlr4::ParserRuleContext {
  public:
    EqualityExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    EqualityExprContext() = default;
    void copyFrom(EqualityExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EqualExprContext : public EqualityExprContext {
  public:
    EqualExprContext(EqualityExprContext *ctx);

    std::vector<RelationalExprContext *> relationalExpr();
    RelationalExprContext* relationalExpr(size_t i);
    antlr4::tree::TerminalNode *T_EQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  NotEqualExprContext : public EqualityExprContext {
  public:
    NotEqualExprContext(EqualityExprContext *ctx);

    std::vector<RelationalExprContext *> relationalExpr();
    RelationalExprContext* relationalExpr(size_t i);
    antlr4::tree::TerminalNode *T_NEQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  TrivialRelationalExprContext : public EqualityExprContext {
  public:
    TrivialRelationalExprContext(EqualityExprContext *ctx);

    RelationalExprContext *relationalExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  EqualityExprContext* equalityExpr();

  class  RelationalExprContext : public antlr4::ParserRuleContext {
  public:
    RelationalExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RelationalExprContext() = default;
    void copyFrom(RelationalExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrivialAdditiveExprContext : public RelationalExprContext {
  public:
    TrivialAdditiveExprContext(RelationalExprContext *ctx);

    AdditiveExprContext *additiveExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  GreaterThanExprContext : public RelationalExprContext {
  public:
    GreaterThanExprContext(RelationalExprContext *ctx);

    std::vector<AdditiveExprContext *> additiveExpr();
    AdditiveExprContext* additiveExpr(size_t i);
    antlr4::tree::TerminalNode *T_GT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  LessThanEqualExprContext : public RelationalExprContext {
  public:
    LessThanEqualExprContext(RelationalExprContext *ctx);

    std::vector<AdditiveExprContext *> additiveExpr();
    AdditiveExprContext* additiveExpr(size_t i);
    antlr4::tree::TerminalNode *T_LTE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  LessThanExprContext : public RelationalExprContext {
  public:
    LessThanExprContext(RelationalExprContext *ctx);

    std::vector<AdditiveExprContext *> additiveExpr();
    AdditiveExprContext* additiveExpr(size_t i);
    antlr4::tree::TerminalNode *T_LT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  GreaterThanEqualExprContext : public RelationalExprContext {
  public:
    GreaterThanEqualExprContext(RelationalExprContext *ctx);

    std::vector<AdditiveExprContext *> additiveExpr();
    AdditiveExprContext* additiveExpr(size_t i);
    antlr4::tree::TerminalNode *T_GTE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  RelationalExprContext* relationalExpr();

  class  AdditiveExprContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AdditiveExprContext() = default;
    void copyFrom(AdditiveExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrivialMultiplicativeExprContext : public AdditiveExprContext {
  public:
    TrivialMultiplicativeExprContext(AdditiveExprContext *ctx);

    MultiplicativeExprContext *multiplicativeExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  SubExprContext : public AdditiveExprContext {
  public:
    SubExprContext(AdditiveExprContext *ctx);

    std::vector<MultiplicativeExprContext *> multiplicativeExpr();
    MultiplicativeExprContext* multiplicativeExpr(size_t i);
    antlr4::tree::TerminalNode *T_SUB();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  AddExprContext : public AdditiveExprContext {
  public:
    AddExprContext(AdditiveExprContext *ctx);

    std::vector<MultiplicativeExprContext *> multiplicativeExpr();
    MultiplicativeExprContext* multiplicativeExpr(size_t i);
    antlr4::tree::TerminalNode *T_ADD();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  AdditiveExprContext* additiveExpr();

  class  MultiplicativeExprContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MultiplicativeExprContext() = default;
    void copyFrom(MultiplicativeExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MulExprContext : public MultiplicativeExprContext {
  public:
    MulExprContext(MultiplicativeExprContext *ctx);

    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);
    antlr4::tree::TerminalNode *T_MUL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  DivExprContext : public MultiplicativeExprContext {
  public:
    DivExprContext(MultiplicativeExprContext *ctx);

    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);
    antlr4::tree::TerminalNode *T_DIV();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  TrivialUnaryExprContext : public MultiplicativeExprContext {
  public:
    TrivialUnaryExprContext(MultiplicativeExprContext *ctx);

    UnaryExprContext *unaryExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ModExprContext : public MultiplicativeExprContext {
  public:
    ModExprContext(MultiplicativeExprContext *ctx);

    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);
    antlr4::tree::TerminalNode *T_MOD();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  MultiplicativeExprContext* multiplicativeExpr();

  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExprContext() = default;
    void copyFrom(UnaryExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrivialPrimaryExprContext : public UnaryExprContext {
  public:
    TrivialPrimaryExprContext(UnaryExprContext *ctx);

    PrimaryExprContext *primaryExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  NotExprContext : public UnaryExprContext {
  public:
    NotExprContext(UnaryExprContext *ctx);

    antlr4::tree::TerminalNode *T_NOT();
    UnaryExprContext *unaryExpr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  UnaryExprContext* unaryExpr();

  class  PrimaryExprContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryExprContext() = default;
    void copyFrom(PrimaryExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FunctionCallExprContext : public PrimaryExprContext {
  public:
    FunctionCallExprContext(PrimaryExprContext *ctx);

    FuncCallContext *funcCall();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  TrueExprContext : public PrimaryExprContext {
  public:
    TrueExprContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *T_TRUE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ColumnExprContext : public PrimaryExprContext {
  public:
    ColumnExprContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  LiteralExprContext : public PrimaryExprContext {
  public:
    LiteralExprContext(PrimaryExprContext *ctx);

    LiteralContext *literal();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ParenthesizedExprContext : public PrimaryExprContext {
  public:
    ParenthesizedExprContext(PrimaryExprContext *ctx);

    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ListExprContext : public PrimaryExprContext {
  public:
    ListExprContext(PrimaryExprContext *ctx);

    ListLiteralContext *listLiteral();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FalseExprContext : public PrimaryExprContext {
  public:
    FalseExprContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *T_FALSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  PrimaryExprContext* primaryExpr();

  class  ListLiteralContext : public antlr4::ParserRuleContext {
  public:
    ListLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ListLiteralContext() = default;
    void copyFrom(ListLiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntegerListExprContext : public ListLiteralContext {
  public:
    IntegerListExprContext(ListLiteralContext *ctx);

    antlr4::tree::TerminalNode *INTEGER_LIST();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StringListExprContext : public ListLiteralContext {
  public:
    StringListExprContext(ListLiteralContext *ctx);

    antlr4::tree::TerminalNode *STRING_LIST();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  DecimalListExprContext : public ListLiteralContext {
  public:
    DecimalListExprContext(ListLiteralContext *ctx);

    antlr4::tree::TerminalNode *DECIMAL_LIST();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  ListLiteralContext* listLiteral();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExprListContext *exprList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FuncCallContext* funcCall();

  class  ExprListContext : public antlr4::ParserRuleContext {
  public:
    ExprListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprListContext* exprList();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StringExprContext : public LiteralContext {
  public:
    StringExprContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  IntegerExprContext : public LiteralContext {
  public:
    IntegerExprContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *INTEGER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  DecimalExprContext : public LiteralContext {
  public:
    DecimalExprContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *DECIMAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LiteralContext* literal();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool logicalOrExprSempred(LogicalOrExprContext *_localctx, size_t predicateIndex);
  bool logicalAndExprSempred(LogicalAndExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

