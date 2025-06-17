#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct AVLNode {
  int value;
  int left;
  int right;
  int height;
  int balance;

  AVLNode(int val) : value(val), left(0), right(0), height(1), balance(0) {}
};

void get_height(vector<AVLNode>& tree, AVLNode& node) {
  int l_height = (node.left != 0) ? tree[node.left - 1].height : 0;
  int r_height = (node.right != 0) ? tree[node.right - 1].height : 0;

  node.height = max(l_height, r_height) + 1;
  node.balance = r_height - l_height;
}

void postorder_balance_check(vector<AVLNode>& tree, AVLNode& node) {
  if (node.left != 0) {
    postorder_balance_check(tree, tree[node.left - 1]);
  }
  if (node.right != 0) {
    postorder_balance_check(tree, tree[node.right - 1]);
  }
  if (node.left != node.right) {
    get_height(tree, node);
  }
}

int main() {
  int n;
  cin >> n;
  vector<AVLNode> tree(n, AVLNode(0));
  for (int i = 0; i < n; ++i) {
    int value;
    cin >> value >> tree[i].left >> tree[i].right;
    tree[i].value = value;
  }

  postorder_balance_check(tree, tree[0]);
  for (int i = 0; i < n; ++i) {
    cout << tree[i].balance << "\n";
  }
  return 0;
}
