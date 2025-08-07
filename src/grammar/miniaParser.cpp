
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
      "prog", "start", "expr", "logicalOrExpr", "logicalAndExpr", "equalityExpr", 
      "relationalExpr", "additiveExpr", "multiplicativeExpr", "unaryExpr", 
      "primaryExpr", "listLiteral", "funcCall", "exprList", "literal"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'&'", "'|'", "'!'", "'true'", "'false'", "'=='", 
      "'!='", "'>'", "'>='", "'<'", "'<='", "'+'", "'-'", "'*'", "'/'", 
      "'%'", "','", "';'", "'='", "'\"'"
    },
    std::vector<std::string>{
      "", "", "", "T_AND", "T_OR", "T_NOT", "T_TRUE", "T_FALSE", "T_EQ", 
      "T_NEQ", "T_GT", "T_GTE", "T_LT", "T_LTE", "T_ADD", "T_SUB", "T_MUL", 
      "T_DIV", "T_MOD", "COMMA", "SEMI", "T_EQUAL", "QUOTA", "STRING_LIST", 
      "INTEGER_LIST", "DECIMAL_LIST", "IDENTIFIER", "INTEGER", "DECIMAL", 
      "STRING", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,30,170,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,1,0,1,0,5,0,34,8,0,10,0,12,0,37,9,0,1,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,5,3,54,8,3,10,3,12,3,57,9,3,1,4,1,4,
  	1,4,1,4,1,4,1,4,5,4,65,8,4,10,4,12,4,68,9,4,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,3,5,79,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,3,6,98,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,
  	7,109,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,124,
  	8,8,1,9,1,9,1,9,1,9,1,9,3,9,131,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,3,10,143,8,10,1,11,1,11,1,11,3,11,148,8,11,1,12,1,12,1,
  	12,3,12,153,8,12,1,12,1,12,1,13,1,13,1,13,5,13,160,8,13,10,13,12,13,163,
  	9,13,1,14,1,14,1,14,3,14,168,8,14,1,14,0,2,6,8,15,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,0,0,182,0,35,1,0,0,0,2,41,1,0,0,0,4,45,1,0,0,0,6,
  	47,1,0,0,0,8,58,1,0,0,0,10,78,1,0,0,0,12,97,1,0,0,0,14,108,1,0,0,0,16,
  	123,1,0,0,0,18,130,1,0,0,0,20,142,1,0,0,0,22,147,1,0,0,0,24,149,1,0,0,
  	0,26,156,1,0,0,0,28,167,1,0,0,0,30,31,3,2,1,0,31,32,5,20,0,0,32,34,1,
  	0,0,0,33,30,1,0,0,0,34,37,1,0,0,0,35,33,1,0,0,0,35,36,1,0,0,0,36,38,1,
  	0,0,0,37,35,1,0,0,0,38,39,3,2,1,0,39,40,5,0,0,1,40,1,1,0,0,0,41,42,5,
  	26,0,0,42,43,5,21,0,0,43,44,3,4,2,0,44,3,1,0,0,0,45,46,3,6,3,0,46,5,1,
  	0,0,0,47,48,6,3,-1,0,48,49,3,8,4,0,49,55,1,0,0,0,50,51,10,2,0,0,51,52,
  	5,4,0,0,52,54,3,6,3,3,53,50,1,0,0,0,54,57,1,0,0,0,55,53,1,0,0,0,55,56,
  	1,0,0,0,56,7,1,0,0,0,57,55,1,0,0,0,58,59,6,4,-1,0,59,60,3,10,5,0,60,66,
  	1,0,0,0,61,62,10,2,0,0,62,63,5,3,0,0,63,65,3,8,4,3,64,61,1,0,0,0,65,68,
  	1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,9,1,0,0,0,68,66,1,0,0,0,69,70,
  	3,12,6,0,70,71,5,8,0,0,71,72,3,12,6,0,72,79,1,0,0,0,73,74,3,12,6,0,74,
  	75,5,9,0,0,75,76,3,12,6,0,76,79,1,0,0,0,77,79,3,12,6,0,78,69,1,0,0,0,
  	78,73,1,0,0,0,78,77,1,0,0,0,79,11,1,0,0,0,80,81,3,14,7,0,81,82,5,10,0,
  	0,82,83,3,14,7,0,83,98,1,0,0,0,84,85,3,14,7,0,85,86,5,11,0,0,86,87,3,
  	14,7,0,87,98,1,0,0,0,88,89,3,14,7,0,89,90,5,12,0,0,90,91,3,14,7,0,91,
  	98,1,0,0,0,92,93,3,14,7,0,93,94,5,13,0,0,94,95,3,14,7,0,95,98,1,0,0,0,
  	96,98,3,14,7,0,97,80,1,0,0,0,97,84,1,0,0,0,97,88,1,0,0,0,97,92,1,0,0,
  	0,97,96,1,0,0,0,98,13,1,0,0,0,99,100,3,16,8,0,100,101,5,14,0,0,101,102,
  	3,16,8,0,102,109,1,0,0,0,103,104,3,16,8,0,104,105,5,15,0,0,105,106,3,
  	16,8,0,106,109,1,0,0,0,107,109,3,16,8,0,108,99,1,0,0,0,108,103,1,0,0,
  	0,108,107,1,0,0,0,109,15,1,0,0,0,110,111,3,18,9,0,111,112,5,16,0,0,112,
  	113,3,18,9,0,113,124,1,0,0,0,114,115,3,18,9,0,115,116,5,17,0,0,116,117,
  	3,18,9,0,117,124,1,0,0,0,118,119,3,18,9,0,119,120,5,18,0,0,120,121,3,
  	18,9,0,121,124,1,0,0,0,122,124,3,18,9,0,123,110,1,0,0,0,123,114,1,0,0,
  	0,123,118,1,0,0,0,123,122,1,0,0,0,124,17,1,0,0,0,125,126,5,5,0,0,126,
  	131,3,18,9,0,127,128,5,15,0,0,128,131,3,18,9,0,129,131,3,20,10,0,130,
  	125,1,0,0,0,130,127,1,0,0,0,130,129,1,0,0,0,131,19,1,0,0,0,132,133,5,
  	1,0,0,133,134,3,4,2,0,134,135,5,2,0,0,135,143,1,0,0,0,136,143,3,24,12,
  	0,137,143,5,26,0,0,138,143,3,28,14,0,139,143,3,22,11,0,140,143,5,6,0,
  	0,141,143,5,7,0,0,142,132,1,0,0,0,142,136,1,0,0,0,142,137,1,0,0,0,142,
  	138,1,0,0,0,142,139,1,0,0,0,142,140,1,0,0,0,142,141,1,0,0,0,143,21,1,
  	0,0,0,144,148,5,23,0,0,145,148,5,24,0,0,146,148,5,25,0,0,147,144,1,0,
  	0,0,147,145,1,0,0,0,147,146,1,0,0,0,148,23,1,0,0,0,149,150,5,26,0,0,150,
  	152,5,1,0,0,151,153,3,26,13,0,152,151,1,0,0,0,152,153,1,0,0,0,153,154,
  	1,0,0,0,154,155,5,2,0,0,155,25,1,0,0,0,156,161,3,4,2,0,157,158,5,19,0,
  	0,158,160,3,4,2,0,159,157,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,
  	162,1,0,0,0,162,27,1,0,0,0,163,161,1,0,0,0,164,168,5,29,0,0,165,168,5,
  	27,0,0,166,168,5,28,0,0,167,164,1,0,0,0,167,165,1,0,0,0,167,166,1,0,0,
  	0,168,29,1,0,0,0,13,35,55,66,78,97,108,123,130,142,147,152,161,167
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
    setState(35);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(30);
        start();
        setState(31);
        match(miniaParser::SEMI); 
      }
      setState(37);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(38);
    start();
    setState(39);
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
    setState(41);
    match(miniaParser::IDENTIFIER);
    setState(42);
    match(miniaParser::T_EQUAL);
    setState(43);
    expr();
   
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

