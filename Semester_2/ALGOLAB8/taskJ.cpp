#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Edge {
 public:
  int b;
  int left_i;
  int right_i;
  Edge(int to, int minSize, int maxSize) {
    this->b = to;
    this->left_i = minSize;
    this->right_i = maxSize;
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> adj_list_;
 public:
  explicit Graph(int n) {
    adj_list_.resize(n + 1);
  }

  void add_edge(int a, int b, int left_i, int right_i) {
    adj_list_[a].emplace_back(b, left_i, right_i);
    adj_list_[b].emplace_back(a, left_i, right_i);
  }

  bool bfs(int begin, int finish, int minimum, int maximum) {
    std::queue<int> q;
    q.push(begin);
    std::vector<bool> visited(adj_list_.size(), false);
    visited[begin] = true;

    while (!q.empty()) {
      int temp = q.front();
      q.pop();
      if (temp == finish)
        return true;

      for (Edge &edge : adj_list_[temp]) {
        if (!visited[edge.b] and maximum <= edge.right_i and minimum >= edge.left_i) {
          visited[edge.b] = true;
          q.push(edge.b);
        }
      }
    }
    return false;
  }
};

int binary_search(Graph &graph, int l, int r, int begin, int end, int minimum) {
  int total = -1;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (graph.bfs(begin, end, minimum, mid)) {
      total = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return total;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios::sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;

  std::vector<std::vector<size_t>> all_e(m + 1, std::vector<size_t>(2));
  std::vector<std::vector<size_t>> all_passes(m + 1, std::vector<size_t>(2));

  for (int i = 0; i < m; ++i) {
    std::cin >> all_e[i + 1][0] >> all_e[i + 1][1];
  }

  Graph graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> all_passes[i + 1][0] >> all_passes[i + 1][1];
  }

  for (int i = 0; i < m; ++i) {
    size_t a = all_e[i + 1][0];
    size_t b = all_e[i + 1][1];
    graph.add_edge(a, b, all_passes[i + 1][0], all_passes[i + 1][1]);
  }

  int ans = -1;
  for (int i = 0; i < m; ++i) {
    size_t ans_binary = binary_search(graph, all_passes[i + 1][0], all_passes[i + 1][1], 1, n, all_passes[i + 1][0]);
    ans = std::max(ans, (int) (ans_binary - all_passes[i + 1][0] + 1));
  }
  std::cout << ((ans != -1) ? ans : -1);
  return 0;
}
