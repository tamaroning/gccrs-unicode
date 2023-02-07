#include <memory>

enum TokenId {
  Ident,
  IntLit,
};

class Token {
private:
  // Token kind.
  TokenId token_id;
  // Token location.
  // ref: https://dmalcolm.fedorapeople.org/presentations/cauldron-2017/#1
  // location_t locus;
  // Associated text (if any) of token.
  std::unique_ptr<std::string> str;
};