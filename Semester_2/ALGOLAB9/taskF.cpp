#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class FB {
 private:
  const int kinf = 1000000000;
  struct edge {
    int a, b, w;
  };

  int N, K, n{}, m{};
  std::vector<int> d;
  std::vector<int> p;
  std::vector<edge> edges;

 public:
  FB(int N, int k) : N(N), K(k) {}

  void chech_cycles() {
    for (int i = 0; i < N; ++i) {
      std::cin >> n >> m;

      edges.resize(m);
      d.resize(n);
      p.resize(n, -1);

      for (int j = 0; j < m; ++j) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[j] = {u - 1, v - 1, w};
      }

      if (has_cycle()) {
        std::cout << "NO\n";
      } else {
        std::cout << "YES\n";
      }
    }
  }

 private:
  bool has_cycle() {
    int saved_vertex = -1;
    for (int i = 0; i < n; ++i) {
      bool flag = false;
      saved_vertex = -1;
      for (int j = 0; j < m; ++j) {
        edge edge = edges[j];
        // релакс типо хахахаха
        if (d[edge.a] + edge.w < d[edge.b]) {
          d[edge.b] = std::max(-kinf, d[edge.a] + edge.w);
          flag = true;
          p[edge.b] = edge.a;
          saved_vertex = edge.b;
        }
      }
      if (!flag) {
        break;
      }
    }

    if (saved_vertex == -1) {
      return false;
    } else {
      int x = saved_vertex;
      for (int i = 0; i < n; ++i) {
        x = p[x];
      }
      std::vector<int> cycle;
      for (int cur = x;  ;cur = p[cur]) {
        cycle.push_back(cur);
        if (cur == x and cycle.size() > 1) {
          break;
        }
      }
      return cycle.size() > K;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N, k;
  std::cin >> N >> k;
  FB fb_alg(N, k);
  fb_alg.chech_cycles();

  return 0;
}
