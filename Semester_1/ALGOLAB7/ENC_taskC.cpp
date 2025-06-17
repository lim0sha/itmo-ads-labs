#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int kCharCount = 26;

struct Hf_Node {
  char symbol;
  int frequency;
  Hf_Node* left;
  Hf_Node* right;

  Hf_Node(char bukva, int frq) : symbol(bukva), frequency(frq), left(nullptr), right(nullptr) {}
};

struct Compare2Nodes {
  bool operator()(Hf_Node* H_node_1, Hf_Node* H_node_2) {
    return H_node_1->frequency > H_node_2->frequency;
  }
};

void Get_hufman_lenght_helper(Hf_Node* H_node, int& huffmanLength, int depth) {
  if (H_node->left == nullptr and H_node->right == nullptr) {
    huffmanLength += depth * H_node->frequency;
    return;
  }
  if (H_node->left != nullptr) {
    Get_hufman_lenght_helper(H_node->left, huffmanLength, depth + 1);
  }
  if (H_node->right != nullptr) {
    Get_hufman_lenght_helper(H_node->right, huffmanLength, depth + 1);
  }
}

void Destroy_Tree(Hf_Node* node) {
  if (node == nullptr) {
    return;
  } else {
    Destroy_Tree(node->left);
    Destroy_Tree(node->right);
    delete node;
  }
}

int Get_hufman_length(const string& s) {
  int frequencyArray[kCharCount] = {0};

  for (char c : s) {
    if (islower(c)) {
      frequencyArray[c - 'a']++;
    }
  }

  priority_queue<Hf_Node*, vector<Hf_Node*>, Compare2Nodes> pq;
  for (int i = 0; i < kCharCount; ++i) {
    if (frequencyArray[i] > 0) {
      pq.push(new Hf_Node('a' + i, frequencyArray[i]));
    }
  }

  while (pq.size() > 1) {
    Hf_Node* left = pq.top();
    pq.pop();
    Hf_Node* right = pq.top();
    pq.pop();

    auto* internal_hufmn_node = new Hf_Node('\0', left->frequency + right->frequency);
    internal_hufmn_node->left = left;
    internal_hufmn_node->right = right;

    pq.push(internal_hufmn_node);
  }

  Hf_Node* root = pq.top();

  int total_length = 0;
  Get_hufman_lenght_helper(root, total_length, 0);
  Destroy_Tree(root);

  return total_length;
}

int main() {
  string s;
  cin >> s;
  cout << Get_hufman_length(s);
  return 0;
}
