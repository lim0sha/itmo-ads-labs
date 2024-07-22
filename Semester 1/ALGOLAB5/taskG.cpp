#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  long long data_, total, data_minimum_, data_maximum_;
  bool is_BST_;
  long long left_, right_, parent_;

  TreeNode() = default;


  explicit TreeNode(int x) : data_(x), total(0), data_minimum_(0), data_maximum_(0), is_BST_(false), left_(-1), right_(-1), parent_(-1) {}
};

void make_new_node(vector<TreeNode> &tree_nodes, int index) {
  tree_nodes[index].data_minimum_ = tree_nodes[index].data_;
  tree_nodes[index].data_maximum_ = tree_nodes[index].data_;
  tree_nodes[index].is_BST_ = true;
  tree_nodes[index].total = tree_nodes[index].data_;
}

bool isLeaf(const vector<TreeNode> &nodes, int i) {
  if (nodes[i].left_ == -1 and nodes[i].right_ == -1) {
    return true;
  }
  return false;
}

void postOrder(vector<TreeNode> &tree_nodes, int k, long long &total) {
  if (k == -1 or tree_nodes[k].is_BST_) {
    return;
  }

  postOrder(tree_nodes, tree_nodes[k].left_, total);
  postOrder(tree_nodes, tree_nodes[k].right_, total);

  if (isLeaf(tree_nodes, k)) {
    total = max(total, tree_nodes[k].data_);
    make_new_node(tree_nodes, k);
  } else if (tree_nodes[k].left_ != -1 and tree_nodes[k].right_ != -1) {
    if (tree_nodes[tree_nodes[k].left_].data_maximum_ < tree_nodes[k].data_ and tree_nodes[k].data_ < tree_nodes[tree_nodes[k].right_].data_minimum_
        and tree_nodes[tree_nodes[k].left_].data_ < tree_nodes[k].data_ and tree_nodes[k].data_ < tree_nodes[tree_nodes[k].right_].data_
        and tree_nodes[tree_nodes[k].left_].is_BST_ and tree_nodes[tree_nodes[k].right_].is_BST_) {
      tree_nodes[k].is_BST_ = true;
      tree_nodes[k].data_minimum_ = min(tree_nodes[tree_nodes[k].left_].data_minimum_, tree_nodes[k].data_);
      tree_nodes[k].data_maximum_ = max(tree_nodes[tree_nodes[k].right_].data_maximum_, tree_nodes[k].data_);
      tree_nodes[k].total = tree_nodes[tree_nodes[k].left_].total + tree_nodes[tree_nodes[k].right_].total + tree_nodes[k].data_;
      total = max(total, tree_nodes[k].total);
    }
  } else if (tree_nodes[k].left_ != -1) {
    if (tree_nodes[tree_nodes[k].left_].data_maximum_ < tree_nodes[k].data_ and tree_nodes[tree_nodes[k].left_].data_ < tree_nodes[k].data_
        and tree_nodes[tree_nodes[k].left_].is_BST_) {
      tree_nodes[k].is_BST_ = true;
      tree_nodes[k].data_minimum_ = min(tree_nodes[tree_nodes[k].left_].data_minimum_, tree_nodes[k].data_);
      tree_nodes[k].data_maximum_ = max(tree_nodes[tree_nodes[k].left_].data_maximum_, tree_nodes[k].data_);
      tree_nodes[k].total = tree_nodes[tree_nodes[k].left_].total + tree_nodes[k].data_;
      total = max(total, tree_nodes[k].total);
    }
  } else if (tree_nodes[k].right_ != -1) {
    if (tree_nodes[tree_nodes[k].right_].data_minimum_ > tree_nodes[k].data_ and tree_nodes[tree_nodes[k].right_].data_ > tree_nodes[k].data_
        and tree_nodes[tree_nodes[k].right_].is_BST_) {
      tree_nodes[k].is_BST_ = true;
      tree_nodes[k].data_minimum_ = min(tree_nodes[tree_nodes[k].right_].data_minimum_, tree_nodes[k].data_);
      tree_nodes[k].data_maximum_ = max(tree_nodes[tree_nodes[k].right_].data_maximum_, tree_nodes[k].data_);
      tree_nodes[k].total = tree_nodes[tree_nodes[k].right_].total + tree_nodes[k].data_;
      total = max(total, tree_nodes[k].total);
    }
  }


}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N;
  string operation;
  cin >> N;
  vector<TreeNode> nodes(1, TreeNode(N));
  int cur = 0;

  while (cin >> operation) {
    if (operation == "l" or operation == "r") {
      cin >> N;
      nodes.emplace_back(N);
      if (operation == "l") {
        nodes[cur].left_ = nodes.size() - 1;
      } else {
        nodes[cur].right_ = nodes.size() - 1;
      }
      nodes[nodes.size() - 1].parent_ = cur;
      cur = nodes.size() - 1;
    } else {
      if (nodes[cur].parent_ != -1) {
        cur = nodes[cur].parent_;
      }
    }
  }
  long long total = 0;
  postOrder(nodes, 0, total);
  cout << total;
  return 0;
}
