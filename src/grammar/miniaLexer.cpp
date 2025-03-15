
// Generated from minia.g4 by ANTLR 4.13.2


#include "miniaLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct MiniaLexerStaticData final {
  MiniaLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniaLexerStaticData(const MiniaLexerStaticData&) = delete;
  MiniaLexerStaticData(MiniaLexerStaticData&&) = delete;
  MiniaLexerStaticData& operator=(const MiniaLexerStaticData&) = delete;
  MiniaLexerStaticData& operator=(MiniaLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minialexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MiniaLexerStaticData> minialexerLexerStaticData = nullptr;

void minialexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (minialexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(minialexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MiniaLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "DOT", "COMMA", "SEMI", "QUOTA", "T_EQUAL", "T_ADD", 
      "T_SUB", "T_MUL", "T_DIV", "T_MOD", "IDENTIFIER", "INTEGER_LIST", 
      "INTEGER", "DECIMAL_LIST", "DECIMAL", "STRING_LIST", "STRING", "ESC", 
      "UNICODE", "HEX", "SAFECODEPOINT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,20,220,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,
  	1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,5,12,
  	76,8,12,10,12,12,12,79,9,12,1,13,1,13,1,13,1,13,5,13,85,8,13,10,13,12,
  	13,88,9,13,3,13,90,8,13,5,13,92,8,13,10,13,12,13,95,9,13,1,13,1,13,5,
  	13,99,8,13,10,13,12,13,102,9,13,1,13,1,13,1,14,3,14,107,8,14,1,14,1,14,
  	1,14,5,14,112,8,14,10,14,12,14,115,9,14,3,14,117,8,14,1,15,1,15,1,15,
  	1,15,5,15,123,8,15,10,15,12,15,126,9,15,3,15,128,8,15,5,15,130,8,15,10,
  	15,12,15,133,9,15,1,15,1,15,5,15,137,8,15,10,15,12,15,140,9,15,1,15,1,
  	15,1,16,3,16,145,8,16,1,16,1,16,1,16,5,16,150,8,16,10,16,12,16,153,9,
  	16,3,16,155,8,16,1,16,1,16,5,16,159,8,16,10,16,12,16,162,9,16,1,17,1,
  	17,1,17,1,17,5,17,168,8,17,10,17,12,17,171,9,17,3,17,173,8,17,5,17,175,
  	8,17,10,17,12,17,178,9,17,1,17,1,17,5,17,182,8,17,10,17,12,17,185,9,17,
  	1,17,1,17,1,18,1,18,1,18,5,18,192,8,18,10,18,12,18,195,9,18,1,18,1,18,
  	1,19,1,19,1,19,3,19,202,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,
  	1,22,1,22,1,23,4,23,215,8,23,11,23,12,23,216,1,23,1,23,0,0,24,1,1,3,2,
  	5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,
  	16,33,17,35,18,37,19,39,0,41,0,43,0,45,0,47,20,1,0,9,3,0,65,90,95,95,
  	97,122,4,0,48,57,65,90,95,95,97,122,1,0,49,57,1,0,48,57,13,0,34,34,47,
  	47,66,66,70,70,78,78,82,82,84,84,92,92,98,98,102,102,110,110,114,114,
  	116,116,2,0,85,85,117,117,3,0,48,57,65,70,97,102,3,0,0,31,34,34,92,92,
  	3,0,9,10,13,13,32,32,239,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,47,1,0,0,
  	0,1,49,1,0,0,0,3,51,1,0,0,0,5,53,1,0,0,0,7,55,1,0,0,0,9,57,1,0,0,0,11,
  	59,1,0,0,0,13,61,1,0,0,0,15,63,1,0,0,0,17,65,1,0,0,0,19,67,1,0,0,0,21,
  	69,1,0,0,0,23,71,1,0,0,0,25,73,1,0,0,0,27,80,1,0,0,0,29,116,1,0,0,0,31,
  	118,1,0,0,0,33,144,1,0,0,0,35,163,1,0,0,0,37,188,1,0,0,0,39,198,1,0,0,
  	0,41,203,1,0,0,0,43,209,1,0,0,0,45,211,1,0,0,0,47,214,1,0,0,0,49,50,5,
  	40,0,0,50,2,1,0,0,0,51,52,5,41,0,0,52,4,1,0,0,0,53,54,5,46,0,0,54,6,1,
  	0,0,0,55,56,5,44,0,0,56,8,1,0,0,0,57,58,5,59,0,0,58,10,1,0,0,0,59,60,
  	5,34,0,0,60,12,1,0,0,0,61,62,5,61,0,0,62,14,1,0,0,0,63,64,5,43,0,0,64,
  	16,1,0,0,0,65,66,5,45,0,0,66,18,1,0,0,0,67,68,5,42,0,0,68,20,1,0,0,0,
  	69,70,5,47,0,0,70,22,1,0,0,0,71,72,5,37,0,0,72,24,1,0,0,0,73,77,7,0,0,
  	0,74,76,7,1,0,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,
  	0,78,26,1,0,0,0,79,77,1,0,0,0,80,93,5,91,0,0,81,89,3,29,14,0,82,86,3,
  	7,3,0,83,85,3,47,23,0,84,83,1,0,0,0,85,88,1,0,0,0,86,84,1,0,0,0,86,87,
  	1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,89,82,1,0,0,0,89,90,1,0,0,0,90,92,
  	1,0,0,0,91,81,1,0,0,0,92,95,1,0,0,0,93,91,1,0,0,0,93,94,1,0,0,0,94,96,
  	1,0,0,0,95,93,1,0,0,0,96,100,3,29,14,0,97,99,3,47,23,0,98,97,1,0,0,0,
  	99,102,1,0,0,0,100,98,1,0,0,0,100,101,1,0,0,0,101,103,1,0,0,0,102,100,
  	1,0,0,0,103,104,5,93,0,0,104,28,1,0,0,0,105,107,5,45,0,0,106,105,1,0,
  	0,0,106,107,1,0,0,0,107,108,1,0,0,0,108,117,5,48,0,0,109,113,7,2,0,0,
  	110,112,7,3,0,0,111,110,1,0,0,0,112,115,1,0,0,0,113,111,1,0,0,0,113,114,
  	1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,116,106,1,0,0,0,116,109,1,0,0,
  	0,117,30,1,0,0,0,118,131,5,91,0,0,119,127,3,33,16,0,120,124,3,7,3,0,121,
  	123,3,47,23,0,122,121,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,124,125,
  	1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,127,120,1,0,0,0,127,128,1,0,0,
  	0,128,130,1,0,0,0,129,119,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,
  	132,1,0,0,0,132,134,1,0,0,0,133,131,1,0,0,0,134,138,3,33,16,0,135,137,
  	3,47,23,0,136,135,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,138,139,1,0,
  	0,0,139,141,1,0,0,0,140,138,1,0,0,0,141,142,5,93,0,0,142,32,1,0,0,0,143,
  	145,5,45,0,0,144,143,1,0,0,0,144,145,1,0,0,0,145,154,1,0,0,0,146,155,
  	5,48,0,0,147,151,7,2,0,0,148,150,7,3,0,0,149,148,1,0,0,0,150,153,1,0,
  	0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,155,1,0,0,0,153,151,1,0,0,0,154,
  	146,1,0,0,0,154,147,1,0,0,0,155,156,1,0,0,0,156,160,5,46,0,0,157,159,
  	7,3,0,0,158,157,1,0,0,0,159,162,1,0,0,0,160,158,1,0,0,0,160,161,1,0,0,
  	0,161,34,1,0,0,0,162,160,1,0,0,0,163,176,5,91,0,0,164,172,3,37,18,0,165,
  	169,3,7,3,0,166,168,3,47,23,0,167,166,1,0,0,0,168,171,1,0,0,0,169,167,
  	1,0,0,0,169,170,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,172,165,1,0,0,
  	0,172,173,1,0,0,0,173,175,1,0,0,0,174,164,1,0,0,0,175,178,1,0,0,0,176,
  	174,1,0,0,0,176,177,1,0,0,0,177,179,1,0,0,0,178,176,1,0,0,0,179,183,3,
  	37,18,0,180,182,3,47,23,0,181,180,1,0,0,0,182,185,1,0,0,0,183,181,1,0,
  	0,0,183,184,1,0,0,0,184,186,1,0,0,0,185,183,1,0,0,0,186,187,5,93,0,0,
  	187,36,1,0,0,0,188,193,3,11,5,0,189,192,3,39,19,0,190,192,3,45,22,0,191,
  	189,1,0,0,0,191,190,1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,193,194,1,
  	0,0,0,194,196,1,0,0,0,195,193,1,0,0,0,196,197,3,11,5,0,197,38,1,0,0,0,
  	198,201,5,92,0,0,199,202,7,4,0,0,200,202,3,41,20,0,201,199,1,0,0,0,201,
  	200,1,0,0,0,202,40,1,0,0,0,203,204,7,5,0,0,204,205,3,43,21,0,205,206,
  	3,43,21,0,206,207,3,43,21,0,207,208,3,43,21,0,208,42,1,0,0,0,209,210,
  	7,6,0,0,210,44,1,0,0,0,211,212,8,7,0,0,212,46,1,0,0,0,213,215,7,8,0,0,
  	214,213,1,0,0,0,215,216,1,0,0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,218,
  	1,0,0,0,218,219,6,23,0,0,219,48,1,0,0,0,25,0,77,86,89,93,100,106,113,
  	116,124,127,131,138,144,151,154,160,169,172,176,183,191,193,201,216,1,
  	6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minialexerLexerStaticData = std::move(staticData);
}

}

miniaLexer::miniaLexer(CharStream *input) : Lexer(input) {
  miniaLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *minialexerLexerStaticData->atn, minialexerLexerStaticData->decisionToDFA, minialexerLexerStaticData->sharedContextCache);
}

miniaLexer::~miniaLexer() {
  delete _interpreter;
}

std::string miniaLexer::getGrammarFileName() const {
  return "minia.g4";
}

const std::vector<std::string>& miniaLexer::getRuleNames() const {
  return minialexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& miniaLexer::getChannelNames() const {
  return minialexerLexerStaticData->channelNames;
}

const std::vector<std::string>& miniaLexer::getModeNames() const {
  return minialexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& miniaLexer::getVocabulary() const {
  return minialexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView miniaLexer::getSerializedATN() const {
  return minialexerLexerStaticData->serializedATN;
}

const atn::ATN& miniaLexer::getATN() const {
  return *minialexerLexerStaticData->atn;
}




void miniaLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  minialexerLexerInitialize();
#else
  ::antlr4::internal::call_once(minialexerLexerOnceFlag, minialexerLexerInitialize);
#endif
}
