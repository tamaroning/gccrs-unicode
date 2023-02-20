#include "lexer.h"

int main(void) {
  // Use Japanese alphabets as an example
  std::string s = "abc\nxyz\t\tあいうえお \r かきくけこ ";

  std::vector<char> v(s.begin(), s.end());

  Lexer lexer(v);

  lexer.lex();
  lexer.dump();

  return 0;
}