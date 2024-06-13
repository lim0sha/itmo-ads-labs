#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

void QsortRecursive(long *mas, long size) {
  long i = 0;
  long j = size - 1;
  long mid = mas[size / 2];
  do {
    while (mas[i] < mid) {
      i++;
    }
    while (mas[j] > mid) {
      j--;
    }
    if (i <= j) {
      int tmp = mas[i];
      mas[i] = mas[j];
      mas[j] = tmp;
      i++;
      j--;
    }
  } while (i <= j);
  if (j > 0) {
    QsortRecursive(mas, j + 1);
  }
  if (i < size) {
    QsortRecursive(&mas[i], size - i);
  }
}

long checkHowManyAreNotGreater(long const *men, long const *women, long n, long end, long sum_n) {
  int j = end, i;
  long c;
  c = 0;
  for (i = 0; i < n; i++) {
    while ((j >= 0) and (sum_n < men[i] + women[j])) {
      j -= 1;
    }
    c = c + j + 1;
  }
  return c;
}

long Binraysrch(const long *men, long const *women, long great, long small, long n, long k, long end) {
  while (great > small) {
    long middle = small + (great - small) / 2;
    if (checkHowManyAreNotGreater(men, women, n, end, middle) < k) {
      small = middle + 1;
    } else {
      great = middle;
    }
  }
  return small;
}

int main() {
  long n, k;
  cin >> n >> k;
  long end = n - 1;
  auto *women = new long[n];
  auto *men = new long[n];
  for (long long i = 0; i < n; ++i) {
    cin >> women[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> men[i];
  }

  QsortRecursive(men, n);
  QsortRecursive(women, n);

  long smallest = women[0] + men[0];
  long greatest = women[end] + men[end];

  long ans = Binraysrch(men, women, greatest, smallest, n, k, end);
  cout << ans;

  return 0;
}
