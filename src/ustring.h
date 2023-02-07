#ifndef USTRING_H
#define USTRING_H

#include <iostream>
#include <iterator>
#include <memory>

class Codepoint {
public:
  uint32_t value;

  Codepoint() : value(0) {}

  Codepoint(uint32_t value) : value(value) {}

  static Codepoint eof() { return Codepoint(UINT32_MAX); }
  bool is_eof() const { return value == UINT32_MAX; }

  std::string to_string() {
    std::string str;
    if (value < 0x80) {
      str += static_cast<char>(value);
    } else if (value < (0x1F + 1) << (1 * 6)) {
      str += static_cast<char>(0xC0 | ((value >> 6) & 0x1F));
      str += static_cast<char>(0x80 | ((value >> 0) & 0x3F));
    } else if (value < (0x0F + 1) << (2 * 6)) {
      str += static_cast<char>(0xE0 | ((value >> 12) & 0x0F));
      str += static_cast<char>(0x80 | ((value >> 6) & 0x3F));
      str += static_cast<char>(0x80 | ((value >> 0) & 0x3F));
    } else if (value < (0x07 + 1) << (3 * 6)) {
      str += static_cast<char>(0xF0 | ((value >> 18) & 0x07));
      str += static_cast<char>(0x80 | ((value >> 12) & 0x3F));
      str += static_cast<char>(0x80 | ((value >> 6) & 0x3F));
      str += static_cast<char>(0x80 | ((value >> 0) & 0x3F));
    } else {
      // invalid code point
      return std::string({static_cast<char>(0xEF), static_cast<char>(0xBF),
                          static_cast<char>(0xBD)});
    }
    return str;
  }

  bool operator==(Codepoint other) const { return value == other.value; }
  bool operator!=(Codepoint other) const { return !operator==(other); }
};

class UString;

class UStringIterator : public std::iterator<std::forward_iterator_tag, int> {
  friend UString;
  const size_t END_M_INDEX = SIZE_MAX;
  const std::nullptr_t END_M_USTRING = nullptr;
public:
  // ++iter
  UStringIterator &operator++();

  // iter++
  UStringIterator operator++(int);

  bool operator==(const UStringIterator &iterator);

  bool operator!=(const UStringIterator &iterator);

  char operator*();

private:
  // current index of bytes
  size_t m_index;
  UString *m_ustring;

  // end of iterator
  UStringIterator() : m_index(END_M_INDEX), m_ustring(END_M_USTRING){};

  UStringIterator(UString *ustring, int index)
      : m_ustring(ustring), m_index(index == 0 ? index : SIZE_MAX){};
};

class UString {
public:
  typedef UStringIterator iterator;

  UString(std::string str) : s(str) {}

  std::string to_string() const { return s; }

  size_t length() const {
    return s.length(); // TODO:
  }

  iterator begin() { return iterator(this, 0); }

  iterator end() { return iterator(); }

private:
  std::string s;
};

std::ostream &operator<<(std::ostream &os, const UString &us);

#endif