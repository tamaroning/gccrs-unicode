#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

class Lexer {
public:
  Lexer(std::istringstream& file) : file(file), pos(0) {}

  void lex() {
    int current_char;
    while (true) {
      current_char = peek_input();
      std::cout << current_char;

      if (current_char == EOF)
        break;

      if (is_whitespace()) {
        skip_input();
        continue;
      }
      parse_ident();
    }
  }

  void dump() {
    for (TokenPtr &tok : tokens) {
      tok->dump();
    }
  }

  void parse_ident() {
    std::string str;
    str.reserve(16);

    str += peek_input();
    skip_input();
    int length = 1;

    // Token ident = Token(0, IDENT, std::move(str));
    tokens.push_back(std::make_unique<Token>(Token(0, IDENT, std::move(str))));
  }

private:
  char peek_input() { return file.peek(); }

  void skip_input() {
    pos++;
    if (!file.eof()) {
      file.ignore(1);
    }
  }

  bool is_alpha() { return 'a' < peek_input() && peek_input() < 'z'; }

  bool is_whitespace() { return peek_input() == ' '; }

  bool is_eof() { return peek_input() == EOF || file.eof(); }

  std::istringstream& file;
  int pos;
  std::vector<TokenPtr> tokens;
};

#endif