miniaParser::LogicalOrExprContext* miniaParser::ExprContext::logicalOrExpr() {
  return getRuleContext<miniaParser::LogicalOrExprContext>(0);
}


size_t miniaParser::ExprContext::getRuleIndex() const {
  return miniaParser::RuleExpr;
}

void miniaParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void miniaParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

miniaParser::ExprContext* miniaParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 4, miniaParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    logicalOrExpr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExprContext ------------------------------------------------------------------

miniaParser::LogicalOrExprContext::LogicalOrExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::LogicalOrExprContext::getRuleIndex() const {
  return miniaParser::RuleLogicalOrExpr;
}

void miniaParser::LogicalOrExprContext::copyFrom(LogicalOrExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- OrExprContext ------------------------------------------------------------------

std::vector<miniaParser::LogicalOrExprContext *> miniaParser::OrExprContext::logicalOrExpr() {
  return getRuleContexts<miniaParser::LogicalOrExprContext>();
}

miniaParser::LogicalOrExprContext* miniaParser::OrExprContext::logicalOrExpr(size_t i) {
  return getRuleContext<miniaParser::LogicalOrExprContext>(i);
}

tree::TerminalNode* miniaParser::OrExprContext::T_OR() {
  return getToken(miniaParser::T_OR, 0);
}

miniaParser::OrExprContext::OrExprContext(LogicalOrExprContext *ctx) { copyFrom(ctx); }

void miniaParser::OrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpr(this);
}
void miniaParser::OrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpr(this);
}
//----------------- TrivialLogicalAndExprContext ------------------------------------------------------------------

miniaParser::LogicalAndExprContext* miniaParser::TrivialLogicalAndExprContext::logicalAndExpr() {
  return getRuleContext<miniaParser::LogicalAndExprContext>(0);
}

miniaParser::TrivialLogicalAndExprContext::TrivialLogicalAndExprContext(LogicalOrExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialLogicalAndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialLogicalAndExpr(this);
}
void miniaParser::TrivialLogicalAndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialLogicalAndExpr(this);
}

