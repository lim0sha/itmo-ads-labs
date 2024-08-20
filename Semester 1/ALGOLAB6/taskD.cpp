#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct AVL_Node {
  string contact_name;
  AVL_Node *left_node;
  AVL_Node *right_node;
  long long height_itself;
  long long balance;
};



int AVL_get_height(AVL_Node *root) {
  return (root == nullptr) ? 0 : root->height_itself;
}

AVL_Node *AVL_fix_height(AVL_Node *root) {
  long long left_height = AVL_get_height(root->left_node);
  long long right_height = AVL_get_height(root->right_node);
  root->height_itself = 1 + std::max(left_height, right_height);
  root->balance = right_height - left_height;
  return root;
}

AVL_Node *AVL_small_rotate_left(AVL_Node *avl_node) {
  AVL_Node *p_node = avl_node->right_node;
  avl_node->right_node = p_node->left_node;
  p_node->left_node = avl_node;
  p_node = AVL_fix_height(p_node);
  avl_node = AVL_fix_height(avl_node);
  return p_node;
}

AVL_Node *AVL_small_rotate_right(AVL_Node *avl_node) {
  AVL_Node *p_node = avl_node->left_node;
  avl_node->left_node = p_node->right_node;
  p_node->right_node = avl_node;
  p_node = AVL_fix_height(p_node);
  avl_node = AVL_fix_height(avl_node);
  return p_node;
}

AVL_Node *AVL_insert(string Name, AVL_Node *root, long long &count) {
  if (root == NULL) {
    return new AVL_Node(Name);
  }

  if (Name < root->contact_name) {
    root->left_node = AVL_insert(Name, root->left_node, count);
  } else if (Name > root->contact_name) {
    root->right_node = AVL_insert(Name, root->right_node, count);
  } else if (Name == root->contact_name) {
    for (int i = 0; i < Name.size(); ++i) {
      bool isUnique = true;
      for (int k = 0; k < i; ++k) {
        if (Name[i] == Name[k]) {
          isUnique = false;
          break;
        }
      }
      if (isUnique) {
        ++count;
      }
    }
    return root;
  }

  root = AVL_fix_height(root);
  long long balance = AVL_get_height(root->right_node) - AVL_get_height(root->left_node);

  if (balance == -2 and root->left_node->balance == 1){
    root->left_node = AVL_small_rotate_left(root->left_node);
    return AVL_small_rotate_right(root);
  }
  else if(balance == -2 and root->left_node->balance != 1){
    return AVL_small_rotate_right(root);
  }
  else if(balance == 2 and root->right_node->balance != -1){
    return AVL_small_rotate_left(root);
  }
  else if(balance == 2 and root->right_node->balance == -1){
    root->right_node = AVL_small_rotate_right(root->right_node);
    return AVL_small_rotate_left(root);
  }

  return root;
}

int main() {
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  AVL_Node *tree_head = nullptr;
  long long total = 0;
  string contact_name;
  for (int i = 0; i < N; ++i) {
    cin >> contact_name;
    tree_head = AVL_insert(contact_name, tree_head, total);
  }
  cout << total;
  return 0;
}
