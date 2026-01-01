#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
 public:
  vector<vector<int>> g, gr;
  vector<int> visited, order, scc;
  void dfs1(int v) {
    visited[v] = 1;
    for (int to : gr[v])
      if (!visited[to])
        dfs1(to);
    order.push_back(v);
  }
  void dfs2(int v, int component) {
    visited[v] = component;
    for (int to : g[v])
      if (!visited[to])
        dfs2(to, component);
  }
 public:
  Graph(int v) {
    g.resize(v);
    gr.resize(v);
  }
  void add_edge(int a, int b) {
    g[a].push_back(b);
    gr[b].push_back(a);
  }
  vector<int> find_scc() {
    visited.assign(g.size(), 0);
    for (int v = 0; v < g.size(); ++v)
      if (!visited[v])
        dfs1(v);
    reverse(order.begin(), order.end());
    visited.assign(g.size(), 0);
    int scc_count = 0;
    for (int v : order)
      if (!visited[v])
        dfs2(v, ++scc_count);
    return visited;
  }
  int count_bridges() {
    set<pair<int, int>> bridges; // Множество для хранения уникальных рёбер между компонентами
    for (int v = 0; v < g.size(); ++v) {
      for (int to : g[v]) {
        if (scc[v] != scc[to]) { // Проверяем, что вершины принадлежат разным компонентам сильной связности
          bridges.insert({min(scc[v], scc[to]), max(scc[v], scc[to])});
        }
      }
    }
    return bridges.size();
  }
  void rename_scc(vector<int>& scc) {
    vector<int> min_vertex(scc.size(), -1); // Вектор для хранения минимальной вершины в компонентах сильной связности
    for (int i = 0; i < scc.size(); ++i) {
      int compvalue = scc[i];
      if (min_vertex[compvalue] == -1 || i < min_vertex[compvalue]) {
        min_vertex[compvalue] = i;
      }
    }
    for (int &compvalue : scc) {
      compvalue = min_vertex[compvalue] + 1; // Нумерация начинается с 1, а не с 0
    }
  }
  void print_bridges() {
    set<pair<int, int>> bridges; // Множество для хранения уникальных рёбер между компонентами
    for (int v = 0; v < g.size(); ++v) {
      for (int to : g[v]) {
        if (scc[v] != scc[to]) { // Проверяем, что вершины принадлежат разным компонентам сильной связности
          bridges.insert({scc[v], scc[to]});
        }
      }
    }
    for (const auto &bridge : bridges) {
      cout << bridge.first << " " << bridge.second << "\n";
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  long n, m, a, b;
  cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    graph.add_edge(a-1, b-1);
  }
  graph.scc = graph.find_scc();
  graph.rename_scc(graph.scc);
  cout << set<int>(graph.scc.begin(), graph.scc.end()).size() << " ";
  cout << graph.count_bridges() << "\n";
  graph.print_bridges();
}