#include <iostream>

using namespace std;

int main() {

  int n;
  cin >> n;
  int mas[n + 1];
  bool flag = true;

  for (int i = 1; i < n + 1; ++i) {
    cin >> mas[i];
  }

  for (int i = 1; i < n / 2; ++i) {
    if ((2 * i > n) or (mas[i] > mas[2 * i])) {
      flag = false;
    }
    if (((2 * i) + 1 > n) or (mas[i] > mas[(2 * i) + 1])) {
      flag = false;
    }
  }

  if (flag) {
    cout << "YES";
  } else {
    cout << "NO";
  }
  return 0;
}