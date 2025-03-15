
// Generated from minia.g4 by ANTLR 4.13.2


#include "miniaListener.h"

#include "miniaParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniaParserStaticData final {
  MiniaParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniaParserStaticData(const MiniaParserStaticData&) = delete;
  MiniaParserStaticData(MiniaParserStaticData&&) = delete;
  MiniaParserStaticData& operator=(const MiniaParserStaticData&) = delete;
  MiniaParserStaticData& operator=(MiniaParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag miniaParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MiniaParserStaticData> miniaParserStaticData = nullptr;

void miniaParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (miniaParserStaticData != nullptr) {
    return;
  }
#else
  assert(miniaParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MiniaParserStaticData>(
    std::vector<std::string>{
      "prog", "start", "expr"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'.'", "','", "';'", "'\"'", "'='", "'+'", "'-'", 
      "'*'", "'/'", "'%'"
    },
    std::vector<std::string>{
      "", "", "", "DOT", "COMMA", "SEMI", "QUOTA", "T_EQUAL", "T_ADD", "T_SUB", 
      "T_MUL", "T_DIV", "T_MOD", "IDENTIFIER", "INTEGER_LIST", "INTEGER", 
      "DECIMAL_LIST", "DECIMAL", "STRING_LIST", "STRING", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,20,71,2,0,7,0,2,1,7,1,2,2,7,2,1,0,1,0,1,0,5,0,10,8,0,10,0,12,0,13,
  	9,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,
  	2,31,8,2,10,2,12,2,34,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,3,2,49,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,5,2,66,8,2,10,2,12,2,69,9,2,1,2,0,1,4,3,0,2,4,0,0,83,0,11,1,
  	0,0,0,2,17,1,0,0,0,4,48,1,0,0,0,6,7,3,2,1,0,7,8,5,5,0,0,8,10,1,0,0,0,
  	9,6,1,0,0,0,10,13,1,0,0,0,11,9,1,0,0,0,11,12,1,0,0,0,12,14,1,0,0,0,13,
  	11,1,0,0,0,14,15,3,2,1,0,15,16,5,0,0,1,16,1,1,0,0,0,17,18,5,13,0,0,18,
  	19,5,7,0,0,19,20,3,4,2,0,20,3,1,0,0,0,21,22,6,2,-1,0,22,23,5,13,0,0,23,
  	24,5,1,0,0,24,49,5,2,0,0,25,26,5,13,0,0,26,27,5,1,0,0,27,32,3,4,2,0,28,
  	29,5,4,0,0,29,31,3,4,2,0,30,28,1,0,0,0,31,34,1,0,0,0,32,30,1,0,0,0,32,
  	33,1,0,0,0,33,35,1,0,0,0,34,32,1,0,0,0,35,36,5,2,0,0,36,49,1,0,0,0,37,
  	49,5,13,0,0,38,49,5,19,0,0,39,49,5,15,0,0,40,49,5,17,0,0,41,49,5,18,0,
  	0,42,49,5,14,0,0,43,49,5,16,0,0,44,45,5,1,0,0,45,46,3,4,2,0,46,47,5,2,
  	0,0,47,49,1,0,0,0,48,21,1,0,0,0,48,25,1,0,0,0,48,37,1,0,0,0,48,38,1,0,
  	0,0,48,39,1,0,0,0,48,40,1,0,0,0,48,41,1,0,0,0,48,42,1,0,0,0,48,43,1,0,
  	0,0,48,44,1,0,0,0,49,67,1,0,0,0,50,51,10,15,0,0,51,52,5,12,0,0,52,66,
  	3,4,2,16,53,54,10,14,0,0,54,55,5,10,0,0,55,66,3,4,2,15,56,57,10,13,0,
  	0,57,58,5,11,0,0,58,66,3,4,2,14,59,60,10,12,0,0,60,61,5,8,0,0,61,66,3,
  	4,2,13,62,63,10,11,0,0,63,64,5,9,0,0,64,66,3,4,2,12,65,50,1,0,0,0,65,
  	53,1,0,0,0,65,56,1,0,0,0,65,59,1,0,0,0,65,62,1,0,0,0,66,69,1,0,0,0,67,
  	65,1,0,0,0,67,68,1,0,0,0,68,5,1,0,0,0,69,67,1,0,0,0,5,11,32,48,65,67
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  miniaParserStaticData = std::move(staticData);
}

}

miniaParser::miniaParser(TokenStream *input) : miniaParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

miniaParser::miniaParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  miniaParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *miniaParserStaticData->atn, miniaParserStaticData->decisionToDFA, miniaParserStaticData->sharedContextCache, options);
}

miniaParser::~miniaParser() {
  delete _interpreter;
}

const atn::ATN& miniaParser::getATN() const {
  return *miniaParserStaticData->atn;
}

std::string miniaParser::getGrammarFileName() const {
  return "minia.g4";
}

const std::vector<std::string>& miniaParser::getRuleNames() const {
  return miniaParserStaticData->ruleNames;
}

