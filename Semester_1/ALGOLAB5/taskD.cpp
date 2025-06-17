#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int value;
  Node* left;
  Node* right;
};

Node* insert_in_tree(Node* root, int value) {
  if (root == nullptr) {
    return new Node(value);
  }

  if (value < root->value) {
    root->left = insert_in_tree(root->left, value);
  } else if (value > root->value) {
    root->right = insert_in_tree(root->right, value);
  }

  return root;
}

vector<int> rightest_on_every_tree_level(Node* root) {
  vector<int> result;
  if (root == NULL) {
    return result;
  }
  queue<Node*> tree_stage_queue;
  tree_stage_queue.push(root);

  while (!(tree_stage_queue.size() == 0)) {
    int levelSize = tree_stage_queue.size();
    Node* rightmost = NULL;

    for (int i = 0; i < levelSize; ++i) {
      Node* current = tree_stage_queue.front();
      tree_stage_queue.pop();

      rightmost = current;

      if (current->left != NULL) {
        tree_stage_queue.push(current->left);
      }
      if (current->right != NULL) {
        tree_stage_queue.push(current->right);
      }
    }

    result.push_back(rightmost->value);
  }

  return result;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  Node* root = NULL;
  for (int i = 0; i < N; ++i) {
    int value;
    cin >> value;
    root = insert_in_tree(root, value);
  }
  vector<int> result = rightest_on_every_tree_level(root);
  for (int value : result) {
    cout << value << ' ';
  }
  return 0;
}
