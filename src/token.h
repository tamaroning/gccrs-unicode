#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <memory>

enum TokenKind {
  IDENT,
};

class Token {
public:
  Token(unsigned int pos, TokenKind kind, std::string &&paramStr)
      : pos(pos), kind(kind), str(paramStr) {}

  void dump() {
    std::cout << "Token {" << std::endl;
    std::cout << "\tkind: " << kind << std::endl;
    std::cout << "\tpos: " << pos << std::endl;
    std::cout << "\tstr: " << str << std::endl;
    std::cout << "}" << std::endl;
  }

private:
  // token kind
  TokenKind kind;

  // location (start position)
  unsigned int pos;

  // associated text
  std::string str;
};

typedef std::unique_ptr<Token> TokenPtr;

#endif
