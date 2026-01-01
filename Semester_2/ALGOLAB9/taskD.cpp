#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const unsigned long long kInf = ULLONG_MAX;

class G_edge {
 public:
  unsigned long long a, b;
  unsigned long long weight_;
};

int main() {
  unsigned long long n, m;
  cin >> n >> m;

  vector<G_edge> edges(m);
  for (unsigned long long i = 0; i < m; ++i) {
    cin >> edges[i].a >> edges[i].b >> edges[i].weight_;
    --edges[i].a;
    --edges[i].b;
  }

  vector<vector<unsigned long long>> d(n, vector<unsigned long long>(n, kInf));

  for (unsigned long long i = 0; i < m; ++i) {
    d[edges[i].a][edges[i].b] = min(d[edges[i].a][edges[i].b], edges[i].weight_);
    d[edges[i].b][edges[i].a] = min(d[edges[i].b][edges[i].a], edges[i].weight_);
  }

  for (unsigned long long i = 0; i < n; ++i) {
    d[i][i] = 0;
  }

  for (unsigned long long v = 0; v < n; ++v) {
    for (unsigned long long a = 0; a < n; ++a) {
      for (unsigned long long b = 0; b < n; ++b) {
        if (d[a][v] != kInf && d[v][b] != kInf) {
          d[a][b] = min(d[a][b], d[a][v] + d[v][b]);
        }
      }
    }
  }

  unsigned long long minimal_sum = kInf;
  unsigned long long answer = kInf;
  for (unsigned long long i = 0; i < n; ++i) {
    unsigned long long sum = 0;
    for (unsigned long long j = 0; j < n; ++j) {
      sum += d[i][j];
    }
    if (sum < minimal_sum) {
      minimal_sum = sum;
      answer = i;
    }
  }

  if (answer == kInf) {
    cout << -1;
  } else {
    cout << answer + 1;
  }

  return 0;
}
