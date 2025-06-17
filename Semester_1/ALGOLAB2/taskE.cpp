#include <iostream>

using namespace std;

long long mergeSort(int arr[], int begin, int end) {
    if (begin >= end) {
        return 0;
    }

    int mid = begin + (end - begin) / 2;
    long long inversions = mergeSort(arr, begin, mid) + mergeSort(arr, mid + 1, end);
    int temp[end - begin + 1];
    int i = begin, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= end) {
        temp[k++] = arr[j++];
    }

    for (int i = begin; i <= end; ++i) {
        arr[i] = temp[i - begin];
    }

    return inversions;
}

long long countInversions(int arr[], int n) {
    return mergeSort(arr, 0, n - 1);
}

int main() {
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    long long inversions = countInversions(arr, n);
    cout << inversions << endl;
    return 0;
}