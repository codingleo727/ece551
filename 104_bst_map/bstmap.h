#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  struct Node {
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key_, const V & value_) :
        key(key_), value(value_), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  virtual void add(const K & key, const V & value) { root = add(root, key, value); }

  Node * add(Node * root, const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      if (key < root->key) {
        root->left = add(root->left, key, value);
      }
      else if (key > root->key) {
        root->right = add(root->right, key, value);
      }
      else {
        root->key = key;
        root->value = value;
      }
    }
    return root;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookup(root, key);
  }

  const V & lookup(Node * root, const K & key) const {
    if (root == NULL) {
      throw std::invalid_argument("Key not found in map");
    }

    if (key == root->key) {
      return root->value;
    }
    else {
      if (key < root->key) {
        return lookup(root->left, key);
      }
      else {
        return lookup(root->right, key);
      }
    }
  }

  virtual void remove(const K & key) { root = remove(root, key); }

  Node * remove(Node * root, const K & key) {
    if (root == NULL) {
      return root;
    }

    if (key == root->key) {
      if (root->left == NULL && root->right == NULL) {
        delete root;
      }
      else if (root->right == NULL) {
        Node * temp = root;
        root = root->left;
        delete temp;
      }
      else if (root->left == NULL) {
        Node * temp = root;
        root = root->right;
        delete temp;
      }
      else {
        Node * succ = min(root);
        root->key = succ->key;
        root->value = succ->value;
        root->right = remove(root->right, succ->key);
      }
    }
    else {
      if (key < root->key) {
        root->left = remove(root->left, key);
      }
      else {
        root->right = remove(root->right, key);
      }
    }
    return root;
  }

  Node * min(Node * root) {
    if (root->left == NULL) {
      return root;
    }
    else {
      return min(root->left);
    }
  }

  virtual ~BstMap<K, V>() { destroy(root); }

  void destroy(Node * root) {
    if (root != NULL) {
      destroy(root->left);
      destroy(root->right);
      delete root;
    }
  }
};

#endif
