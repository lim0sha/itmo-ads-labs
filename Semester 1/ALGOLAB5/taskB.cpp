#include <iostream>
using namespace std;

struct Node {
  int age;
  Node *left;
  Node *right;

  Node(int value) : age(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
 private:
  Node *root;

  Node *insertRec(Node *root, int age) {
    if (root == nullptr) {
      return new Node(age);
    }

    if (age < root->age) {
      root->left = insertRec(root->left, age);
    } else if (age > root->age) {
      root->right = insertRec(root->right, age);
    }

    return root;
  }

  Node *deleteRec(Node *root, int age) {
    if (root == nullptr) {
      return root;
    }

    if (age < root->age) {
      root->left = deleteRec(root->left, age);
    } else if (age > root->age) {
      root->right = deleteRec(root->right, age);
    } else if (root->left != nullptr && root->right != nullptr) {
      root->age = findMin(root->right)->age;
      root->right = deleteRec(root->right, root->age);
    } else {
      if (root->left != nullptr) {
        root = root->left;
      } else if (root->right != nullptr) {
        root = root->right;
      } else {
        root = nullptr;
      }
    }
    return root;
  }

  bool existsRec(Node *root, int age) const {
    if (root == nullptr) {
      return false;
    }

    if (age < root->age) {
      return existsRec(root->left, age);
    } else if (age > root->age) {
      return existsRec(root->right, age);
    }

    return true;
  }

  Node *findMin(Node *root) const {
    while (root->left != nullptr) {
      root = root->left;
    }
    return root;
  }

  Node *findMax(Node *root) const {
    while (root->right != nullptr) {
      root = root->right;
    }
    return root;
  }

  Node *findNext(Node *root, int age) const {
    Node *successor = nullptr;
    while (root != nullptr) {
      if (age < root->age) {
        successor = root;
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return successor;
  }

  Node *findPrev(Node *root, int age) const {
    Node *predecessor = nullptr;
    while (root != nullptr) {
      if (age > root->age) {
        predecessor = root;
        root = root->right;
      } else {
        root = root->left;
      }
    }
    return predecessor;
  }

 public:
  BinarySearchTree() : root(nullptr) {}

  void insert(int age) {
    root = insertRec(root, age);
  }

  void remove(int age) {
    root = deleteRec(root, age);
  }

  bool exists(int age) const {
    return existsRec(root, age);
  }

  auto next(int age) -> std::string {
    Node* successor = findNext(root, age);
    return successor != nullptr ? std::to_string(successor->age) + "\n" : "none\n";
  }

  auto prev(int age)-> std::string {
    Node* predecessor = findPrev(root, age);
    return predecessor != nullptr ? std::to_string(predecessor->age) + "\n" : "none\n";
  }
};

int main() {
  BinarySearchTree bst;

  string purpose;
  int x;

  while (cin >> purpose >> x) {
    if (purpose == "insert") {
      bst.insert(x);
    } else if (purpose == "delete") {
      bst.remove(x);
    } else if (purpose == "exists") {
      cout << (bst.exists(x) ? "true" : "false") << "\n";
    } else if (purpose == "next") {
      auto result = bst.next(x);
      cout << (result != "-1" ? result : "none");
    } else if (purpose == "prev") {
      auto result = bst.prev(x);
      cout << (result != "-1" ? result : "none");
    }
  }

  return 0;
}
