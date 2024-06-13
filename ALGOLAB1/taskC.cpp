#include <iostream>

using namespace std;

int main() {
  int a, b;
  cin >> b >> a;
  while (b != a) {
    if (b > a) {
      b -= a;
    } else {
      a -= b;
    }
  }
  cout << b;
}