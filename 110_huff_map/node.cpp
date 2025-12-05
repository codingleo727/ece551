#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    theMap[sym] = b;
    return;
  }

  if (left != NULL) {
    BitString left_bits = b.plusZero();
    left->buildMap(left_bits, theMap);
  }

  if (right != NULL) {
    BitString right_bits = b.plusOne();
    right->buildMap(right_bits, theMap);
  }
}
