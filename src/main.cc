#include "lexer.h"
#include <iostream>
#include <sstream>


int main(void) {
  std::istringstream src = std::istringstream("abc xyz");

  Lexer lexer(src);

  lexer.lex();
  lexer.dump();

  return 0;
}