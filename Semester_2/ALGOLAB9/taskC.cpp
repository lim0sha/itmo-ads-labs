#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
  int to;
  int weight;

  Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

int dkstr(vector<vector<Edge>> &graph, int start, int end) {
  int n = graph.size();
  vector<int> distance(n, numeric_limits<int>::max());
  distance[start] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, start});

  while (!pq.empty()) {
    int u = pq.top().second;
    int dist = pq.top().first;
    pq.pop();

    if (dist > distance[u])
      continue;

    for (Edge &e : graph[u]) {
      int v = e.to;
      int weight = e.weight;

      if (distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        pq.push({distance[v], v});
      }
    }
  }

  return distance[end];
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<Edge>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b, t;
    cin >> a >> b >> t;
    graph[a].push_back(Edge(b, t));
  }

  int start = 1;
  int end = n;
  int result = dkstr(graph, start, end);
  if (result == numeric_limits<int>::max())
    cout << "-1";
  else
    cout << result;

  return 0;
}