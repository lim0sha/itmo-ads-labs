#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj; // Список смежности
vector<bool> visited;
int n, m;

void dfs(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
}

bool isHydra() {
    visited.assign(n + 1, false);
    int components = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    return components == 1;
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    if (m == n and isHydra()) {
        cout << "ARCHIMEDES";
    } else {
        cout << "EUCLID";
    }

    return 0;
}
