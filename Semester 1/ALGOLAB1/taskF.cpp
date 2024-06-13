#include <iostream>

using namespace std;

int main() {

  int n, mainSum = 0;

  bool flag = true;
  cin >> n;
  int numbers[n];
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  for (int i = 0; i < n; i++) {
    mainSum += numbers[i];
  }

  int sumsLeft;
  int sumsRight;
  sumsLeft = 0;
  sumsRight = mainSum;

  for (int i = 0; i < n; i++) {
    if (i == 0) {
      sumsLeft = 0;
      sumsRight = mainSum - numbers[i];
    }

    if (i == n - 1) {
      sumsLeft = mainSum - numbers[i];
      sumsRight = 0;
    }

    if (i != 0 and i != n - 1) {
      sumsLeft += numbers[i - 1];
      sumsRight -= numbers[i];
    }

    if (sumsLeft == sumsRight) {
      cout << i;
      flag = false;
      break;
    }
  }
  if (flag) {
    cout << -1;
  }
  return 0;
}