#include <iostream>
#include <vector>
#include <algorithm>


void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
  }
}


int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> seats(n);
  for (int i = 0; i < n; i++) {
    std::cin >> seats[i];
  }

  mergeSort(seats, 0, n-1);

  int l = 0, r = seats.back() - seats.front() + 1;
  while (l < r) {
    int mid = (l + r) / 2;
    int boyars = 1;
    int last = seats[0];
    for (int i = 1; i < n; i++) {
      if (seats[i] - last > mid) {
        ++boyars;
        last = seats[i];
      }
    }
    if (boyars >= k) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  std::cout << l << std::endl;

  return 0;
}