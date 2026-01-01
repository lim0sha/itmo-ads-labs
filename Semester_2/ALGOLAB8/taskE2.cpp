#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int start, finish;
};

struct Graph {
  vector<vector<int>> adj_list;
  Graph(vector<Edge> const &edges, int n) {
    adj_list.resize(n);
    for (size_t i = 0; i < edges.size(); ++i) {
      Edge edge = edges[i];
      adj_list[edge.start].push_back(edge.finish);
      adj_list[edge.finish].push_back(edge.start);
    }
  }
};

bool DFS(Graph const &graph, int v, vector<bool> &visited, int parent) {
  visited[v] = true;
  for (int w: graph.adj_list[v]) {
    if (!visited[w]) {
      if (DFS(graph, w, visited, v)) {
        return true;
      }
    } else if (w != parent) {
      return true;
    }
  }
  visited[v] = false;
  return false;
}

int main() {
  vector<Edge> edges;

  int n, m;
  cin >> n >> m;
  int u, v;

  Graph graph(edges, n);

  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    graph.adj_list[u - 1].push_back(v - 1);
    graph.adj_list[v - 1].push_back(u - 1);
  }

  vector<bool> visited(n, false);

  bool has_cycle = false;
  for (int i = 0; i < n; ++i) {
    if (DFS(graph, i, visited, -1)) {
      has_cycle = true;
      break;
    }
  }
  if (has_cycle) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }

  return 0;
}