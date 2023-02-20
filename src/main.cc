#include "lexer.h"

int main(void) {
  std::string s = "abc xyz def あいう え おかき ";
  std::vector<char> v(s.begin(), s.end());

  Lexer lexer(v);

  lexer.lex();
  lexer.dump();

  return 0;
}