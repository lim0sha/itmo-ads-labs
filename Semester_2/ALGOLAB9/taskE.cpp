#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> tin, low;
vector<pair<int, int>> bridges;
vector<bool> used;
long timer = 0;

void dfs_bridges(int v, int p = -1) {
  used[v] = true;
  tin[v] = low[v] = timer++;
  for (int u : graph[v]) {
    if (u == p) continue;
    if (used[u]) {
      low[v] = min(low[v], tin[u]);
    } else {
      dfs_bridges(u, v);
      low[v] = min(low[v], low[u]);
      if (low[u] > tin[v]) {
        bridges.emplace_back(min(v, u), max(v, u));
      }
    }
  }
}

void find_bridges(int n) {
  timer = 0;
  tin.assign(n, -1);
  low.assign(n, -1);
  used.assign(n, false);
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      dfs_bridges(i);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  graph.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  find_bridges(n);

  sort(bridges.begin(), bridges.end());

  for (const auto& bridge : bridges) {
    cout << bridge.first + 1 << " " << bridge.second + 1 << "\n";
  }

  return 0;
}