miniaParser::LogicalOrExprContext* miniaParser::logicalOrExpr() {
   return logicalOrExpr(0);
}

miniaParser::LogicalOrExprContext* miniaParser::logicalOrExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  miniaParser::LogicalOrExprContext *_localctx = _tracker.createInstance<LogicalOrExprContext>(_ctx, parentState);
  miniaParser::LogicalOrExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, miniaParser::RuleLogicalOrExpr, precedence);

    

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
    _localctx = _tracker.createInstance<TrivialLogicalAndExprContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(48);
    logicalAndExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(55);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<LogicalOrExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLogicalOrExpr);
        setState(50);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(51);
        match(miniaParser::T_OR);
        setState(52);
        logicalOrExpr(3); 
      }
      setState(57);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalAndExprContext ------------------------------------------------------------------

miniaParser::LogicalAndExprContext::LogicalAndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::LogicalAndExprContext::getRuleIndex() const {
  return miniaParser::RuleLogicalAndExpr;
}

void miniaParser::LogicalAndExprContext::copyFrom(LogicalAndExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AndExprContext ------------------------------------------------------------------

std::vector<miniaParser::LogicalAndExprContext *> miniaParser::AndExprContext::logicalAndExpr() {
  return getRuleContexts<miniaParser::LogicalAndExprContext>();
}

miniaParser::LogicalAndExprContext* miniaParser::AndExprContext::logicalAndExpr(size_t i) {
  return getRuleContext<miniaParser::LogicalAndExprContext>(i);
}

tree::TerminalNode* miniaParser::AndExprContext::T_AND() {
  return getToken(miniaParser::T_AND, 0);
}

miniaParser::AndExprContext::AndExprContext(LogicalAndExprContext *ctx) { copyFrom(ctx); }

void miniaParser::AndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpr(this);
}
void miniaParser::AndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpr(this);
}
//----------------- TrivialEqualityExprContext ------------------------------------------------------------------

miniaParser::EqualityExprContext* miniaParser::TrivialEqualityExprContext::equalityExpr() {
  return getRuleContext<miniaParser::EqualityExprContext>(0);
}

miniaParser::TrivialEqualityExprContext::TrivialEqualityExprContext(LogicalAndExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialEqualityExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialEqualityExpr(this);
}
void miniaParser::TrivialEqualityExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialEqualityExpr(this);
}

miniaParser::LogicalAndExprContext* miniaParser::logicalAndExpr() {
   return logicalAndExpr(0);
}

miniaParser::LogicalAndExprContext* miniaParser::logicalAndExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  miniaParser::LogicalAndExprContext *_localctx = _tracker.createInstance<LogicalAndExprContext>(_ctx, parentState);
  miniaParser::LogicalAndExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, miniaParser::RuleLogicalAndExpr, precedence);

    

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
    _localctx = _tracker.createInstance<TrivialEqualityExprContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(59);
    equalityExpr();
    _ctx->stop = _input->LT(-1);
    setState(66);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<LogicalAndExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLogicalAndExpr);
        setState(61);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(62);
        match(miniaParser::T_AND);
        setState(63);
        logicalAndExpr(3); 
      }
      setState(68);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqualityExprContext ------------------------------------------------------------------

miniaParser::EqualityExprContext::EqualityExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::EqualityExprContext::getRuleIndex() const {
  return miniaParser::RuleEqualityExpr;
}

void miniaParser::EqualityExprContext::copyFrom(EqualityExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EqualExprContext ------------------------------------------------------------------

std::vector<miniaParser::RelationalExprContext *> miniaParser::EqualExprContext::relationalExpr() {
  return getRuleContexts<miniaParser::RelationalExprContext>();
}

miniaParser::RelationalExprContext* miniaParser::EqualExprContext::relationalExpr(size_t i) {
  return getRuleContext<miniaParser::RelationalExprContext>(i);
}

tree::TerminalNode* miniaParser::EqualExprContext::T_EQ() {
  return getToken(miniaParser::T_EQ, 0);
}

miniaParser::EqualExprContext::EqualExprContext(EqualityExprContext *ctx) { copyFrom(ctx); }

void miniaParser::EqualExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualExpr(this);
}
void miniaParser::EqualExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualExpr(this);
}
//----------------- NotEqualExprContext ------------------------------------------------------------------

std::vector<miniaParser::RelationalExprContext *> miniaParser::NotEqualExprContext::relationalExpr() {
  return getRuleContexts<miniaParser::RelationalExprContext>();
}

miniaParser::RelationalExprContext* miniaParser::NotEqualExprContext::relationalExpr(size_t i) {
  return getRuleContext<miniaParser::RelationalExprContext>(i);
}

tree::TerminalNode* miniaParser::NotEqualExprContext::T_NEQ() {
  return getToken(miniaParser::T_NEQ, 0);
}

miniaParser::NotEqualExprContext::NotEqualExprContext(EqualityExprContext *ctx) { copyFrom(ctx); }

