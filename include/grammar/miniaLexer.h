
// Generated from minia.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  miniaLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T_AND = 3, T_OR = 4, T_NOT = 5, T_TRUE = 6, T_FALSE = 7, 
    T_EQ = 8, T_NEQ = 9, T_GT = 10, T_GTE = 11, T_LT = 12, T_LTE = 13, T_ADD = 14, 
    T_SUB = 15, T_MUL = 16, T_DIV = 17, T_MOD = 18, COMMA = 19, SEMI = 20, 
    T_EQUAL = 21, QUOTA = 22, STRING_LIST = 23, INTEGER_LIST = 24, DECIMAL_LIST = 25, 
    IDENTIFIER = 26, INTEGER = 27, DECIMAL = 28, STRING = 29, WS = 30
  };

  explicit miniaLexer(antlr4::CharStream *input);

  ~miniaLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

