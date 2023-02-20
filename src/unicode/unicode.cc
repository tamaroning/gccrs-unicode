#include "table.h"

namespace Unicode {

bool is_xid_start(unsigned int codepoint) {
  // TODO: use binary search
  // just perform linear search for now
  for (auto range : XID_START_TABLE) {
    if (range.first <= codepoint && codepoint <= range.second)
      return true;
  }
  return false;
}

bool is_xid_continue(unsigned int codepoint) {
  // TODO: use binary search
  // just perform linear search for now
  for (auto range : XID_CONTINUE_TABLE) {
    if (range.first <= codepoint && codepoint <= range.second)
      return true;
  }
  return false;
}

} // namespace Unicode