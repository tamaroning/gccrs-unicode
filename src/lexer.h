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
      current_char = peek_one_byte();
      std::cout << current_char;

      if (is_eof())
        break;

      if (is_whitespace()) {
        skip_one_byte();
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

    str += peek_one_byte();
    skip_one_byte();
    int length = 1;

    while (is_alpha()) {
      int current_char = peek_one_byte();
      str += current_char;
      length++;
      skip_one_byte();
    }

    // Token ident = Token(0, IDENT, std::move(str));
    tokens.push_back(
        std::make_unique<Token>(Token(start_pos, IDENT, std::move(str))));
  }

private:
  char peek_one_byte() { return file.peek(); }

  void skip_one_byte() {
    pos++;
    if (!file.eof()) {
      file.ignore(1);
    }
  }

  bool is_alpha() {
    int c = peek_one_byte();

    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
  }

  bool is_whitespace() { return peek_one_byte() == ' '; }

  bool is_eof() { return peek_one_byte() == EOF; }

  std::istringstream &file;
  int pos;
  std::vector<TokenPtr> tokens;
};

#endif