void miniaParser::NotEqualExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotEqualExpr(this);
}
void miniaParser::NotEqualExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotEqualExpr(this);
}
//----------------- TrivialRelationalExprContext ------------------------------------------------------------------

miniaParser::RelationalExprContext* miniaParser::TrivialRelationalExprContext::relationalExpr() {
  return getRuleContext<miniaParser::RelationalExprContext>(0);
}

miniaParser::TrivialRelationalExprContext::TrivialRelationalExprContext(EqualityExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialRelationalExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialRelationalExpr(this);
}
void miniaParser::TrivialRelationalExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialRelationalExpr(this);
}
miniaParser::EqualityExprContext* miniaParser::equalityExpr() {
  EqualityExprContext *_localctx = _tracker.createInstance<EqualityExprContext>(_ctx, getState());
  enterRule(_localctx, 10, miniaParser::RuleEqualityExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<miniaParser::EqualExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(69);
      relationalExpr();
      setState(70);
      match(miniaParser::T_EQ);
      setState(71);
      relationalExpr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<miniaParser::NotEqualExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(73);
      relationalExpr();
      setState(74);
      match(miniaParser::T_NEQ);
      setState(75);
      relationalExpr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<miniaParser::TrivialRelationalExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(77);
      relationalExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExprContext ------------------------------------------------------------------

miniaParser::RelationalExprContext::RelationalExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::RelationalExprContext::getRuleIndex() const {
  return miniaParser::RuleRelationalExpr;
}

void miniaParser::RelationalExprContext::copyFrom(RelationalExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrivialAdditiveExprContext ------------------------------------------------------------------

miniaParser::AdditiveExprContext* miniaParser::TrivialAdditiveExprContext::additiveExpr() {
  return getRuleContext<miniaParser::AdditiveExprContext>(0);
}

miniaParser::TrivialAdditiveExprContext::TrivialAdditiveExprContext(RelationalExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialAdditiveExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialAdditiveExpr(this);
}
void miniaParser::TrivialAdditiveExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialAdditiveExpr(this);
}
//----------------- GreaterThanExprContext ------------------------------------------------------------------

std::vector<miniaParser::AdditiveExprContext *> miniaParser::GreaterThanExprContext::additiveExpr() {
  return getRuleContexts<miniaParser::AdditiveExprContext>();
}

miniaParser::AdditiveExprContext* miniaParser::GreaterThanExprContext::additiveExpr(size_t i) {
  return getRuleContext<miniaParser::AdditiveExprContext>(i);
}

tree::TerminalNode* miniaParser::GreaterThanExprContext::T_GT() {
  return getToken(miniaParser::T_GT, 0);
}

miniaParser::GreaterThanExprContext::GreaterThanExprContext(RelationalExprContext *ctx) { copyFrom(ctx); }

void miniaParser::GreaterThanExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGreaterThanExpr(this);
}
void miniaParser::GreaterThanExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGreaterThanExpr(this);
}
//----------------- LessThanEqualExprContext ------------------------------------------------------------------

std::vector<miniaParser::AdditiveExprContext *> miniaParser::LessThanEqualExprContext::additiveExpr() {
  return getRuleContexts<miniaParser::AdditiveExprContext>();
}

miniaParser::AdditiveExprContext* miniaParser::LessThanEqualExprContext::additiveExpr(size_t i) {
  return getRuleContext<miniaParser::AdditiveExprContext>(i);
}

tree::TerminalNode* miniaParser::LessThanEqualExprContext::T_LTE() {
  return getToken(miniaParser::T_LTE, 0);
}

miniaParser::LessThanEqualExprContext::LessThanEqualExprContext(RelationalExprContext *ctx) { copyFrom(ctx); }

void miniaParser::LessThanEqualExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLessThanEqualExpr(this);
}
void miniaParser::LessThanEqualExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLessThanEqualExpr(this);
}
//----------------- LessThanExprContext ------------------------------------------------------------------

std::vector<miniaParser::AdditiveExprContext *> miniaParser::LessThanExprContext::additiveExpr() {
  return getRuleContexts<miniaParser::AdditiveExprContext>();
}

miniaParser::AdditiveExprContext* miniaParser::LessThanExprContext::additiveExpr(size_t i) {
  return getRuleContext<miniaParser::AdditiveExprContext>(i);
}

tree::TerminalNode* miniaParser::LessThanExprContext::T_LT() {
  return getToken(miniaParser::T_LT, 0);
}

miniaParser::LessThanExprContext::LessThanExprContext(RelationalExprContext *ctx) { copyFrom(ctx); }

void miniaParser::LessThanExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLessThanExpr(this);
}
void miniaParser::LessThanExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLessThanExpr(this);
}
//----------------- GreaterThanEqualExprContext ------------------------------------------------------------------

std::vector<miniaParser::AdditiveExprContext *> miniaParser::GreaterThanEqualExprContext::additiveExpr() {
  return getRuleContexts<miniaParser::AdditiveExprContext>();
}

