#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
  int a, b;
};

class Graph {
 public:
  vector<vector<int>> adjacency_list_;

  Graph(vector<Edge> const &edges, int n) {
    adjacency_list_.resize(n);
    for (int i = 0; i < edges.size(); ++i) {
      adjacency_list_[edges[i].a].push_back(edges[i].b);
      adjacency_list_[edges[i].b].push_back(edges[i].a);
    }
  }

  void add_edge(int a, int b) {
    --a;
    --b;
    this->adjacency_list_[a].push_back(b);
    this->adjacency_list_[b].push_back(a);
  }

  bool bfs(int start, int finish, const vector<vector<int>>& adj_list_) {
    vector<bool> visited(adj_list_.size(), false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
      int temporary = q.front();
      q.pop();
      for (auto nearby_vertex : adj_list_[temporary]) {
        if (nearby_vertex == finish) {
          return true;
        }
        if (!visited[nearby_vertex]) {
          visited[nearby_vertex] = true;
          q.push(nearby_vertex);
        }
      }
    }
    return false;
  }

  bool request_answer(int a, int b, const vector<vector<int>>& adj_list_) {
    if (a == b) {
      return true;
    }
    return bfs(a, b, adj_list_);
  }


  static void delete_edge(int a, int b, std::vector<std::vector<int>>& adjacency_list_) {
    auto it = std::find(adjacency_list_[a].begin(), adjacency_list_[a].end(), b);
    if (it != adjacency_list_[a].end()) {
      adjacency_list_[a].erase(it);
    }

    it = std::find(adjacency_list_[b].begin(), adjacency_list_[b].end(), a);
    if (it != adjacency_list_[b].end()) {
      adjacency_list_[b].erase(it);
    }
  }

};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<Edge> all_edges;
  int n, m, q;
  char request;
  cin >> n >> m >> q;

  Graph graph(all_edges, n);
  int a, b;

  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    graph.add_edge(a, b);
  }

  int a_to_workwith, b_to_workwith;
  for (int i = 0; i < q; ++i) {
    cin >> request >> a_to_workwith >> b_to_workwith;
    --a_to_workwith;
    --b_to_workwith;
    if (request == '?') {
      if (graph.request_answer(a_to_workwith, b_to_workwith, graph.adjacency_list_)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    } else if (request == '-') {
      Graph::delete_edge(a_to_workwith, b_to_workwith, graph.adjacency_list_);
    }
  }
  return 0;
}