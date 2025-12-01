#ifndef BSTSET_H
#define BSTSET_H

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;

    Node(const T & key_) : key(key_), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) { root = copy_tree(rhs.root); }

  Node * copy_tree(const Node * rhs_root) {
    if (rhs_root == NULL) {
      return NULL;
    }

    Node * node = new Node(rhs_root->key);
    node->left = copy_tree(rhs_root->left);
    node->right = copy_tree(rhs_root->right);

    return node;
  }

  const BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy_tree(rhs.root);
    }
    return *this;
  }

  virtual ~BstSet<T>() { destroy(root); }

  void destroy(Node * root) {
    if (root == NULL) {
      return;
    }

    destroy(root->left);
    destroy(root->right);
    delete root;
  }

  virtual void add(const T & key) { root = add_node(root, key); }

  Node * add_node(Node * root, const T & key) {
    if (root == NULL) {
      return new Node(key);
    }
    if (key < root->key) {
      root->left = add_node(root->left, key);
    }
    else if (key > root->key) {
      root->right = add_node(root->right, key);
    }

    return root;
  }

  virtual bool contains(const T & key) const { return contains_node(root, key); }

  bool contains_node(Node * root, const T & key) const {
    if (root == NULL) {
      return false;
    }
    if (key < root->key) {
      return contains_node(root->left, key);
    }
    else if (key > root->key) {
      return contains_node(root->right, key);
    }
    else {
      return true;
    }
  }

  virtual void remove(const T & key) { root = remove_node(root, key); }

  Node * remove_node(Node * root, const T & key) {
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
};

#endif
