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
  // Token kind.
  TokenKind kind;

  // Token location.
  // ref: https://dmalcolm.fedorapeople.org/presentations/cauldron-2017/#1
  // location_t locus;
  
  unsigned int pos;

  // Associated text (if any) of token.
  std::string str;
};

typedef std::unique_ptr<Token> TokenPtr;

#endif
