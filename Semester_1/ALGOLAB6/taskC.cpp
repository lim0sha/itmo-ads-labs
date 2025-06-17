#include <iostream>
#include <vector>

using namespace std;



struct Node {
  int data_;
  Node *left_;
  Node *right_;
  int height_;
};

int height(Node *node) {
  return (node == nullptr) ? 0 : node->height_;
}

Node *min(Node *root_node) {
  return (root_node->left_ == nullptr) ? root_node : min(root_node->right_);
}

Node *max(Node *root_node) {
  return (root_node->right_ == nullptr) ? root_node : max(root_node->right_);
}

Node *rotateright(Node *root_node) {
  Node *root2 = root_node->left_;
  Node *tmp = root2->right_;
  root2->right_ = root_node;
  root_node->left_ = tmp;
  root_node->height_ = max(height(root_node->left_), height(root_node->right_)) + 1;
  root2->height_ = max(height(root2->left_), height(root2->right_)) + 1;
  return root2;
}

Node *rotateleft(Node *root_node) {
  Node *root2 = root_node->right_;
  Node *tmp = root2->left_;
  root2->left_ = root_node;
  root_node->right_ = tmp;
  root_node->height_ = max(height(root_node->left_), height(root_node->right_)) + 1;
  root2->height_ = max(height(root2->left_), height(root2->right_)) + 1;
  return root2;
}

int Balance2(Node *root_node) {
  if (root_node == nullptr) {
    return 0;
  } else if (root_node->right_ != nullptr and root_node->left_ == nullptr) {
    return height(root_node->right_);
  } else if (root_node->right_ == nullptr and root_node->left_ != nullptr) {
    return 0 - height(root_node->left_);
  } else {
    return height(root_node->right_) - height(root_node->left_);
  }
}

void fixheight(Node *root_node) {
  int height_left_ = height(root_node->left_);
  int geight_right_ = height(root_node->right_);
  root_node->height_ = max(height_left_, geight_right_) + 1;
}

Node *newbalance(Node *root_node) {
  fixheight(root_node);
  if (Balance2(root_node) > 1) {
    if (Balance2(root_node->right_) < 0)
      root_node->right_ = rotateright(root_node->right_);
    return rotateleft(root_node);
  }
  if (Balance2(root_node) < -1) {
    if (Balance2(root_node->left_) > 0)
      root_node->left_ = rotateleft(root_node->left_);
    return rotateright(root_node);
  }
  return root_node;
}

vector<vector<int>> padding_array(200900, vector<int>(4));
int flag_c = 2;

Node *add(Node *root_node, int i) {
  root_node = new Node;
  root_node->data_ = padding_array[i][0];
  root_node->left_ = nullptr;
  root_node->right_ = nullptr;
  root_node->height_ = 1;
  if (padding_array[i][1] - 1 != -1) {
    root_node->left_ = add(root_node->left_, padding_array[i][1] - 1);
  }
  if (padding_array[i][2] - 1 != -1) {
    root_node->right_ = add(root_node->right_, padding_array[i][2] - 1);
  }
  return newbalance(root_node);
}

Node *add1(Node *root_node, int data_) {
  if (root_node == nullptr) {
    root_node = new Node;
    root_node->data_ = data_;
    root_node->left_ = nullptr;
    root_node->right_ = nullptr;
    root_node->height_ = 1;
  }
  if (data_ < root_node->data_) {
    root_node->left_ = add1(root_node->left_, data_);
  } else if (data_ > root_node->data_) {
    root_node->right_ = add1(root_node->right_, data_);
  }
  return newbalance(root_node);
}

void cout_tree(Node *root, int heightttt) {
  if (root == nullptr) {
    return;
  }
  if (heightttt == 1) {
    if ((root->left_ == nullptr) and (root->right_ == nullptr)) {
      cout << root->data_ << " " << 0 << " " << 0 << "\n";
    } else if ((root->left_ != nullptr) and (root->right_ != nullptr)) {
      cout << root->data_ << " " << flag_c << " " << flag_c + 1 << "\n";
      flag_c += 2;
    } else if ((root->left_ == nullptr) and (root->right_ != nullptr)) {
      cout << root->data_ << " " << 0 << " " << flag_c << "\n";
      flag_c++;
    } else if ((root->left_ != nullptr) and (root->right_ == nullptr)) {
      cout << root->data_ << " " << flag_c << " " << 0 << "\n";
      flag_c++;
    }
  } else {
    cout_tree(root->left_, heightttt - 1);
    cout_tree(root->right_, heightttt - 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int number_of_element, key, left, right, h;
  cin >> number_of_element;
  Node *tree = nullptr;
  for (int i = 0; i < number_of_element; ++i) {
    cin >> key >> left >> right;
    padding_array[i][0] = key;
    padding_array[i][1] = left;
    padding_array[i][2] = right;
    padding_array[i][3] = 1;
  }
  cin >> key;
  if (number_of_element == 0) {
    cin >> key >> left >> right;
    cout << number_of_element + 1 << "\n";
    cout << key << " " << left << " " << right << " ";
  } else {
    tree = add(tree, 0);
    tree = add1(tree, key);
    h = height(tree) + 1;
    cout << number_of_element + 1 << "\n";
    for (int i = 0; i < h; ++i) {
      cout_tree(tree, i);
    }
  }
  return 0;
}
