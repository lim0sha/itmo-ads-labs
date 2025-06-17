#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
  int data_;
  Node *left_;
  Node *right_;
  int height_;
};

Node *find_prevoius(Node *root, int val) {
  Node *cur = root;
  Node *tmp{};
  while (cur != nullptr) {
    if (cur->data_ < val) {
      tmp = cur;
      cur = cur->right_;
    } else {
      cur = cur->left_;
    }
  }
  return tmp;
}

int AVL_getheight(Node *h) {
  return (h == nullptr) ? 0 : h->height_;
}

Node *get_minimum(Node *root) {
  return (root->left_ == nullptr) ? root : get_minimum(root->left_);
}

Node *get_maximum(Node *root) {
  return (root->right_ == nullptr) ? root : get_maximum(root->right_);
}

Node *litte_rotate_right(Node *root) {
  Node *root2 = root->left_;
  root->left_ = root2->right_;
  root2->right_ = root;
  root->height_ = max(AVL_getheight(root->left_), AVL_getheight(root->right_)) + 1;
  root2->height_ = max(AVL_getheight(root2->left_), AVL_getheight(root2->right_)) + 1;
  return root2;
}

Node *litte_rotate_left(Node *root) {
  Node *root2 = root->right_;
  root->right_ = root2->left_;
  root2->left_ = root;
  root->height_ = max(AVL_getheight(root->left_), AVL_getheight(root->right_)) + 1;
  root2->height_ = max(AVL_getheight(root2->left_), AVL_getheight(root2->right_)) + 1;
  return root2;
}

int balance_nodes(Node *h) {
  if (h == nullptr) {
    return 0;
  } else if (h->right_ != nullptr and h->left_ == nullptr) {
    return AVL_getheight(h->right_);
  } else if (h->right_ == nullptr and h->left_ != nullptr) {
    return 0 - AVL_getheight(h->left_);
  } else {
    return AVL_getheight(h->right_) - AVL_getheight(h->left_);
  }
}

void AVL_fix_heights(Node *root) {
  int hl = AVL_getheight(root->left_);
  int hr = AVL_getheight(root->right_);
  root->height_ = max(hl, hr) + 1;
}

Node *make_new_balance(Node *root) {
  AVL_fix_heights(root);
  int balance = balance_nodes(root);
  if (balance > 1) {
    if (balance_nodes(root->right_) < 0)
      root->right_ = litte_rotate_right(root->right_);
    return litte_rotate_left(root);
  }
  if (balance < -1) {
    if (balance_nodes(root->left_) > 0)
      root->left_ = litte_rotate_left(root->left_);
    return litte_rotate_right(root);
  }
  return root;
}

Node *insert(Node *root, int val) {
  if (root == nullptr) {
    root = new Node{val, nullptr, nullptr, 1};
  } else if (val < root->data_) {
    root->left_ = insert(root->left_, val);
  } else if (val > root->data_) {
    root->right_ = insert(root->right_, val);
  }
  return make_new_balance(root);
}

Node *removal(Node *root, int val) {
  if (root == nullptr) {
    return root;
  }
  if (val < root->data_) {
    root->left_ = removal(root->left_, val);
  } else if (val > root->data_) {
    root->right_ = removal(root->right_, val);
  } else if (root->left_ != nullptr and root->right_ != nullptr) {
    root->data_ = find_prevoius(root->left_, val)->data_;
    root->left_ = removal(root->left_, root->data_);
  } else if (root->left_ != nullptr or root->right_ != nullptr) {
    if (root->right_ != nullptr) {
      root = root->right_;
      return make_new_balance(root);
    } else if (root->left_ != nullptr) {
      root = root->left_;
      return make_new_balance(root);
    }
  } else if (root->right_ == nullptr or root->left_ == nullptr) {
    return nullptr;
  }
  return make_new_balance(root);
}

bool peek(Node *root, int val) {
  while (root != nullptr) {
    if (val == root->data_) {
      return true;
    } else if (val < root->data_) {
      root = root->left_;
    } else {
      root = root->right_;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Node *tree{};
  string operation;
  size_t value;
  size_t N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> operation;
    if (operation == "A") {
      cin >> value;
      if (!peek(tree, value)) {
        tree = insert(tree, value);
        cout << balance_nodes(tree);
        cout << '\n';
      } else {
        cout << balance_nodes(tree);
        cout << '\n';
      }
    } else if (operation == "D") {
      cin >> value;
      if (peek(tree, value)) {
        tree = removal(tree, value);
      }
      if (tree == nullptr) {
        cout << 0;
        cout << '\n';
      } else {
        cout << balance_nodes(tree);
        cout << '\n';
      }
    } else if (operation == "C") {
      cin >> value;
      if (peek(tree, value)) {
        cout << 'Y';
        cout << '\n';
      } else {
        cout << 'N';
        cout << '\n';
      }
    }
  }
  return 0;
}