const dfa::Vocabulary& miniaParser::getVocabulary() const {
  return miniaParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView miniaParser::getSerializedATN() const {
  return miniaParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

miniaParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<miniaParser::StartContext *> miniaParser::ProgContext::start() {
  return getRuleContexts<miniaParser::StartContext>();
}

miniaParser::StartContext* miniaParser::ProgContext::start(size_t i) {
  return getRuleContext<miniaParser::StartContext>(i);
}

tree::TerminalNode* miniaParser::ProgContext::EOF() {
  return getToken(miniaParser::EOF, 0);
}

std::vector<tree::TerminalNode *> miniaParser::ProgContext::SEMI() {
  return getTokens(miniaParser::SEMI);
}

tree::TerminalNode* miniaParser::ProgContext::SEMI(size_t i) {
  return getToken(miniaParser::SEMI, i);
}


size_t miniaParser::ProgContext::getRuleIndex() const {
  return miniaParser::RuleProg;
}

void miniaParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void miniaParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}

miniaParser::ProgContext* miniaParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, miniaParser::RuleProg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(11);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(6);
        start();
        setState(7);
        match(miniaParser::SEMI); 
      }
      setState(13);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(14);
    start();
    setState(15);
    match(miniaParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartContext ------------------------------------------------------------------

miniaParser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* miniaParser::StartContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

tree::TerminalNode* miniaParser::StartContext::T_EQUAL() {
  return getToken(miniaParser::T_EQUAL, 0);
}

miniaParser::ExprContext* miniaParser::StartContext::expr() {
  return getRuleContext<miniaParser::ExprContext>(0);
}


size_t miniaParser::StartContext::getRuleIndex() const {
  return miniaParser::RuleStart;
}

void miniaParser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void miniaParser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

miniaParser::StartContext* miniaParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 2, miniaParser::RuleStart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17);
    match(miniaParser::IDENTIFIER);
    setState(18);
    match(miniaParser::T_EQUAL);
    setState(19);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

miniaParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::ExprContext::getRuleIndex() const {
  return miniaParser::RuleExpr;
}

void miniaParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulExprContext ------------------------------------------------------------------

std::vector<miniaParser::ExprContext *> miniaParser::MulExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::MulExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

tree::TerminalNode* miniaParser::MulExprContext::T_MUL() {
  return getToken(miniaParser::T_MUL, 0);
}

miniaParser::MulExprContext::MulExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::MulExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExpr(this);
}
void miniaParser::MulExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExpr(this);
}
//----------------- StringExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::StringExprContext::STRING() {
  return getToken(miniaParser::STRING, 0);
}

miniaParser::StringExprContext::StringExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::StringExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringExpr(this);
}
void miniaParser::StringExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringExpr(this);
}
//----------------- DecimalLISTExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::DecimalLISTExprContext::DECIMAL_LIST() {
  return getToken(miniaParser::DECIMAL_LIST, 0);
}

miniaParser::DecimalLISTExprContext::DecimalLISTExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::DecimalLISTExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecimalLISTExpr(this);
}
void miniaParser::DecimalLISTExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecimalLISTExpr(this);
}
//----------------- PlainExprContext ------------------------------------------------------------------

miniaParser::ExprContext* miniaParser::PlainExprContext::expr() {
  return getRuleContext<miniaParser::ExprContext>(0);
}

miniaParser::PlainExprContext::PlainExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::PlainExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlainExpr(this);
}
void miniaParser::PlainExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlainExpr(this);
}
//----------------- ColumnExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::ColumnExprContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

miniaParser::ColumnExprContext::ColumnExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::ColumnExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnExpr(this);
}
void miniaParser::ColumnExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnExpr(this);
}
//----------------- SubExprContext ------------------------------------------------------------------

std::vector<miniaParser::ExprContext *> miniaParser::SubExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::SubExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

tree::TerminalNode* miniaParser::SubExprContext::T_SUB() {
  return getToken(miniaParser::T_SUB, 0);
}

miniaParser::SubExprContext::SubExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::SubExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubExpr(this);
}
void miniaParser::SubExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubExpr(this);
}
//----------------- AddExprContext ------------------------------------------------------------------

std::vector<miniaParser::ExprContext *> miniaParser::AddExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::AddExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

tree::TerminalNode* miniaParser::AddExprContext::T_ADD() {
  return getToken(miniaParser::T_ADD, 0);
}

miniaParser::AddExprContext::AddExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::AddExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpr(this);
}
void miniaParser::AddExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpr(this);
}
//----------------- FuncExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::FuncExprContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

std::vector<miniaParser::ExprContext *> miniaParser::FuncExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::FuncExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> miniaParser::FuncExprContext::COMMA() {
  return getTokens(miniaParser::COMMA);
}

tree::TerminalNode* miniaParser::FuncExprContext::COMMA(size_t i) {
  return getToken(miniaParser::COMMA, i);
}

