#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  vector<bool> two_degrees(1 << 16, false);
  for (auto i = 0; i <= 16; ++i) {
    two_degrees[(1 << i) - 1] = true;
  }

  int n;
  cin >> n;

  for (auto iter = 0; iter < n; ++iter) {
    string code;
    cin >> code;

    int mistake = 0;
    vector<int> counts_n(code.size(), 0);

    for (auto i = 0; i < code.size(); ++i) {
      int begin = 1 << i;
      if (begin - 1 >= code.length()) {
        break;
      }

      for (auto j = begin - 1; j < code.size(); j += 2 * begin) {
        for (auto k = j; k < j + begin and k < code.size(); ++k) {
          if (code[k] == '1') {
            ++counts_n[i];
          }
        }
      }

      counts_n[i] -= (code[begin - 1] == '1');

      if (counts_n[i] % 2 != (code[begin - 1] - '0')) {
        mistake += begin;
      }
    }

    for (auto i = 0; i < code.size(); ++i) {
      if (!two_degrees[i]) {
        if (mistake - 1 != i) {
          cout << code[i];
        } else {
          cout << (code[i] == '0' ? '1' : '0');
        }
      }
    }

    cout << "\n";
  }

  return 0;
}
