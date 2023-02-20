#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "unicode/unicode.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Codepoint {
public:
  Codepoint(unsigned int v) : v(v) {}

  unsigned int v;
};

class Lexer {
public:
  Lexer(std::vector<char> source) : source(source), pos(0) {}

  // just tokenizes sequence of identifiers and whitespaces
  void lex() {
    Codepoint current_char(0);
    while (!is_eof()) {
      std::cout << "current pos: " << pos << std::endl;
      std::cout << "current input(1byte): 0x" << std::hex << peek_input()
                << std::dec << std::endl;
      current_char = peek_one_utf8_character();
      std::cout << "current char: 0x" << std::hex << current_char.v << std::dec
                << std::endl;

      if (is_whitespace()) {
        advance_input();
        continue;
      } else if (is_xid_start()) {
        parse_ident();
      }
    }
  }

  void dump() {
    for (TokenPtr &tok : tokens) {
      tok->dump();
    }
  }

  void parse_ident() {
    int start_pos = pos;

    // identifiers must start with XID_Start and continue with XID_Continue
    // refs:
    // UAX31:
    // https://unicode.org/reports/tr31/#Table_Lexical_Classes_for_Identifiers
    // Rust:
    // https://doc.rust-lang.org/reference/identifiers.html?highlight=unicode#identifiers
    assert(is_xid_start());
    advance_one_utf8_charcter();

    while (is_xid_continue()) {
      advance_one_utf8_charcter();
    }

    std::string str(source.begin() + start_pos, source.begin() + pos);
    tokens.push_back(
        std::make_unique<Token>(Token(start_pos, IDENT, std::move(str))));
  }

private:
  unsigned int peek_input() { return peek_input(0); }

  unsigned int peek_input(int nth) {
    if (pos + nth >= source.size())
      return EOF;
    return source[pos + nth];
  }

  // advance input by 1 byte
  void advance_input() { advance_input(1); }

  // advance input by n byte
  void advance_input(int n) {
    if (pos + n >= source.size())
      pos = source.size();
    else
      pos += n;
  }

  // NOTE: These function `get_codepoint_length` and `peek_one_utf8_character`
  // does not work correctly for some invalid utf8 continuation. (e.g, 0xFE and
  // 0xFF) This repo is just for experiment so we do not deal with them.
  int get_codepoint_length() {
    unsigned int input = peek_input();
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

  Codepoint peek_one_utf8_character() {
    unsigned int input = peek_input();
    if (input < 0x7f) {
      // 1 byte
      return input;
    } else if ((input & 0xE0) == 0xC0) {
      // 2 bytes
      unsigned int input2 = peek_input(1);
      return ((input & 0b11111) << 5) | (input2 & 0b111111);
    } else if ((input & 0xF0) == 0xE0) {
      // 3 bytes
      unsigned int input2 = peek_input(1);
      unsigned int input3 = peek_input(2);
      return ((input & 0b1111) << 12) | ((input2 & 0b111111) << 6) |
             (input3 & 0b111111);
    } else if ((input & 0xF8) == 0xF0) {
      // 4 bytes
      unsigned int input2 = peek_input(1);
      unsigned int input3 = peek_input(2);
      unsigned int input4 = peek_input(3);
      return ((input & 0b111) << 18) | ((input2 & 0b111111) << 12) |
             ((input3 & 0b111111) << 6) | (input4 & 0b111111);
    } else {
      std::cout << "invalid utf8 charcter" << std::endl;
      std::exit(1);
    }
  }

  // returns the length of codepoint (i.e. 1~4 bytes)
  int advance_one_utf8_charcter() {
    int ret = get_codepoint_length();
    pos += ret;
    return ret;
  }

  bool is_xid_start() {
    unsigned int v = peek_input();
    // Fast-path for ascii idents
    if (('A' <= v && v <= 'Z') || ('a' <= v && v <= 'z'))
      return true;

    unsigned int cp = peek_one_utf8_character().v;
    return cp > 0x7f && Unicode::is_xid_start(cp);
  }

  bool is_xid_continue() {
    unsigned int v = peek_input();
    // Fast-path for ascii idents
    if (('A' <= v && v <= 'Z') || ('a' <= v && v <= 'z') ||
        ('0' <= v && v <= '9') || v == '_')
      return true;

    unsigned int cp = peek_one_utf8_character().v;
    return cp > 0x7f && Unicode::is_xid_continue(cp);
  }

  bool is_whitespace() {
    unsigned int cp = peek_one_utf8_character().v;
    return cp == 0x0009    // \t
           || cp == 0x000a // \n
           || cp == 0x000b // vertical tab
           || cp == 0x000c // form feed
           || cp == 0x000d // \r
           || cp == 0x0020 // space
           // NEXT LINE from latin1
           || cp == 0x0085
           // Bidi markers
           || cp == 0x200e // LEFT-TO-RIGHT MARK
           || cp == 0x200f // RIGHT-TO-LEFT MARK
           // Dedicated whitespace characters from Unicode
           || cp == 0x2028 // LINE SEPARATOR
           || cp == 0x2029 // PARAGRAPH SEPARATOR
        ;
  }

  bool is_eof() { return pos == source.size(); }

  std::vector<char> source;
  int pos;
  std::vector<TokenPtr> tokens;
};

#endif