#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;

void dfs(int v) {
  visited[v] = true;
  for (int u : adj_list[v]) {
    if (!visited[u]) {
      dfs(u);
    }
  }
}

int count_connected_components(int n) {
  int result = 0;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
      ++result;
    }
  }
  return result;
}

int main() {
  int n, m;
  cin >> n >> m;

  adj_list.resize(n + 1);

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj_list[a].push_back(b);
    adj_list[b].push_back(a); // для неориент графа
  }

  visited.assign(n + 1, false);
  cout << count_connected_components(n) << "\n";
  return 0;
}