miniaParser::FuncExprContext::FuncExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::FuncExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncExpr(this);
}
void miniaParser::FuncExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncExpr(this);
}
//----------------- DecimalExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::DecimalExprContext::DECIMAL() {
  return getToken(miniaParser::DECIMAL, 0);
}

miniaParser::DecimalExprContext::DecimalExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::DecimalExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecimalExpr(this);
}
void miniaParser::DecimalExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecimalExpr(this);
}
//----------------- StringLISTExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::StringLISTExprContext::STRING_LIST() {
  return getToken(miniaParser::STRING_LIST, 0);
}

miniaParser::StringLISTExprContext::StringLISTExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::StringLISTExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLISTExpr(this);
}
void miniaParser::StringLISTExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLISTExpr(this);
}
//----------------- RuntTimeFuncExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::RuntTimeFuncExprContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

miniaParser::RuntTimeFuncExprContext::RuntTimeFuncExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::RuntTimeFuncExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuntTimeFuncExpr(this);
}
void miniaParser::RuntTimeFuncExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuntTimeFuncExpr(this);
}
//----------------- IntegerExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::IntegerExprContext::INTEGER() {
  return getToken(miniaParser::INTEGER, 0);
}

miniaParser::IntegerExprContext::IntegerExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::IntegerExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerExpr(this);
}
void miniaParser::IntegerExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerExpr(this);
}
//----------------- DivExprContext ------------------------------------------------------------------

std::vector<miniaParser::ExprContext *> miniaParser::DivExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::DivExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

tree::TerminalNode* miniaParser::DivExprContext::T_DIV() {
  return getToken(miniaParser::T_DIV, 0);
}

miniaParser::DivExprContext::DivExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::DivExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDivExpr(this);
}
void miniaParser::DivExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDivExpr(this);
}
//----------------- ModExprContext ------------------------------------------------------------------

std::vector<miniaParser::ExprContext *> miniaParser::ModExprContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::ModExprContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

tree::TerminalNode* miniaParser::ModExprContext::T_MOD() {
  return getToken(miniaParser::T_MOD, 0);
}

miniaParser::ModExprContext::ModExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::ModExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModExpr(this);
}
void miniaParser::ModExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModExpr(this);
}
//----------------- IntegerLISTExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::IntegerLISTExprContext::INTEGER_LIST() {
  return getToken(miniaParser::INTEGER_LIST, 0);
}

miniaParser::IntegerLISTExprContext::IntegerLISTExprContext(ExprContext *ctx) { copyFrom(ctx); }

void miniaParser::IntegerLISTExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerLISTExpr(this);
}
void miniaParser::IntegerLISTExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerLISTExpr(this);
}

miniaParser::ExprContext* miniaParser::expr() {
   return expr(0);
}

miniaParser::ExprContext* miniaParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  miniaParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  miniaParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, miniaParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(48);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<RuntTimeFuncExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(22);
      match(miniaParser::IDENTIFIER);
      setState(23);
      match(miniaParser::T__0);
      setState(24);
      match(miniaParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<FuncExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(25);
      match(miniaParser::IDENTIFIER);
      setState(26);
      match(miniaParser::T__0);
      setState(27);
      expr(0);
      setState(32);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == miniaParser::COMMA) {
        setState(28);
        match(miniaParser::COMMA);
        setState(29);
        expr(0);
        setState(34);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(35);
      match(miniaParser::T__1);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ColumnExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(37);
      match(miniaParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<StringExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(38);
      match(miniaParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<IntegerExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(39);
      match(miniaParser::INTEGER);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<DecimalExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(40);
      match(miniaParser::DECIMAL);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<StringLISTExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(41);
      match(miniaParser::STRING_LIST);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IntegerLISTExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(42);
      match(miniaParser::INTEGER_LIST);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<DecimalLISTExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(43);
      match(miniaParser::DECIMAL_LIST);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<PlainExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(44);
      match(miniaParser::T__0);
      setState(45);
      expr(0);
      setState(46);
      match(miniaParser::T__1);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(67);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(65);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ModExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(50);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(51);
          match(miniaParser::T_MOD);
          setState(52);
          expr(16);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MulExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(53);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(54);
          match(miniaParser::T_MUL);
          setState(55);
          expr(15);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DivExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(56);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(57);
          match(miniaParser::T_DIV);
          setState(58);
          expr(14);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AddExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(59);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(60);
          match(miniaParser::T_ADD);
          setState(61);
          expr(13);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<SubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(62);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(63);
          match(miniaParser::T_SUB);
          setState(64);
          expr(12);
          break;
        }

        default:
          break;
        } 
      }
      setState(69);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool miniaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool miniaParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 15);
    case 1: return precpred(_ctx, 14);
    case 2: return precpred(_ctx, 13);
    case 3: return precpred(_ctx, 12);
    case 4: return precpred(_ctx, 11);

  default:
    break;
  }
  return true;
}

void miniaParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  miniaParserInitialize();
#else
  ::antlr4::internal::call_once(miniaParserOnceFlag, miniaParserInitialize);
#endif
}
