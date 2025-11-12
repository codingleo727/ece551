#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <algorithm>

//YOUR CODE GOES HERE
class out_of_index_error : public std::exception {
public:
  virtual const char * what() const throw() {
    return "Index out of bounds";
  }
};

template<typename T>
class LinkedList {
private:
  class Node {
  public:
    T data;
    Node * next;
    Node * prev;
    Node(): data(), next(NULL), prev(NULL) {}
  };

  Node * head;
  Node * tail;
  int size;

  void swap(LinkedList<T> & other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }

  Node * nodeAt(int index) const {
    if (index < 0 || index >= size) {
      throw out_of_index_error();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr; 
  }
public:
  LinkedList(): head(NULL), tail(NULL), size(0) {}
  
  LinkedList(const LinkedList<T> & li): head(NULL), tail(NULL), size(0) {
    Node * copy_curr = li.head;
    while (copy_curr != NULL) {
      addBack(copy_curr->data);
    }
  }

  LinkedList & operator=(LinkedList<T> li) {
    swap(li);
    return *this;
  }
  
  ~LinkedList() {
    Node * curr = tail;
    while (curr != NULL) {
      Node * temp = curr;
      curr = curr->prev;
      delete temp;
    }
  }

  void addFront(const T & item) {
    Node * new_head = new Node();
    new_head->data = item;
    new_head->prev = NULL;
    if (head == NULL) {
      new_head->next = NULL;
      tail = new_head;
    } 
    else {
      new_head->next = head;
      head->prev = new_head; 
    }
    head = new_head;
    size++;
  }

  void addBack(const T & item) {
    Node * new_tail = new Node();
    new_tail->data = item;
    new_tail->next = NULL;
    if (tail == NULL) {
      new_tail->prev = NULL;
      head = new_tail;
    } 
    else {
      new_tail->prev = tail;
      tail->next = new_tail;
    }
    tail = new_tail;
    size++;
  }

  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        // Check if it is head or tail
        if (curr == head && curr == tail) {
          head = NULL;
          tail = NULL;
        }
        else if (curr == head) {
          head = curr->next;
          head->prev = NULL;
        }
        else if (curr == tail) {
          tail = curr->prev;
          tail->next = NULL;
        }
        else {
          curr->next->prev = curr->prev;
          curr->prev->next = curr->next;
        }
        delete curr;
        size--;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }
  
  T & operator[](int index) {
    return nodeAt(index)->data;
  }

  const T & operator[](int index) const {
    return nodeAt(index)->data; 
  }

  int find(const T & item) const {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;
  }

  int getSize() const {
    return size;
  }
};

#endif
