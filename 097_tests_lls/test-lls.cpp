#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFrontBack() {
    IntList il;
    il.addFront(1); // 1
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head == il.tail);
    assert(il.head->data == 1);

    il.addFront(0); // 0 1
    assert(il.head->data == 0);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 0);
    assert(il.tail->prev->next == il.tail);

    il.addBack(2); // 0 1 2
    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 3);
  }
  
  void testRuleOfThree() {
    IntList a;
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);

    IntList b(a);
    assert(b.getSize() == 3);
    assert(b.head != a.head);
    assert(b.tail != a.tail);
    assert(b.head->data == 1);
    assert(b.tail->data == 3);

    a.addBack(4);
    assert(a.getSize() == 4);
    assert(b.getSize() == 3);

    IntList c;
    c.addBack(5);
    c = a;
    assert(c.getSize() == 4);
    assert(c.head != a.head);
    assert(c.tail->data == 4);
  }

  void testRemove() {
    IntList il;
    il.addBack(1); // 1
    il.addBack(2); // 1 2
    il.addBack(3); // 1 2 3
    il.addBack(4); // 1 2 3 4
    il.addBack(5); // 1 2 3 4 5

    assert(il.remove(1) == true); // 2 3 4 5
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);

    assert(il.remove(5) == true); // 2 3 4
    assert(il.tail->data == 4);
    assert(il.tail->next == NULL);

    assert(il.remove(3) == true); // 2 4
    assert(il.head->next->data == 4);
    assert(il.head->next->prev->data == 2);

    assert(il.remove(2) == true); // 4
    assert(il.remove(4) == true); // empty
    assert(il.head == NULL && il.tail == NULL);
    assert(il.getSize() == 0);

    assert(il.remove(0) == false);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFrontBack();
  t.testRuleOfThree();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