miniaParser::AdditiveExprContext* miniaParser::GreaterThanEqualExprContext::additiveExpr(size_t i) {
  return getRuleContext<miniaParser::AdditiveExprContext>(i);
}

tree::TerminalNode* miniaParser::GreaterThanEqualExprContext::T_GTE() {
  return getToken(miniaParser::T_GTE, 0);
}

miniaParser::GreaterThanEqualExprContext::GreaterThanEqualExprContext(RelationalExprContext *ctx) { copyFrom(ctx); }

void miniaParser::GreaterThanEqualExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGreaterThanEqualExpr(this);
}
void miniaParser::GreaterThanEqualExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGreaterThanEqualExpr(this);
}
miniaParser::RelationalExprContext* miniaParser::relationalExpr() {
  RelationalExprContext *_localctx = _tracker.createInstance<RelationalExprContext>(_ctx, getState());
  enterRule(_localctx, 12, miniaParser::RuleRelationalExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(97);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<miniaParser::GreaterThanExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(80);
      additiveExpr();
      setState(81);
      match(miniaParser::T_GT);
      setState(82);
      additiveExpr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<miniaParser::GreaterThanEqualExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(84);
      additiveExpr();
      setState(85);
      match(miniaParser::T_GTE);
      setState(86);
      additiveExpr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<miniaParser::LessThanExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(88);
      additiveExpr();
      setState(89);
      match(miniaParser::T_LT);
      setState(90);
      additiveExpr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<miniaParser::LessThanEqualExprContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(92);
      additiveExpr();
      setState(93);
      match(miniaParser::T_LTE);
      setState(94);
      additiveExpr();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<miniaParser::TrivialAdditiveExprContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(96);
      additiveExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExprContext ------------------------------------------------------------------

miniaParser::AdditiveExprContext::AdditiveExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::AdditiveExprContext::getRuleIndex() const {
  return miniaParser::RuleAdditiveExpr;
}

void miniaParser::AdditiveExprContext::copyFrom(AdditiveExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrivialMultiplicativeExprContext ------------------------------------------------------------------

miniaParser::MultiplicativeExprContext* miniaParser::TrivialMultiplicativeExprContext::multiplicativeExpr() {
  return getRuleContext<miniaParser::MultiplicativeExprContext>(0);
}

miniaParser::TrivialMultiplicativeExprContext::TrivialMultiplicativeExprContext(AdditiveExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialMultiplicativeExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialMultiplicativeExpr(this);
}
void miniaParser::TrivialMultiplicativeExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialMultiplicativeExpr(this);
}
//----------------- SubExprContext ------------------------------------------------------------------

std::vector<miniaParser::MultiplicativeExprContext *> miniaParser::SubExprContext::multiplicativeExpr() {
  return getRuleContexts<miniaParser::MultiplicativeExprContext>();
}

miniaParser::MultiplicativeExprContext* miniaParser::SubExprContext::multiplicativeExpr(size_t i) {
  return getRuleContext<miniaParser::MultiplicativeExprContext>(i);
}

tree::TerminalNode* miniaParser::SubExprContext::T_SUB() {
  return getToken(miniaParser::T_SUB, 0);
}

miniaParser::SubExprContext::SubExprContext(AdditiveExprContext *ctx) { copyFrom(ctx); }

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

std::vector<miniaParser::MultiplicativeExprContext *> miniaParser::AddExprContext::multiplicativeExpr() {
  return getRuleContexts<miniaParser::MultiplicativeExprContext>();
}

miniaParser::MultiplicativeExprContext* miniaParser::AddExprContext::multiplicativeExpr(size_t i) {
  return getRuleContext<miniaParser::MultiplicativeExprContext>(i);
}

tree::TerminalNode* miniaParser::AddExprContext::T_ADD() {
  return getToken(miniaParser::T_ADD, 0);
}

miniaParser::AddExprContext::AddExprContext(AdditiveExprContext *ctx) { copyFrom(ctx); }

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
miniaParser::AdditiveExprContext* miniaParser::additiveExpr() {
  AdditiveExprContext *_localctx = _tracker.createInstance<AdditiveExprContext>(_ctx, getState());
  enterRule(_localctx, 14, miniaParser::RuleAdditiveExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<miniaParser::AddExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(99);
      multiplicativeExpr();
      setState(100);
      match(miniaParser::T_ADD);
      setState(101);
      multiplicativeExpr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<miniaParser::SubExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(103);
      multiplicativeExpr();
      setState(104);
      match(miniaParser::T_SUB);
      setState(105);
      multiplicativeExpr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<miniaParser::TrivialMultiplicativeExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(107);
      multiplicativeExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExprContext ------------------------------------------------------------------

miniaParser::MultiplicativeExprContext::MultiplicativeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::MultiplicativeExprContext::getRuleIndex() const {
  return miniaParser::RuleMultiplicativeExpr;
}

void miniaParser::MultiplicativeExprContext::copyFrom(MultiplicativeExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulExprContext ------------------------------------------------------------------

std::vector<miniaParser::UnaryExprContext *> miniaParser::MulExprContext::unaryExpr() {
  return getRuleContexts<miniaParser::UnaryExprContext>();
}

miniaParser::UnaryExprContext* miniaParser::MulExprContext::unaryExpr(size_t i) {
  return getRuleContext<miniaParser::UnaryExprContext>(i);
}

tree::TerminalNode* miniaParser::MulExprContext::T_MUL() {
  return getToken(miniaParser::T_MUL, 0);
}

miniaParser::MulExprContext::MulExprContext(MultiplicativeExprContext *ctx) { copyFrom(ctx); }

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
//----------------- DivExprContext ------------------------------------------------------------------

std::vector<miniaParser::UnaryExprContext *> miniaParser::DivExprContext::unaryExpr() {
  return getRuleContexts<miniaParser::UnaryExprContext>();
}

miniaParser::UnaryExprContext* miniaParser::DivExprContext::unaryExpr(size_t i) {
  return getRuleContext<miniaParser::UnaryExprContext>(i);
}

tree::TerminalNode* miniaParser::DivExprContext::T_DIV() {
  return getToken(miniaParser::T_DIV, 0);
}

miniaParser::DivExprContext::DivExprContext(MultiplicativeExprContext *ctx) { copyFrom(ctx); }

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
//----------------- TrivialUnaryExprContext ------------------------------------------------------------------

miniaParser::UnaryExprContext* miniaParser::TrivialUnaryExprContext::unaryExpr() {
  return getRuleContext<miniaParser::UnaryExprContext>(0);
}

miniaParser::TrivialUnaryExprContext::TrivialUnaryExprContext(MultiplicativeExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialUnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialUnaryExpr(this);
}
void miniaParser::TrivialUnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialUnaryExpr(this);
}
//----------------- ModExprContext ------------------------------------------------------------------

std::vector<miniaParser::UnaryExprContext *> miniaParser::ModExprContext::unaryExpr() {
  return getRuleContexts<miniaParser::UnaryExprContext>();
}

miniaParser::UnaryExprContext* miniaParser::ModExprContext::unaryExpr(size_t i) {
  return getRuleContext<miniaParser::UnaryExprContext>(i);
}

tree::TerminalNode* miniaParser::ModExprContext::T_MOD() {
  return getToken(miniaParser::T_MOD, 0);
}

miniaParser::ModExprContext::ModExprContext(MultiplicativeExprContext *ctx) { copyFrom(ctx); }

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
miniaParser::MultiplicativeExprContext* miniaParser::multiplicativeExpr() {
  MultiplicativeExprContext *_localctx = _tracker.createInstance<MultiplicativeExprContext>(_ctx, getState());
  enterRule(_localctx, 16, miniaParser::RuleMultiplicativeExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(123);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<miniaParser::MulExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(110);
      unaryExpr();
      setState(111);
      match(miniaParser::T_MUL);
      setState(112);
      unaryExpr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<miniaParser::DivExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(114);
      unaryExpr();
      setState(115);
      match(miniaParser::T_DIV);
      setState(116);
      unaryExpr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<miniaParser::ModExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(118);
      unaryExpr();
      setState(119);
      match(miniaParser::T_MOD);
      setState(120);
      unaryExpr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<miniaParser::TrivialUnaryExprContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(122);
      unaryExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExprContext ------------------------------------------------------------------

miniaParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::UnaryExprContext::getRuleIndex() const {
  return miniaParser::RuleUnaryExpr;
}

void miniaParser::UnaryExprContext::copyFrom(UnaryExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrivialPrimaryExprContext ------------------------------------------------------------------

miniaParser::PrimaryExprContext* miniaParser::TrivialPrimaryExprContext::primaryExpr() {
  return getRuleContext<miniaParser::PrimaryExprContext>(0);
}

miniaParser::TrivialPrimaryExprContext::TrivialPrimaryExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrivialPrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrivialPrimaryExpr(this);
}
void miniaParser::TrivialPrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrivialPrimaryExpr(this);
}
//----------------- NegExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::NegExprContext::T_SUB() {
  return getToken(miniaParser::T_SUB, 0);
}

miniaParser::UnaryExprContext* miniaParser::NegExprContext::unaryExpr() {
  return getRuleContext<miniaParser::UnaryExprContext>(0);
}

miniaParser::NegExprContext::NegExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::NegExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegExpr(this);
}
void miniaParser::NegExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegExpr(this);
}
//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::NotExprContext::T_NOT() {
  return getToken(miniaParser::T_NOT, 0);
}

miniaParser::UnaryExprContext* miniaParser::NotExprContext::unaryExpr() {
  return getRuleContext<miniaParser::UnaryExprContext>(0);
}

miniaParser::NotExprContext::NotExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::NotExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpr(this);
}
void miniaParser::NotExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpr(this);
}
miniaParser::UnaryExprContext* miniaParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 18, miniaParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(130);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case miniaParser::T_NOT: {
        _localctx = _tracker.createInstance<miniaParser::NotExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(125);
        match(miniaParser::T_NOT);
        setState(126);
        unaryExpr();
        break;
      }

      case miniaParser::T_SUB: {
        _localctx = _tracker.createInstance<miniaParser::NegExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(127);
        match(miniaParser::T_SUB);
        setState(128);
        unaryExpr();
        break;
      }

      case miniaParser::T__0:
      case miniaParser::T_TRUE:
      case miniaParser::T_FALSE:
      case miniaParser::STRING_LIST:
      case miniaParser::INTEGER_LIST:
      case miniaParser::DECIMAL_LIST:
      case miniaParser::IDENTIFIER:
      case miniaParser::INTEGER:
      case miniaParser::DECIMAL:
      case miniaParser::STRING: {
        _localctx = _tracker.createInstance<miniaParser::TrivialPrimaryExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(129);
        primaryExpr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

miniaParser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::PrimaryExprContext::getRuleIndex() const {
  return miniaParser::RulePrimaryExpr;
}

void miniaParser::PrimaryExprContext::copyFrom(PrimaryExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FunctionCallExprContext ------------------------------------------------------------------

miniaParser::FuncCallContext* miniaParser::FunctionCallExprContext::funcCall() {
  return getRuleContext<miniaParser::FuncCallContext>(0);
}

miniaParser::FunctionCallExprContext::FunctionCallExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::FunctionCallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpr(this);
}
void miniaParser::FunctionCallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpr(this);
}
//----------------- TrueExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::TrueExprContext::T_TRUE() {
  return getToken(miniaParser::T_TRUE, 0);
}

