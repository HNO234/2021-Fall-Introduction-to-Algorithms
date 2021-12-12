#include <cassert>
#include <iostream>
using namespace std;

#define RED true
#define BLACK false
#define NIL nullptr

struct rbtree {
private:
  struct node {
    node *p, *left, *right;
    bool color;
    int key;

    node(int z) : p(NIL), left(NIL), right(NIL), color(RED), key(z) {}
  };
  node *root;

  void left_rotate(node *x) {
    node *y = x->right;
    assert(y != NIL);
    x->right = y->left;
    if (y->left != NIL)
      y->left->p = x;
    y->p = x->p;
    if (x->p == NIL)
      root = y;
    else if (x == x->p->left)
      x->p->left = y;
    else
      x->p->right = y;
    y->left = x;
    x->p = y;
  }

  void right_rotate(node *x) {
    node *y = x->left;
    assert(y != NIL);
    x->left = y->right;
    if (y->right != NIL)
      y->right->p = x;
    y->p = x->p;
    if (x->p == NIL)
      root = y;
    else if (x == x->p->right)
      x->p->right = y;
    else
      x->p->left = y;
    y->right = x;
    x->p = y;
  }

  void insert_fixup(node *z) {
    if (z == root) {
      root->color = BLACK;
      return;
    }

    while (z->p != NIL && z->p->color == RED) {
      if (z->p == z->p->p->left) {
        node *y = z->p->p->right;
        if (y != NIL && y->color == RED) { // case 1
          z->p->color = BLACK;
          y->color = BLACK;
          z->p->p->color = RED;
          z = z->p->p;
        } else {
          if (z == z->p->right) { // case 2
            z = z->p;
            left_rotate(z);
          }
          z->p->color = BLACK; // case 3
          z->p->p->color = RED;
          right_rotate(z->p->p);
        }
      } else {
        node *y = z->p->p->left;
        if (y != NIL && y->color == RED) { // case 1
          z->p->color = BLACK;
          y->color = BLACK;
          z->p->p->color = RED;
          z = z->p->p;
        } else {
          if (z == z->p->left) { // case 2
            z = z->p;
            right_rotate(z);
          }
          z->p->color = BLACK; // case 3
          z->p->p->color = RED;
          left_rotate(z->p->p);
        }
      }
    }
    if (root != NIL)
      root->color = BLACK;
  }

public:
  rbtree() : root(NIL) {}

  void insert(int _z) {
    cerr << _z << endl;
    node *y = NIL, *x = root, *z = new node(_z);
    while (x != NIL) {
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    z->p = y;
    if (y == NIL)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
    insert_fixup(z);
  }

  void erase(int z) {}

  void inorder_traversal(node *z = NIL) {
    if (z == NIL)
      z = root;

    if (z->left != NIL)
      inorder_traversal(z->left);

    cout << "key: " << z->key << " ";
    if (z->p == NIL)
      cout << "parent:   ";
    else
      cout << "parent: " << z->p->key << " ";
    cout << "color: " << (z->color == RED ? "red" : "black") << endl;

    if (z->right != NIL)
      inorder_traversal(z->right);
  }
};

int main() {
  rbtree s;
  int x;
  while (cin >> x) {
    s.insert(x);
  }
  s.inorder_traversal();
}
