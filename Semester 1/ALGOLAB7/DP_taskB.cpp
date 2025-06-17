#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int nvp_dlinna(vector<int>& array) {
  int n = array.size();
  if (n == 0) return 0;
  vector<int> dp(n, 0); // dp[i] хранит конец НВП длины i+1
  int res_len = 1; // текущая длина НВП
  dp[0] = array[0];
  for (int i = 1; i < n; ++i) {
    if (array[i] < dp[0]) {
      // Новый элемент меньше всех, обновляем начало НВП
      dp[0] = array[i];
    } else if (array[i] > dp[res_len - 1]) {
      // Новый элемент больше всех, продлеваем НВП
      dp[res_len++] = array[i];
    } else {
      // Ищем бинарным поиском наименьший элемент, который больше array[i]
      int pos = lower_bound(dp.begin(), dp.begin() + res_len, array[i]) - dp.begin();
      dp[pos] = array[i];
    }
  }

  return res_len;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }
  cout << nvp_dlinna(arr);
  return 0;
}
