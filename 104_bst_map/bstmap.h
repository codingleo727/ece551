#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key_, const V & value_) :
        key(key_), value(value_), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(NULL) { root = copy_tree(rhs.root); }

  virtual ~BstMap<K, V>() { destroy(root); }

  Node * copy_tree(const Node * rhs_root) {
    if (rhs_root == NULL) {
      return NULL;
    }

    Node * node = new Node(rhs_root->key, rhs_root->value);
    node->left = copy_tree(rhs_root->left);
    node->right = copy_tree(rhs_root->right);

    return node;
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy_tree(rhs.root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) { root = add_node(root, key, value); }

  Node * add_node(Node * root, const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      if (key < root->key) {
        root->left = add_node(root->left, key, value);
      }
      else if (key > root->key) {
        root->right = add_node(root->right, key, value);
      }
      else {
        root->value = value;
      }
    }
    return root;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookup_node(root, key);
  }

  const V & lookup_node(Node * root, const K & key) const throw(std::invalid_argument) {
    if (root == NULL) {
      throw std::invalid_argument("Key not found in map");
    }

    if (key == root->key) {
      return root->value;
    }
    else if (key < root->key) {
      return lookup_node(root->left, key);
    }
    else {
      return lookup_node(root->right, key);
    }
  }

  virtual void remove(const K & key) { root = remove_node(root, key); }

  Node * remove_node(Node * root, const K & key) {
    if (root == NULL) {
      return NULL;
    }

    if (key < root->key) {
      root->left = remove_node(root->left, key);
      return root;
    }
    else if (key > root->key) {
      root->right = remove_node(root->right, key);
      return root;
    }
    else {
      if (root->left == NULL && root->right == NULL) {
        delete root;
        return NULL;
      }
      else if (root->right == NULL) {
        Node * child = root->left;
        delete root;
        return child;
      }
      else if (root->left == NULL) {
        Node * child = root->right;
        delete root;
        return child;
      }
      else {
        Node * succ = min(root->right);
        root->key = succ->key;
        root->value = succ->value;
        root->right = remove_node(root->right, succ->key);
        return root;
      }
    }
  }

  Node * min(Node * root) {
    Node * curr = root;
    while (curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }

  void destroy(Node * root) {
    if (root == NULL) {
      return;
    }

    if (root != NULL) {
      destroy(root->left);
      destroy(root->right);
      delete root;
    }
  }
};

#endif
