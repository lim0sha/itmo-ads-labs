#include <iostream>
#include <string>

using namespace std;

int main() {
  int t, n, s;
  string q;
  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> n;
    int votes[n];
    int minimum = 15;
    int maximum = 30;
    for (int j = 0; j < n; j++) {
      cin >> q >> s;
      votes[j] = s;
      if (q == ">=" and minimum < s) {
        minimum = s;
      }
      if (q == "<=" and maximum > s) {
        maximum = s;
      }
      if (minimum <= s <= maximum and maximum >= minimum) {
        cout << minimum << "\n";
      } else {
        cout << -1 << "\n";
      }
    }
  }
  return 0;
}
