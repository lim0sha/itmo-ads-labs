#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

struct AVL_Node {
  std::string value{};
  AVL_Node* left{};
  AVL_Node* right{};
  long avl_height_itself{};
};

long AVL_Height(const AVL_Node* height) {
  return height ? height->avl_height_itself : 0;
}

void AVL_fix_height(AVL_Node* AVL_root) {
  AVL_root->avl_height_itself = std::max(AVL_Height(AVL_root->left), AVL_Height(AVL_root->right)) + 1;
}

AVL_Node* AVL_small_rotate_right(AVL_Node* AVL_root) {
  AVL_Node* root1 = AVL_root->left;
  AVL_root->left = root1->right;
  root1->right = AVL_root;
  AVL_fix_height(AVL_root);
  AVL_fix_height(root1);
  return root1;
}

AVL_Node* AVL_small_rotate_left(AVL_Node* AVL_root) {
  AVL_Node* root1 = AVL_root->right;
  AVL_root->right = root1->left;
  root1->left = AVL_root;
  AVL_fix_height(AVL_root);
  AVL_fix_height(root1);
  return root1;
}

long AVL_balance_heights(const AVL_Node* height) {
  return height ? AVL_Height(height->left) - AVL_Height(height->right) : 0;
}

AVL_Node* AVL_insert(AVL_Node* AVL_root, const std::string& value) {
  if (!AVL_root) {
    AVL_root = new AVL_Node{value, nullptr, nullptr, 1};
  } else if (value < AVL_root->value) {
    AVL_root->left = AVL_insert(AVL_root->left, value);
  } else if (value > AVL_root->value) {
    AVL_root->right = AVL_insert(AVL_root->right, value);
  }
  AVL_fix_height(AVL_root);
  const long balance = AVL_balance_heights(AVL_root);
  if (balance > 1) {
    if (value < AVL_root->left->value) {
      return AVL_small_rotate_right(AVL_root);
    } else {
      AVL_root->left = AVL_small_rotate_left(AVL_root->left);
      return AVL_small_rotate_right(AVL_root);
    }
  }
  if (balance < -1) {
    if (value > AVL_root->right->value) {
      return AVL_small_rotate_left(AVL_root);
    } else {
      AVL_root->right = AVL_small_rotate_right(AVL_root->right);
      return AVL_small_rotate_left(AVL_root);
    }
  }
  return AVL_root;
}

AVL_Node* AVL_minimum(AVL_Node* root) {
  return root->left ? AVL_minimum(root->left) : root;
}

AVL_Node* AVL_delete(AVL_Node* AVL_root, const std::string& val_for_delete) {
  if (!AVL_root) {
    return AVL_root;
  }
  if (val_for_delete < AVL_root->value) {
    AVL_root->left = AVL_delete(AVL_root->left, val_for_delete);
  } else if (val_for_delete > AVL_root->value) {
    AVL_root->right = AVL_delete(AVL_root->right, val_for_delete);
  } else if (AVL_root->left && AVL_root->right) {
    AVL_root->value = AVL_minimum(AVL_root->right)->value;
    AVL_root->right = AVL_delete(AVL_root->right, AVL_root->value);
  } else {
    AVL_Node* temp = AVL_root;
    AVL_root = AVL_root->left ? AVL_root->left : AVL_root->right;
    delete temp;
  }
  return AVL_root;
}

bool AVL_Search(const AVL_Node* AVL_root, const std::string& value) {
  if (!AVL_root) {
    return false;
  }
  if (value == AVL_root->value) {
    return true;
  }
  if (value < AVL_root->value) {
    return AVL_Search(AVL_root->left, value);
  } else {
    return AVL_Search(AVL_root->right, value);
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  AVL_Node* main_root = nullptr;
  AVL_Node* AVL_tree = nullptr;
  std::string element;
  long first_friend = 0, second_friend = 0, third_friend = 0, number_of_elements;

  std::cin >> number_of_elements;
  std::vector<std::vector<std::string>> array(3, std::vector<std::string>(number_of_elements));

  for (long i = 0; i < 3; ++i) {
    for (long j = 0; j < number_of_elements; ++j) {
      std::cin >> element;
      array[i][j] = element;
    }
  }

  for (long i = 0; i < number_of_elements; ++i) {
    main_root = AVL_insert(main_root, array[0][i]);
    AVL_tree = AVL_insert(AVL_tree, array[1][i]);
  }

  for (long i = 0; i < number_of_elements; ++i) {
    if (!AVL_Search(AVL_tree, array[2][i]) and !AVL_Search(main_root, array[2][i])) {
      third_friend += 3;
    } else if (!AVL_Search(AVL_tree, array[2][i]) or !AVL_Search(main_root, array[2][i])) {
      if (!AVL_Search(AVL_tree, array[2][i]) and AVL_Search(main_root, array[2][i])) {
        ++third_friend;
      } else if (AVL_Search(AVL_tree, array[2][i]) and !AVL_Search(main_root, array[2][i])) {
        ++third_friend;
      }
    }
  }

  for (long i = 0; i < number_of_elements; ++i) {
    AVL_tree = AVL_delete(AVL_tree, array[1][i]);
  }

  for (long i = 0; i < number_of_elements; ++i) {
    AVL_tree = AVL_insert(AVL_tree, array[2][i]);
  }

  for (long i = 0; i < number_of_elements; ++i) {
    if (!AVL_Search(AVL_tree, array[1][i]) and !AVL_Search(main_root, array[1][i])) {
      second_friend += 3;
    } else if (!AVL_Search(AVL_tree, array[1][i]) or !AVL_Search(main_root, array[1][i])) {
      if (!AVL_Search(AVL_tree, array[1][i]) and AVL_Search(main_root, array[1][i])) {
        ++second_friend;
      } else if (AVL_Search(AVL_tree, array[1][i]) and !AVL_Search(main_root, array[1][i])) {
        ++second_friend;
      }
    }
  }

  for (long i = 0; i < number_of_elements; ++i) {
    AVL_tree = AVL_delete(AVL_tree, array[2][i]);
    main_root = AVL_delete(main_root, array[0][i]);
  }

  for (long i = 0; i < number_of_elements; ++i) {
    main_root = AVL_insert(main_root, array[1][i]);
    AVL_tree = AVL_insert(AVL_tree, array[2][i]);
  }

  for (long i = 0; i < number_of_elements; ++i) {
    if (!AVL_Search(AVL_tree, array[0][i]) and !AVL_Search(main_root, array[0][i])) {
      first_friend += 3;
    } else if (!AVL_Search(AVL_tree, array[0][i]) or !AVL_Search(main_root, array[0][i])) {
      if (!AVL_Search(AVL_tree, array[0][i]) and AVL_Search(main_root, array[0][i])) {
        ++first_friend;
      } else if (AVL_Search(AVL_tree, array[0][i]) and !AVL_Search(main_root, array[0][i])) {
        ++first_friend;
      }
    }
  }

  std::cout << first_friend << ' ' << second_friend << ' ' << third_friend;
  return 0;
}
