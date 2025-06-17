#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
  int value;
  Node *left;
  Node *right;
  int size; // размер поддерева с корнем в данной вершине

  Node(int val) : value(val), left(nullptr), right(nullptr), size(1) {}
};

class BinarySearchTree {
 public:
  BinarySearchTree() : root(nullptr) {}

  void insert(int key) {
    root = insertRec(root, key);
  }

  void remove(int key) {
    root = removeRec(root, key);
  }

  int findKthMax(int k) {
    return kthMaxRec(root, k);
  }

 private:
  Node *root;

  // добавление эл-та по значению на нужное место
  Node *insertRec(Node *root, int key) {
    if (root == nullptr) {
      return new Node(key);
    }
    if (key < root->value) {
      root->left = insertRec(root->left, key);
    } else {
      root->right = insertRec(root->right, key);
    }
    root->size++;
    return root;
  }

  // удаление по значению
  Node *removeRec(Node *root, int key) {
    if (root == nullptr) {
      return root;
    }
    if (key < root->value) {
      root->left = removeRec(root->left, key);
    } else if (key > root->value) {
      root->right = removeRec(root->right, key);
    } else {
      if (root->left == nullptr) {
        Node *temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node *temp = root->left;
        delete root;
        return temp;
      }
      Node *temp = minValueNode(root->right);
      root->value = temp->value;
      root->right = removeRec(root->right, temp->value);
    }
    root->size--;
    return root;
  }

  Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // k - порядковая в дереве
  int kthMaxRec(Node *root, int k) {
    if (root == nullptr || k > root->size) {
      return -1; // В дереве меньше k элементов
    }
    int rightSize = (root->right) ? root->right->size : 0;
    if (k == rightSize + 1) {
      return root->value;
    } else if (k <= rightSize) {
      return kthMaxRec(root->right, k);
    } else {
      return kthMaxRec(root->left, k - rightSize - 1);
    }
  }
};

int main() {
  long long n;
  BinarySearchTree apples;
  cin >> n;
  int command, k;
  for (int i = 0; i < n; ++i) {
    cin >> command >> k;
    if (command == 1) {
      apples.insert(k);
    }
    if (command == 0) {
      cout << apples.findKthMax(k) << "\n";
    }
    if (command == -1) {
      apples.remove(k);
    }
  }
  return 0;
}
