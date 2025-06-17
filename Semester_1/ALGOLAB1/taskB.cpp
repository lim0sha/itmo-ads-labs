#include <iostream>

using namespace std;

int main() {
  long long n, k, temp;
  cin >> n >> k;
  long long array[n];

  for (int i = 0; i < n; i++) {
    cin >> array[i];
  }
  if (abs(k) >= n) {
    k = k % n;
  }
  if (k < 0) {
    k = n - abs(k);
  }
  // cout << k << endl;
  for (int i = 0; i < k; i++) {
    temp = array[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      array[i + 1] = array[i];
    }
    array[0] = temp;
  }
  for (int i = 0; i < n; i++) {
    cout << array[i] << " ";
  }
  return 0;
}