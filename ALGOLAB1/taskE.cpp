#include <iostream>
#include <string>

using namespace std;

int main() {
  int n, mist;
  cin >> n;
  string s;
  char a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int i = 0;
  mist = 0;
  while (i < (n / 2)) {
    if (a[i] != a[n - i - 1] and mist == 0) {
      mist += 1;
    }
    if (mist == 1) {
      if (a[i] != a[n - i - 2] and a[i + 1] != a[n - i - 1]) {
        mist += 1;
      }
    }
    if (mist == 2) {
      break;
    }
    ++i;
  }
  if (mist == 2) {
    cout << "NO" << "\n";
  } else {
    cout << "YES" << "\n";
  }
  return 0;
}
