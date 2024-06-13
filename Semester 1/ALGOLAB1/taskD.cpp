#include <iostream>

using namespace std;

int main() {
  long n, m, q, ep, season, k;
  cin >> n >> m >> q;
  int a[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = 0;
    }
  }
  k = 0;
  for (int i = 0; i < q; i++) {

    cin >> ep >> season;
    if (a[season - 1][ep - 1] != 1) {
      k = k + 1;
      a[season - 1][ep - 1] = 1;
    }
  }

  cout << n * m - k << "\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] != 1) {
        cout << j + 1 << " " << i + 1 << "\n";
      }
    }
  }

  return 0;
}