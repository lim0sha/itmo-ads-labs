#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
 private:
  const size_t Kvertexundef = -10000;
  vector<vector<size_t>> g_, gr_;
  vector<size_t> visited_, visited_r_, consiquence_;
  set<pair<size_t, size_t>> result;
  static size_t unique_id_;

  // дфс с функцией топ сорта (делает нужный порядок вершин)
  void dfs_to_form_order(size_t vertex) {
    visited_[vertex] = 1;
    for (size_t i = 0; i < gr_[vertex].size(); ++i) {
      size_t to = gr_[vertex][i];
      if (!visited_[to]) {
        dfs_to_form_order(to);
      }
    }
    consiquence_.push_back(vertex);
  }

  // дфс по конденсации графа = по компонентам
  void dfs_scc(size_t v, size_t scc_index) {
    visited_[v] = scc_index;
    for (size_t i = 0; i < g_[v].size(); ++i) {
      size_t to = g_[v][i];
      if (!visited_[to]) {
        dfs_scc(to, scc_index);
      }
    }
  }

  // поиск мостов дфсом
  void dfs_bridges(size_t vertex, size_t *scc_index, std::vector<size_t> &scc_minimum_vertex) {
    visited_r_[vertex] = 1;
    for (size_t i = 0; i < gr_[vertex].size(); ++i) {
      size_t to = gr_[vertex][i];
      if (visited_[vertex] != visited_[to]) {
        pair<size_t, size_t> bridge(scc_minimum_vertex[visited_[to] - 1], scc_minimum_vertex[visited_[vertex] - 1]);
        result.insert(bridge);
        (*scc_index)++;
      }
      if (!visited_r_[to]) {
        dfs_bridges(to, scc_index, scc_minimum_vertex);
      }
    }
  }

 public:
  Graph();
  Graph(size_t n) {
    g_.resize(n);
    gr_.resize(n);
    visited_.resize(n);
    visited_r_.resize(n);
    unique_id_++;
  }

  // добавление вершины
  void add(size_t a, size_t b) {
    --a;
    --b;
    g_[a].push_back(b);
    gr_[b].push_back(a);
  }

  void findScc() {
    // прошли прямо, сделали порядок
    visited_.assign(g_.size(), 0);
    for (size_t vertex = 0; vertex < g_.size(); ++vertex) {
      if (!visited_[vertex]) {
        dfs_to_form_order(vertex);
      }
    }

    // прошли в обратном порядке, посчитали scc
    reverse(consiquence_.begin(), consiquence_.end());
    visited_.assign(g_.size(), 0);
    size_t scc = 0;
    for (size_t i = 0; i < consiquence_.size(); ++i) {
      size_t vertex = consiquence_[i];
      if (!visited_[vertex]) {
        dfs_scc(vertex, ++scc);
      }
    }

    // в каждой компоненте ищем нужный номер по наименьшей вершине
    vector<size_t> min_point(scc, Kvertexundef);
    for (size_t i = 0; i < visited_.size(); ++i) {
      size_t component = visited_[i];
      if (min_point[component - 1] == Kvertexundef) {
        min_point[component - 1] = i;
      }
    }

    // именуем компоненты как надо
    visited_r_.assign(g_.size(), 0);
    size_t counter = 0;
    for (size_t i = 0; i < consiquence_.size(); ++i) {
      size_t vertex = consiquence_[i];
      if (!visited_r_[vertex]) {
        dfs_bridges(vertex, &counter, min_point);
      }
    }

    // принт
    cout << scc << " ";
    cout << result.size() << "\n";
    for (set<pair<size_t, size_t>>::iterator it = result.begin(); it != result.end(); ++it) {
      cout << (*it).first + 1 << " " << (*it).second + 1 << "\n";
    }
  }
};

size_t Graph::unique_id_ = 0;

int main() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
  size_t n, m, a, b, i;
  cin >> n >> m;
  Graph graph(n);
  for (i = 0; i < m; ++i) {
    cin >> a >> b;
    graph.add(a, b);
  }
  graph.findScc();
  return 0;
}
