#include <cassert>
#include <iostream>
#include <vector>

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

  void recursive_delete(node *z) {
    if (z == NIL)
      return;
    if (z->left != NIL)
      recursive_delete(z->left);
    if (z->right != NIL)
      recursive_delete(z->right);
    delete z;
  }

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

  void transplant(node *u, node *v) {
    if (u->p == NIL)
      root = v;
    else if (u == u->p->left)
      u->p->left = v;
    else
      u->p->right = v;
    if (v != NIL)
      v->p = u->p;
  }

  node *tree_search(int x) {
    node *y = root;
    while (y != NIL) {
      if (y->key == x)
        break;
      else if (y->key > x)
        y = y->left;
      else
        y = y->right;
    }
    return y;
  }

  node *tree_minimum(node *x) {
    while (x->left != NIL)
      x = x->left;
    return x;
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

  void delete_fixup(node *x, node *xp) {
    assert(x == NIL || x->p == xp);
    while (x != root && (x == NIL || x->color == BLACK)) {
      if (x == xp->left) {
        node *w = xp->right; // w != NIL
        if (w->color == RED) {
          w->color = BLACK;
          xp->color = RED;
          left_rotate(xp);
          w = xp->right;
        }
        if ((w->left == NIL || w->left->color == BLACK) &&
            (w->right == NIL || w->right->color == BLACK)) {
          w->color = RED;
          x = xp;
          xp = x->p;
        } else {
          if (w->right == NIL || w->right->color == BLACK) {
            if (w->left != NIL)
              w->left->color = BLACK;
            w->color = RED;
            right_rotate(w);
            w = xp->right;
          }
          w->color = xp->color;
          xp->color = BLACK;
          if (w->right != NIL)
            w->right->color = BLACK;
          left_rotate(xp);
          x = root;
          xp = NIL;
        }
      } else {
        node *w = xp->left; // w != NIL
        if (w->color == RED) {
          w->color = BLACK;
          xp->color = RED;
          right_rotate(xp);
          w = xp->left;
        }
        if ((w->left == NIL || w->left->color == BLACK) &&
            (w->right == NIL || w->right->color == BLACK)) {
          w->color = RED;
          x = xp;
          xp = x->p;
        } else {
          if (w->left == NIL || w->left->color == BLACK) {
            if (w->right != NIL)
              w->right->color = BLACK;
            w->color = RED;
            left_rotate(w);
            w = xp->left;
          }
          w->color = xp->color;
          xp->color = BLACK;
          if (w->left != NIL)
            w->left->color = BLACK;
          right_rotate(xp);
          x = root;
        }
      }
    }
    if (x != NIL)
      x->color = BLACK;
  }

public:
  rbtree() : root(NIL) {}

  ~rbtree() { recursive_delete(root); }

  void insert(int _z) {
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

  void erase(int _z) {
    node *z = tree_search(_z), *y = z, *x, *xp;
    assert(z != NIL && z->key == _z);
    bool y_ori_color = y->color;
    if (z->left == NIL) {
      x = z->right;
      xp = z->p;
      transplant(z, z->right);
    } else if (z->right == NIL) {
      x = z->left;
      xp = z->p;
      transplant(z, z->left);
    } else {
      y = tree_minimum(z->right);
      if (y->p == z)
        xp = y;
      else
        xp = y->p;
      y_ori_color = y->color;
      x = y->right;
      if (y->p == z && x != NIL)
        x->p = y;
      else {
        transplant(y, y->right);
        y->right = z->right;
        if (y->right != NIL)
          y->right->p = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->p = y;
      y->color = z->color;
    }
    delete z;
    if (y_ori_color == BLACK)
      delete_fixup(x, xp);
  }

  void inorder_traversal(node *z = NIL) {
    if (z == NIL)
      z = root;
    if (root == NIL)
      return;

    if (z->left != NIL)
      inorder_traversal(z->left);

    std::cout << "key: " << z->key << " ";
    if (z->p == NIL)
      std::cout << "parent:   ";
    else
      std::cout << "parent: " << z->p->key << " ";
    std::cout << "color: " << (z->color == RED ? "red" : "black") << std::endl;

    if (z->right != NIL)
      inorder_traversal(z->right);
  }
};

int main() {
  rbtree tree;
  int t;
  std::cin >> t;
  while (t--) {
    int op, n;
    std::cin >> op >> n;
    std::vector<int> a(n);
    for (int &i : a)
      std::cin >> i;
    if (op == 1)
      std::cout << "Insert:";
    else
      std::cout << "Delete:";
    for (int i = 0; i < n; i++) {
      std::cout << ' ' << a[i];
      if (i < n - 1)
        std::cout << ',';
    }
    std::cout << std::endl;

    if (op == 1)
      for (int i : a)
        tree.insert(i);
    else
      for (int i : a)
        tree.erase(i);
    tree.inorder_traversal();
  }
}
