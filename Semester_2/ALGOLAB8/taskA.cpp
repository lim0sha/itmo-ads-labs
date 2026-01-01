#include <iostream>
#include <vector>

using namespace std;

void DFS(int u, const vector<vector<int>>& adj_list, vector<bool>& visited, vector<int>& sorted_points, int& current) {
  visited[u] = true;
  for (int v : adj_list[u]) {
    if (!visited[v]) {
      DFS(v, adj_list, visited, sorted_points, current);
    }
  }
  sorted_points[u] = current--;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj_list(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj_list[u].push_back(v);
  }

  vector<int> sorted_points(n + 1);

  int current = n;
  vector<bool> visited(n + 1, false);
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      DFS(i, adj_list, visited, sorted_points, current);
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << sorted_points[i] << " ";
  }

  return 0;
}