miniaParser::TrueExprContext::TrueExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::TrueExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrueExpr(this);
}
void miniaParser::TrueExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrueExpr(this);
}
//----------------- ColumnExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::ColumnExprContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

miniaParser::ColumnExprContext::ColumnExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

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
//----------------- LiteralExprContext ------------------------------------------------------------------

miniaParser::LiteralContext* miniaParser::LiteralExprContext::literal() {
  return getRuleContext<miniaParser::LiteralContext>(0);
}

miniaParser::LiteralExprContext::LiteralExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::LiteralExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpr(this);
}
void miniaParser::LiteralExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpr(this);
}
//----------------- ParenthesizedExprContext ------------------------------------------------------------------

miniaParser::ExprContext* miniaParser::ParenthesizedExprContext::expr() {
  return getRuleContext<miniaParser::ExprContext>(0);
}

miniaParser::ParenthesizedExprContext::ParenthesizedExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::ParenthesizedExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpr(this);
}
void miniaParser::ParenthesizedExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpr(this);
}
//----------------- ListExprContext ------------------------------------------------------------------

miniaParser::ListLiteralContext* miniaParser::ListExprContext::listLiteral() {
  return getRuleContext<miniaParser::ListLiteralContext>(0);
}

miniaParser::ListExprContext::ListExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::ListExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterListExpr(this);
}
void miniaParser::ListExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitListExpr(this);
}
//----------------- FalseExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::FalseExprContext::T_FALSE() {
  return getToken(miniaParser::T_FALSE, 0);
}

