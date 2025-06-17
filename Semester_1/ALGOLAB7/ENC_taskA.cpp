#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void Print_Gray_Codes(int n) {
  vector<string> main_array;
  main_array.emplace_back("0");
  main_array.emplace_back("1");
  int i;
  int k;
  for (i = 2; i < (1 << n); i = i << 1) {
    for (k = i - 1; k >= 0; --k)
      main_array.push_back(main_array[k]);
    for (k = 0; k < i; ++k)
      main_array[k] = '0' + main_array[k];
    for (k = i; k < 2 * i; ++k)
      main_array[k] = '1' + main_array[k];
  }
  for (const auto &element : main_array)
    cout << element << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  Print_Gray_Codes(n);
  return 0;
}