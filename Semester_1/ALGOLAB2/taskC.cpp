#include <iostream>

using namespace std;

void QquickSort(int arr[], int length) {
    if (length < 2)
        return;

    int pivot = arr[length / 2];

    int i = 0, j = length - 1;

    while (i <= j) {
        while (arr[i] > pivot)
            i++;
        while (arr[j] < pivot)
            j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (j > 0)
        QquickSort(arr, j + 1);

    if (i < length)
        QquickSort(arr + i, length - i);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    QquickSort(a, n);
    int j = 0;
    long long side_by_side = 1;
    long long total = 0;
    long long count = 0;

    while (j < n) {
        if (a[j] == a[j + 1]) {
            side_by_side *= a[j];
            count += 1;
            j += 2;
        } else if (a[j] - 1 == a[j + 1]) {
            side_by_side *= a[j + 1];
            count += 1;
            j += 2;
        } else
            j += 1;
        if (count == 2) {
            count = 0;
            total += side_by_side;
            side_by_side = 1;
        }
    }
    cout << (total);
    return 0;
}
