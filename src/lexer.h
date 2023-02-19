#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Lexer {
public:
  Lexer(std::istringstream &file) : file(file), pos(0) {}

  void lex() {
    int current_char;
    while (true) {
      current_char = peek_input();
      std::cout << current_char;

      if (is_eof())
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
    int start_pos = pos;

    str.reserve(16);

    str += peek_input();
    skip_input();
    int length = 1;

    while (is_alpha()) {
      int current_char = peek_input();
      str += current_char;
      length++;
      skip_input();
    }

    // Token ident = Token(0, IDENT, std::move(str));
    tokens.push_back(
        std::make_unique<Token>(Token(start_pos, IDENT, std::move(str))));
  }

private:
  char peek_input() { return file.peek(); }

  void skip_input() {
    pos++;
    if (!file.eof()) {
      file.ignore(1);
    }
  }

  bool is_alpha() {
    int c = peek_input();

    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
  }

  bool is_whitespace() { return peek_input() == ' '; }

  bool is_eof() { return peek_input() == EOF; }

  std::istringstream &file;
  int pos;
  std::vector<TokenPtr> tokens;
};

#endif