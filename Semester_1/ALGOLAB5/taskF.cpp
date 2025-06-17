#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
  int data;
  Node* left;
  Node* right;
};

Node* Insert(Node* x, int z) {
  if (x == nullptr) {
    return new Node{z, nullptr, nullptr};
  }
  if (z < x->data) {
    x->left = Insert(x->left, z);
  } else if (z > x->data) {
    x->right = Insert(x->right, z);
  }
  return x;
}

void Inorder(Node* root, int result[], int& index) {
  if (!root) {
    return;
  }
  Inorder(root->left, result, index);
  result[index++] = root->data;
  Inorder(root->right, result, index);
}

void Preorder(Node* root, int result[], int& index) {
  if (!root) {
    return;
  }
  result[index++] = root->data;
  Preorder(root->left, result, index);
  Preorder(root->right, result, index);
}

void Postorder(Node* root, int total[], int& pos) {
  if (!root) {
    return;
  }
  Postorder(root->left, total, pos);
  Postorder(root->right, total, pos);
  total[pos++] = root->data;
}

long long peekBST(const int* arr, long long left, long long right, int x) {
  for (long long i = left; i < right; ++i) {
    if (arr[i] == x) {
      return i;
    }
  }
  return -1;
}

Node* builder(const int inrdr[], const int preordr[], long long& pos, long long in_pos, long long end_pos) {
  if (in_pos > end_pos) {
    return nullptr;
  }

  Node* node = new Node{preordr[pos++], nullptr, nullptr};
  if (in_pos == end_pos) {
    return node;
  }

  long long inIndex = peekBST(inrdr, in_pos, end_pos + 1, node->data);
  if (inIndex == -1) {
    cout << "NO";
    exit(0);
  }

  node->left = builder(inrdr, preordr, pos, in_pos, inIndex - 1);
  node->right = builder(inrdr, preordr, pos, inIndex + 1, end_pos);
  return node;
}

Node* make_BST(const int* inn, const int* pre, int n) {
  long long sup_pos = 0;
  return builder(inn, pre, sup_pos, 0, n - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  int innnnnn[N], preeeeee[N], psttttt[N];

  for (int i = 0; i < N; ++i) {
    cin >> preeeeee[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> innnnnn[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> psttttt[i];
  }

  Node* root = make_BST(innnnnn, preeeeee, N);

  int in[N], pre[N], post[N];
  int inIndex = 0, preIndex = 0, postIndex = 0;

  Postorder(root, post, postIndex);
  Inorder(root, in, inIndex);
  Preorder(root, pre, preIndex);

  if (equal(in, in + N, innnnnn) and equal(pre, pre + N, preeeeee) and equal(post, post + N, psttttt))
    cout << "YES";
  else
    cout << "NO";

  return 0;
}
