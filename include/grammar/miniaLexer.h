
// Generated from minia.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  miniaLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, DOT = 3, COMMA = 4, SEMI = 5, QUOTA = 6, T_EQUAL = 7, 
    T_ADD = 8, T_SUB = 9, T_MUL = 10, T_DIV = 11, T_MOD = 12, IDENTIFIER = 13, 
    INTEGER_LIST = 14, INTEGER = 15, DECIMAL_LIST = 16, DECIMAL = 17, STRING_LIST = 18, 
    STRING = 19, WS = 20
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

