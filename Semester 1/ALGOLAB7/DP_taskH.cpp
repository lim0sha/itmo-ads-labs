#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int rows, columns;
  cin >> rows >> columns;

  vector<int> Padding_array(columns + 1);

  int x = 0, y = 0, total_lenght = 0;
  int current_element, prev_element = 0;
  string stroka;
  for (int i = 1; i <= rows; ++i) {
    cin >> stroka;
    for (int j = 1; j <= columns; ++j) {
      current_element = Padding_array[j];
      if (stroka[j - 1] == '5') {
        Padding_array[j] = std::min(std::min(Padding_array[j - 1], prev_element), Padding_array[j]) + 1;
        if (Padding_array[j] > total_lenght) {
          total_lenght = Padding_array[j];
          x = i - total_lenght + 1;
          y = j - total_lenght + 1;
        } else if (total_lenght == Padding_array[j]) {
          x = i - total_lenght + 1;
          y = j - total_lenght + 1;
        }
      } else {
        Padding_array[j] = 0;
      }
      prev_element = current_element;
    }
  }

  cout << total_lenght;
  cout << " " << x << " " << y;
  return 0;
}
