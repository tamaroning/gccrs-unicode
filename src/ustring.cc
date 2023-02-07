#include "ustring.h"
#include <fstream>

// ++iter
UString::iterator &UString::iterator::operator++() {
  if (m_ustring == nullptr)
    return *this;
  m_index++;
  if (m_index > m_ustring->length()) {
    m_ustring = END_M_USTRING;
    m_index = END_M_INDEX;
  }
  return *this;
}

// iter++
UString::iterator UString::iterator::operator++(int) {
  if (m_ustring == nullptr)
    return *this;
  UStringIterator result = *this;
  m_index++;
  if (m_index > m_ustring->length()) {
    m_ustring = END_M_USTRING;
    m_index = END_M_INDEX;
  }
  return result;
};

bool UString::iterator::operator!=(const UString::iterator &iterator) {
  return this->m_ustring != iterator.m_ustring ||
         this->m_index != iterator.m_index;
}

bool UString::iterator::operator==(const UString::iterator &iterator) {
  return !(*this != iterator);
}

char UString::iterator::operator*() { return m_ustring->to_string()[m_index]; }

std::ostream &operator<<(std::ostream &os, const UString &us) {
  os << us.to_string();
  return os;
}
