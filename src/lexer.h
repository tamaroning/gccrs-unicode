#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Codepoint {
public:
  Codepoint (unsigned int v) : v(v) {}

  /*
  static Codepoint eof() {
    return Codepoint(UINT32_MAX);
  }

  bool is_eof() {
    return v == UINT32_MAX;
  }
  */

  unsigned int v;

  bool is_legacy_id_start() {
    return ('A' <= v && v <= 'Z') || ('a' <= v && v <= 'z') || v == '_';
  }

  bool is_legacy_id_continue() {
    return is_legacy_id_start() || ('0' <= v && v <= '9');
  }
};

class Lexer {
public:
  Lexer(std::vector<char> source) : source(source), pos(0) {}

  // just tokenizes sequence of identifiers and whitespaces
  void lex() {
    int current_char;
    while (!is_eof()) {
      current_char = peek_one_byte();
      std::cout << "current pos: " << pos << std::endl;
      std::cout << "current char: " << current_char << std::endl;

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

    tokens.push_back(
        std::make_unique<Token>(Token(start_pos, IDENT, std::move(str))));
  }

private:
  char peek_one_byte() { return source[pos]; }

  char skip_one_byte() {
    if (pos <= source.size())
      pos++;

    return source[pos];
  }

  // NOTE: This function does not work correctly for some invalid utf8
  // continuation. (e.g, 0xFE and 0xFF) This repo is just for experiment so we
  // do not deal with them.
  int get_codepoint_length() {
    char input = peek_one_byte();
    if (input < 0x7f) {
      // 1 byte
      return 1;
    } else if ((input & 0xE0) == 0xC0) {
      // 2 bytes
      return 2;
    } else if ((input & 0xF0) == 0xE0) {
      // 3 bytes
      return 3;
    } else if ((input & 0xF8) == 0xF0) {
      // 4 bytes
      return 4;
    } else {
      std::cout << "invalid utf8 charcter" << std::endl;
      std::exit(1);
    }
  }

  // FIXME: スキップしないようにする
  Codepoint peek_one_utf8_character() {
    char input = skip_one_byte();
    if (input < 0x7f) {
      // 1 byte
      return input;
    } else if ((input & 0xE0) == 0xC0) {
      // 2 bytes
      char input2 = skip_one_byte();
      return ((input & 0b11111) << 5) | (input2 & 0b111111);
    } else if ((input & 0xF0) == 0xE0) {
      // 3 bytes
      char input2 = skip_one_byte();
      char input3 = skip_one_byte();
      return ((input & 0b1111) << 12) | ((input2 & 0b111111) << 6) |
             (input3 & 0b111111);
    } else if ((input & 0xF8) == 0xF0) {
      // 4 bytes
      char input2 = skip_one_byte();
      char input3 = skip_one_byte();
      char input4 = skip_one_byte();
      return ((input & 0b111) << 18) | ((input2 & 0b111111) << 12) |
             ((input3 & 0b111111) << 6) | (input4 & 0b111111);
    } else {
      std::cout << "invalid utf8 charcter" << std::endl;
      std::exit(1);
    }
  }

  bool is_alpha() {
    char c = peek_one_byte();
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
  }

  bool is_whitespace() { return peek_one_byte() == ' '; }

  bool is_eof() { return pos == source.size(); }

  std::vector<char> source;
  int pos;
  std::vector<TokenPtr> tokens;
};

#endif