miniaParser::FalseExprContext::FalseExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }

void miniaParser::FalseExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFalseExpr(this);
}
void miniaParser::FalseExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFalseExpr(this);
}
miniaParser::PrimaryExprContext* miniaParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 20, miniaParser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<miniaParser::ParenthesizedExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(132);
      match(miniaParser::T__0);
      setState(133);
      expr();
      setState(134);
      match(miniaParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<miniaParser::FunctionCallExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(136);
      funcCall();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<miniaParser::ColumnExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(137);
      match(miniaParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<miniaParser::LiteralExprContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(138);
      literal();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<miniaParser::ListExprContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(139);
      listLiteral();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<miniaParser::TrueExprContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(140);
      match(miniaParser::T_TRUE);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<miniaParser::FalseExprContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(141);
      match(miniaParser::T_FALSE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListLiteralContext ------------------------------------------------------------------

miniaParser::ListLiteralContext::ListLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::ListLiteralContext::getRuleIndex() const {
  return miniaParser::RuleListLiteral;
}

void miniaParser::ListLiteralContext::copyFrom(ListLiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntegerListExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::IntegerListExprContext::INTEGER_LIST() {
  return getToken(miniaParser::INTEGER_LIST, 0);
}

miniaParser::IntegerListExprContext::IntegerListExprContext(ListLiteralContext *ctx) { copyFrom(ctx); }

void miniaParser::IntegerListExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerListExpr(this);
}
void miniaParser::IntegerListExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerListExpr(this);
}
//----------------- StringListExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::StringListExprContext::STRING_LIST() {
  return getToken(miniaParser::STRING_LIST, 0);
}

miniaParser::StringListExprContext::StringListExprContext(ListLiteralContext *ctx) { copyFrom(ctx); }

void miniaParser::StringListExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringListExpr(this);
}
void miniaParser::StringListExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringListExpr(this);
}
//----------------- DecimalListExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::DecimalListExprContext::DECIMAL_LIST() {
  return getToken(miniaParser::DECIMAL_LIST, 0);
}

