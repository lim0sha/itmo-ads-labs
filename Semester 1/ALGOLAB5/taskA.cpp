#include <iostream>
#include <algorithm>

using namespace std;

void preorder_print(int left, int right, int array[]) {
  if (left == right) {
    return;
  }
  int n = (left + right - 1) / 2;
  cout << array[n] << " ";
  preorder_print(left, n, array);
  preorder_print(n + 1, right, array);
}

int main() {
  int n;
  cin >> n;
  int elements[n];
  for (int i = 0; i < n; ++i) {
    cin >> elements[i];
  }

  preorder_print(0, n, elements);
  return 0;
}
