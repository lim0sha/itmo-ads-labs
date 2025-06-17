#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  long long rows, columns;
  cin >> rows >> columns;

  vector<string> array(rows);
  for (auto &row : array) {
    cin >> row;
  }

  vector<vector<long long>> Padding_array(rows + 1, vector<long long>(columns + 1));

  long long x = 0;
  long long y = 0;
  long long total_length = 0;

  for (long long i = rows - 1; i >= 0; --i) {
    for (long long j = columns - 1; j >= 0; --j) {
      if (array[i][j] == '5') {
        Padding_array[i][j] = std::min({Padding_array[i + 1][j], Padding_array[i][j + 1], Padding_array[i + 1][j + 1]}) + 1;
        if (Padding_array[i][j] > total_length) {
          total_length = Padding_array[i][j];
          x = i + 1;
          y = j + 1;
        }
      }
    }
  }

  cout << total_length;
  cout << " " << x << " " << y;
  return 0;
}
