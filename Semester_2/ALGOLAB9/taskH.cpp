#include <iostream>
#include <vector>
#include <string>

using namespace std;

int dfs(const vector<vector<int>>& graph, int u, int dest, vector<bool>& visited) {
  if (u == dest) {
    return 0;
  }
  visited[u] = true;
  for (int v : graph[u]) {
    if (!visited[v]) {
      int pathLength = dfs(graph, v, dest, visited);
      if (pathLength >= 0)
        return pathLength + 1;
    }
  }
  return -1;
}

int isUniquePath(const vector<vector<int>>& graph, int src, int dest, int n) {
  vector<bool> visited(n + 1, false);
  return dfs(graph, src, dest, visited);
}

void dfs(const vector<vector<int>>& graph, int u, int dest, vector<bool>& visited, int& pathCount) {
  if (u == dest) {
    pathCount++;
    return;
  }
  visited[u] = true;
  for (int v : graph[u]) {
    if (!visited[v]) {
      dfs(graph, v, dest, visited, pathCount);
    }
  }
  visited[u] = false;
}

bool isUniquePath_bool(const vector<vector<int>>& graph, int src, int dest, int n) {
  vector<bool> visited(n + 1, false);
  int pathCount = 0;
  dfs(graph, src, dest, visited, pathCount);
  return pathCount == 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n + 1);
  vector<string> vertices(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> vertices[i];
  }

  for (int i = 0; i < m; ++i) {
    string u, v;
    cin >> u >> v;
    int uId = -1, vId = -1;
    for (int j = 1; j <= n; ++j) {
      if (vertices[j] == u) uId = j;
      if (vertices[j] == v) vId = j;
    }
    if (uId != -1 && vId != -1) {
      graph[uId].push_back(vId);
      graph[vId].push_back(uId);
    }
  }

  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int pathLength = isUniquePath(graph, i, j, n);
      if (isUniquePath_bool(graph, i, j, n)) {
        // cout << i << " " << j << " " << pathLength << "\n";
        answer += pathLength;
      }
    }
  }
  std::cout << answer;
  return 0;
}
