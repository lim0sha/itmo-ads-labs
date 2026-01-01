#include <iostream>
#include <vector>

using namespace std;

bool dfs(int curr, int end, vector<vector<int>>& adj_list, vector<bool>& visited) {
  if (curr == end) {
    return true;
  }
  visited[curr] = true;
  for (size_t i = 0; i < adj_list[curr].size(); ++i) {
    int neighbor = adj_list[curr][i];
    if ((visited[neighbor] == false) and dfs(neighbor, end, adj_list, visited))
      return true;
  }
  return false;
}

bool can_reach(int start_point, int finish_point, vector<vector<int>>& adj_list) {
  vector<bool> visited(adj_list.size(), false);
  return dfs(start_point, finish_point, adj_list, visited);
}

int main() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<int>> adj_list(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj_list[a].push_back(b);
  }

  for (int i = 0; i < q; i++) {
    int start_vertex, end_vertex;
    cin >> start_vertex >> end_vertex;
    if (can_reach(start_vertex, end_vertex, adj_list) and can_reach(end_vertex, start_vertex, adj_list)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}

