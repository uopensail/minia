#include "grammar/minia.h"
#include "grammar/miniaLexer.h"
#include <iostream>

int main() {
  antlr4::ANTLRInputStream input("z = a + 1111; x = t*y");
  miniaLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  miniaParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.prog();

  minia::MiniaListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  const auto &nodes = listener.nodes_;
  for (size_t i = 0; i < nodes.size(); ++i) {
    std::cout << nodes[i]->name << " " << int(nodes[i]->type) << std::endl;
  }

  return 0;
}