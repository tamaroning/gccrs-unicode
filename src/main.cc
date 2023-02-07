#include "ustring.h"
#include <iostream>
#include <typeinfo>
#include "ustring.h"


int main(void) {
  std::string s = "helloこんにちは";
  UString us = UString("helloこんにちは");

  // auto a = "a";

  // std::cout << typeid(a).name() << std::endl;

  std::cout << s << std::endl;
  std::cout << s.length() << std::endl;

  std::cout << us << std::endl;
  std::cout << us.length() << std::endl;

  for (auto c: s) {
    std::cout << c;
  }
  std::cout << std::endl << *us.begin() << std::endl;

  for (auto it = us.begin(); it != us.end(); it++) {
    std::cout << *it;
  }
  std::cout << std::endl;

  for (auto c: us) {
    std::cout << c;
  }
  std::cout << std::endl;

  return 0;
}