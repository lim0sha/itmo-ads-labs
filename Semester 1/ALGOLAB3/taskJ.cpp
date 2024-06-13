#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Hero {
  int damage;
  string name;
};

void StableCountingSort(Hero *array, int array_size, int *arr, int max) {

  Hero additions_prefix_array[array_size];
  int tmp[max];
  for (int i = 0; i < max; ++i) {
    tmp[i] = 0;
  }

  for (int i = 0; i < array_size; i++) {
    tmp[(array[i].damage)] += 1;
  }

  for (int i = 0; i < max; ++i) {
    arr[i] = tmp[i];
  }

  for (int i = 1; i < max; ++i) {
    tmp[i] += tmp[i - 1];
  }

  for (int i = 0; i < max; ++i) {
    tmp[i] -= 1;
  }

  for (int i = array_size - 1; i >= 0; i--) {
    additions_prefix_array[tmp[(array[i].damage)]--] = array[i];
  }

  for (int i = 0; i < array_size; i++) {
    array[i] = additions_prefix_array[i];
  }
}

int main() {

  int n;
  cin >> n;

  Hero arr[n];

  for (int i = 0; i < n; ++i) {
    int temp = 0;
    cin >> temp;
    arr[i].damage = temp;
  }
  for (int i = 0; i < n; ++i) {
    string temp;
    cin >> temp;
    arr[i].name = temp;
  }

  long long maximum = -1;
  for (int i = 0; i < n; ++i) {
    if (maximum < arr[i].damage) {
      maximum = arr[i].damage;
    }
  }
  maximum += 1;
  int temporary_arr[maximum + 1];

  StableCountingSort(arr, n, temporary_arr, maximum);

  for (int i = 0; i < n; ++i) {
    cout << arr[i].damage;
    if (i < n - 1) {
      cout << " ";
    } else {
      cout << "\n";
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << arr[i].name;
    if (i < n - 1) {
      cout << " ";
    } else {
      cout << "\n";
    }
  }

  int prefix_counts[maximum];
  for (int i = 0; i < maximum; ++i) {
    prefix_counts[i] = temporary_arr[i];
  }
  for (int i = 1; i < maximum; ++i) {
    prefix_counts[i] += prefix_counts[i - 1];
  }

  long long prefix_sums[maximum];
  prefix_sums[0] = temporary_arr[0];
  for (int i = 1; i < maximum; ++i) {
    prefix_sums[i] = prefix_sums[i - 1] + temporary_arr[i] * (i);
  }

  int prefix_xors[maximum];
  prefix_xors[0] = (temporary_arr[0] % 2);
  for (int i = 1; i < maximum; ++i) {
    prefix_xors[i] = prefix_xors[i - 1] ^ (i) * (temporary_arr[i] % 2);
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int left;
    int right;
    int xor_ans;
    string request;
    cin >> request >> left >> right;
    if (right > maximum - 1) {
      right = maximum - 1;
    }
    if (left > maximum - 1) {
      left = maximum - 1;
    }
    if (left < 0) {
      left = 0;
    }
    if (request[0] == 'C') {
      cout << prefix_counts[right] - prefix_counts[left - 1] << "\n";
    } else if (request[0] == 'S') {
      cout << prefix_sums[right] - prefix_sums[left - 1] << "\n";
    } else {
      xor_ans = prefix_xors[right] ^ (prefix_xors[left - 1]);
      cout << xor_ans << "\n";
    }
  }
}