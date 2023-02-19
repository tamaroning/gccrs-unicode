#include "lexer.h"
#include <iostream>
#include <sstream>


int main(void) {
  std::string s = "abc xyz def";
  std::vector<char> v(s.begin(), s.end());

  Lexer lexer(v);

  lexer.lex();
  lexer.dump();

  return 0;
}