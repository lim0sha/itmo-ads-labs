#include <iostream>

using namespace std;

struct TreeNode {
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
};

const int MAX_SIZE = 1000000;

TreeNode *minimumsrch(TreeNode *node_2_find) {
  while (node_2_find->left != NULL) {
    node_2_find = node_2_find->left;
  }
  return node_2_find;
}

TreeNode *linaersrch(TreeNode *node, long key) {
  while (node != nullptr and key != node->data) {
    node = (key < node->data) ? node->left : node->right;
  }
  return node;
}

TreeNode *ins(TreeNode *node, long new_value) {
  if (linaersrch(node, new_value) != nullptr) {
    return node;
  }
  if (node == nullptr) {
    return new TreeNode(new_value);
  }
  if (new_value < node->data) {
    node->left = ins(node->left, new_value);
  } else {
    node->right = ins(node->right, new_value);
  }
  return node;
}

TreeNode *removing(TreeNode *nodes_root, long value) {
  if (nodes_root == nullptr) return nodes_root;

  TreeNode *node_parentt = nullptr;
  TreeNode *current_node = nodes_root;

  while (current_node != nullptr && current_node->data != value) {
    node_parentt = current_node;
    current_node = (value < current_node->data) ? current_node->left : current_node->right;
  }

  if (current_node == nullptr) {
    return nodes_root;
  }
  TreeNode *temporary_node;
  if (current_node->left == nullptr) {
    temporary_node = current_node->right;
  } else if (current_node->right == nullptr) {
    temporary_node = current_node->left;
  } else {
    temporary_node = minimumsrch(current_node->right);
    current_node->data = temporary_node->data;
    current_node->right = removing(current_node->right, temporary_node->data);
    return nodes_root;
  }

  delete current_node;

  if (node_parentt == nullptr) {
    nodes_root = temporary_node;
  } else if (node_parentt->left == current_node) {
    node_parentt->left = temporary_node;
  } else {
    node_parentt->right = temporary_node;
  }

  return nodes_root;
}

void inordertraversal(TreeNode *node, long *total, long &i) {
  if (node == NULL) {
    cout << "";
    return;
  }
  inordertraversal(node->left, total, i);
  total[i++] = node->data;
  inordertraversal(node->right, total, i);
}

void merge(TreeNode *&tree_root_1, TreeNode *tree_root_2) {
  if (tree_root_2 == NULL) {
    return;
  }
  merge(tree_root_1, tree_root_2->left);
  tree_root_1 = ins(tree_root_1, tree_root_2->data);
  merge(tree_root_1, tree_root_2->right);
}

int main() {
  ios_base::sync_with_stdio(NULL);
  cin.tie(NULL);
  cout.tie(NULL);

  TreeNode *pack1 = NULL;
  TreeNode *pack2 = NULL;

  long N;
  cin >> N;

  long tree_number;
  long value;
  long total[MAX_SIZE];
  long sup_pos = 0;
  string command;

  for (int i = 0; i < N; ++i) {
    cin >> command;
    if (command[0] == 'b') {
      cin >> tree_number >> value;
      if (tree_number == 1) {
        pack1 = ins(pack1, value);
      } else {
        pack2 = ins(pack2, value);
      }
    } else if (command[0] == 's') {
      cin >> tree_number >> value;
      if (tree_number == 1) {
        pack1 = removing(pack1, value);
      } else {
        pack2 = removing(pack2, value);
      }
    } else {
      merge(pack1, pack2);
      pack2 = NULL;

      sup_pos = 0;
      inordertraversal(pack1, total, sup_pos);

      for (long k = 0; k < sup_pos; ++k) {
        if (k > 0) {
          cout << ' ';
        }
        cout << total[k];
      }
      if (sup_pos > 0) {
        cout << "\n";
      }
    }
  }
}
