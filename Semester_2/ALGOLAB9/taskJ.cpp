#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

struct Node {
  string data;
  Node *next{};
};

struct Stack {
 private:
  Node *top;

 public:
  Stack() { top = nullptr; }

  void push(string data) {
    Node *newNode = new Node();
    newNode->data = std::move(data);
    newNode->next = top;
    top = newNode;
  }

  string pop() {
    if (top == nullptr) {
      return "";
    }

    string data = top->data;
    Node *temp = top;
    top = top->next;
    delete temp;
    return data;
  }

  string peek() {
    if (top == nullptr) {
      return "";
    }
    return top->data;
  }

  bool empty() {
    if (this->top == nullptr) {
      return true;
    } else {
      return false;
    }
  }
};

class DisjointSet {
 private:
  vector<int> parent_;
  vector<int> rank_;

 public:
  explicit DisjointSet(int n) {
    parent_.resize(n);
    rank_.resize(n);
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
      rank_[i] = 0;
    }
  }

  int find(int x) {
    if (parent_[x] == x) {
      return x;
    }
    return parent_[x] = find(parent_[x]);
  }

  void merge(int x, int y) {
    int parentX = find(x);
    int parentY = find(y);
    if (parentX != parentY) {
      if (rank_[parentX] < rank_[parentY]) {
        swap(parentX, parentY);
      }
      parent_[parentY] = parentX;
      if (rank_[parentX] == rank_[parentY]) {
        rank_[parentX] += 1;
      }
    }
  }

};

struct ans {
  bool response_s;
  pair<int, int> e_;
};

class Graph {
 private:
  DisjointSet DSU_;
  vector<pair<int, int>> G;
  vector<ans> all_requests_;
  vector<pair<int, int>> for_deletion;

 public:
  Graph(int n, int m) : DSU_(n), G(m) {}

  bool binsrch(vector<pair<int, int>> &array, pair<int, int> it) {
    return binary_search(array.begin(), array.end(), it);
  }

  void makegraph() {
    for (auto & i : G) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      i.first = min(a, b);
      i.second = max(a, b);
    }
  }

  void makerequests(int q) {
    for (int i = 0; i < q; ++i) {
      char response;
      int a, b;
      cin >> response >> a >> b;
      --a;
      --b;
      if (response == '?') {
        all_requests_.push_back({true, {a, b}});
      } else if (response == '-') {
        (a < b) ? for_deletion.emplace_back(a, b) : for_deletion.emplace_back(b, a);
        all_requests_.push_back({false, {(a < b) ? a : b, (a < b) ? b : a}});
      }
    }
  }

  void sortgraph() {
    vector<pair<int, int>> grapph_copy;
    sort(G.begin(), G.end());
    sort(for_deletion.begin(), for_deletion.end());
    for (const auto & i : G) {
      if (!binsrch(for_deletion, i)) {
        if (!binsrch(grapph_copy, i)) {
          grapph_copy.push_back(i);
        }
      }
    }
    G = grapph_copy;
  }

  void merge() {
    for (auto &edge : G) {
      DSU_.merge(edge.first, edge.second);
    }
  }

  void answer() {
    Stack output;
    for (int i = all_requests_.size() - 1; i >= 0; --i) {
      if (all_requests_[i].response_s) {
        output.push(DSU_.find(all_requests_[i].e_.first) == DSU_.find(all_requests_[i].e_.second) ? "YES" : "NO");
      } else {
        DSU_.merge(all_requests_[i].e_.first, all_requests_[i].e_.second);
      }
    }
    while (!output.empty()) {
      cout << output.pop() << "\n";
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  Graph Graph(n, m);
  Graph.makegraph();
  Graph.makerequests(q);
  Graph.sortgraph();
  Graph.merge();
  Graph.answer();

  return 0;
}
