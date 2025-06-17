#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int data_ = 0;
  int left_ = -1;
  int right_ = -1;
};

struct AVLtreenpde {
  int key = 0;
  int height = 0;
  int absoluteIndex = -1;
  AVLtreenpde *leftChild = nullptr;
  AVLtreenpde *rightChild = nullptr;
  AVLtreenpde(int k, int index) {
    key = k;
    absoluteIndex = index;
  }
};

struct AVLtree {
  vector<Node *> tree;
  vector<Node *> tempTree;
  AVLtreenpde *root{};
  void get_tree_heights() {
    if (!tree.empty()) {
      h_DFS(root);
    }
  }

  void h_DFS(AVLtreenpde *v) {
    if (v->leftChild != nullptr) {
      h_DFS(v->leftChild);
    }
    if (v->rightChild != nullptr) {
      h_DFS(v->rightChild);
    }
    v->height = max(h_left(v), h_right(v)) + 1;
  }

  int h_left(AVLtreenpde *node) {
    if (node->leftChild != nullptr) {
      return node->leftChild->height;
    } else {
      return 0;
    }
  }

  int h_right(AVLtreenpde *node) {
    if (node->rightChild != nullptr) {
      return node->rightChild->height;
    } else {
      return 0;
    }
  }

  int balance(AVLtreenpde *node) {
    if (node == nullptr) {
      return 0;
    }
    int l = 0;
    int r = 0;
    if (node->leftChild != nullptr) {
      l = node->leftChild->height;
    }
    if (node->rightChild != nullptr) {
      r = node->rightChild->height;
    }
    return r - l;
  }

  void makeTreeAVL() {
    root = new AVLtreenpde(tree[0]->data_, 0);
    makeDFS(root);
  }

  void makeDFS(AVLtreenpde *node) {
    if (tree[node->absoluteIndex]->left_ != -1) {
      int i = tree[node->absoluteIndex]->left_;
      node->leftChild = new AVLtreenpde(tree[i]->data_, i);
      makeDFS(node->leftChild);
    } else {
      node->leftChild = nullptr;
    }

    if (tree[node->absoluteIndex]->right_ != -1) {
      int i = tree[node->absoluteIndex]->right_;
      node->rightChild = new AVLtreenpde(tree[i]->data_, i);
      makeDFS(node->rightChild);
    } else {
      node->rightChild = nullptr;
    }
  }

  AVLtreenpde *little_left_rotation(AVLtreenpde *node) {
    AVLtreenpde *u = node->rightChild;
    node->rightChild = u->leftChild;
    u->leftChild = node;
    node->height = max(h_left(node), h_right(node)) + 1;
    node->height = max(h_left(node), h_right(node)) + 1;
    return u;
  }

  AVLtreenpde *little_right_rotation(AVLtreenpde *node) {
    AVLtreenpde *u = node->leftChild;
    node->leftChild = u->rightChild;
    u->rightChild = node;
    node->height = max(h_left(node), h_right(node)) + 1;
    node->height = max(h_left(node), h_right(node)) + 1;
    return u;
  }

  AVLtreenpde *toBalance(AVLtreenpde *node) {
    if (balance(node->rightChild) < 0) {
      node->rightChild = little_right_rotation(node->rightChild);
    }
    return little_left_rotation(node);
  }

  void Bfs() {
    queue<AVLtreenpde *> QUEUE;
    QUEUE.push(root);
    int n = 1;
    while (!QUEUE.size() == 0) {
      AVLtreenpde *node = QUEUE.front();
      QUEUE.pop();
      int left_n = 0;
      int right_n = 0;
      if (node->leftChild != nullptr) {
        QUEUE.push(node->leftChild);
        left_n = ++n;
      }
      if (node->rightChild != nullptr) {
        QUEUE.push(node->rightChild);
        right_n = ++n;
      }
      tempTree.push_back(new Node(node->key, left_n, right_n));
    }

  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  int k;
  int li;
  int r;

  cin >> N;
  AVLtree newAVLtree;

  for (int i = 0; i < N; ++i) {
    cin >> k >> li >> r;
    newAVLtree.tree.push_back(new Node(k, li - 1, r - 1));
  }

  newAVLtree.makeTreeAVL();
  newAVLtree.get_tree_heights();
  newAVLtree.root = newAVLtree.toBalance(newAVLtree.root);
  newAVLtree.Bfs();

  cout << newAVLtree.tempTree.size() << "\n";

  for (auto t : newAVLtree.tempTree) {
    cout << t->data_ << " " << t->left_ << " " << t->right_ << "\n";
  }
  return 0;
}