miniaParser::DecimalListExprContext::DecimalListExprContext(ListLiteralContext *ctx) { copyFrom(ctx); }

void miniaParser::DecimalListExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecimalListExpr(this);
}
void miniaParser::DecimalListExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecimalListExpr(this);
}
miniaParser::ListLiteralContext* miniaParser::listLiteral() {
  ListLiteralContext *_localctx = _tracker.createInstance<ListLiteralContext>(_ctx, getState());
  enterRule(_localctx, 22, miniaParser::RuleListLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case miniaParser::STRING_LIST: {
        _localctx = _tracker.createInstance<miniaParser::StringListExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(144);
        match(miniaParser::STRING_LIST);
        break;
      }

      case miniaParser::INTEGER_LIST: {
        _localctx = _tracker.createInstance<miniaParser::IntegerListExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(145);
        match(miniaParser::INTEGER_LIST);
        break;
      }

      case miniaParser::DECIMAL_LIST: {
        _localctx = _tracker.createInstance<miniaParser::DecimalListExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(146);
        match(miniaParser::DECIMAL_LIST);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

miniaParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* miniaParser::FuncCallContext::IDENTIFIER() {
  return getToken(miniaParser::IDENTIFIER, 0);
}

miniaParser::ExprListContext* miniaParser::FuncCallContext::exprList() {
  return getRuleContext<miniaParser::ExprListContext>(0);
}


size_t miniaParser::FuncCallContext::getRuleIndex() const {
  return miniaParser::RuleFuncCall;
}

void miniaParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}

void miniaParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}

miniaParser::FuncCallContext* miniaParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 24, miniaParser::RuleFuncCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(miniaParser::IDENTIFIER);
    setState(150);
    match(miniaParser::T__0);
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1065386210) != 0)) {
      setState(151);
      exprList();
    }
    setState(154);
    match(miniaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprListContext ------------------------------------------------------------------

miniaParser::ExprListContext::ExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<miniaParser::ExprContext *> miniaParser::ExprListContext::expr() {
  return getRuleContexts<miniaParser::ExprContext>();
}

miniaParser::ExprContext* miniaParser::ExprListContext::expr(size_t i) {
  return getRuleContext<miniaParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> miniaParser::ExprListContext::COMMA() {
  return getTokens(miniaParser::COMMA);
}

tree::TerminalNode* miniaParser::ExprListContext::COMMA(size_t i) {
  return getToken(miniaParser::COMMA, i);
}


size_t miniaParser::ExprListContext::getRuleIndex() const {
  return miniaParser::RuleExprList;
}

void miniaParser::ExprListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprList(this);
}

void miniaParser::ExprListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<miniaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprList(this);
}

miniaParser::ExprListContext* miniaParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 26, miniaParser::RuleExprList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    expr();
    setState(161);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == miniaParser::COMMA) {
      setState(157);
      match(miniaParser::COMMA);
      setState(158);
      expr();
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

miniaParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t miniaParser::LiteralContext::getRuleIndex() const {
  return miniaParser::RuleLiteral;
}

void miniaParser::LiteralContext::copyFrom(LiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StringExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::StringExprContext::STRING() {
  return getToken(miniaParser::STRING, 0);
}

miniaParser::StringExprContext::StringExprContext(LiteralContext *ctx) { copyFrom(ctx); }

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
//----------------- IntegerExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::IntegerExprContext::INTEGER() {
  return getToken(miniaParser::INTEGER, 0);
}

miniaParser::IntegerExprContext::IntegerExprContext(LiteralContext *ctx) { copyFrom(ctx); }

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
//----------------- DecimalExprContext ------------------------------------------------------------------

tree::TerminalNode* miniaParser::DecimalExprContext::DECIMAL() {
  return getToken(miniaParser::DECIMAL, 0);
}

miniaParser::DecimalExprContext::DecimalExprContext(LiteralContext *ctx) { copyFrom(ctx); }

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
miniaParser::LiteralContext* miniaParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 28, miniaParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(167);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case miniaParser::STRING: {
        _localctx = _tracker.createInstance<miniaParser::StringExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(164);
        match(miniaParser::STRING);
        break;
      }

      case miniaParser::INTEGER: {
        _localctx = _tracker.createInstance<miniaParser::IntegerExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(165);
        match(miniaParser::INTEGER);
        break;
      }

      case miniaParser::DECIMAL: {
        _localctx = _tracker.createInstance<miniaParser::DecimalExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(166);
        match(miniaParser::DECIMAL);
        break;
      }

    default:
      throw NoViableAltException(this);
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
    case 3: return logicalOrExprSempred(antlrcpp::downCast<LogicalOrExprContext *>(context), predicateIndex);
    case 4: return logicalAndExprSempred(antlrcpp::downCast<LogicalAndExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool miniaParser::logicalOrExprSempred(LogicalOrExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool miniaParser::logicalAndExprSempred(LogicalAndExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

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
