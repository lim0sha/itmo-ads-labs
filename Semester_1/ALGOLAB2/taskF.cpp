#include <iostream>

using namespace std;

void merge(long long arr1[], long long arr2[], long long left, long long mid, long long right) {
    int sorting1[right - left];
    int sorting2[right - left];

    int i = 0;
    int j = 0;
    while (left + i < mid and j + mid < right) {
        if (arr1[left + i] < arr1[mid + j]) {
            sorting1[i + j] = arr1[mid + j];
            sorting2[i + j] = arr2[mid + j];
            j += 1;
        } else {
            sorting1[i + j] = arr1[left + i];
            sorting2[i + j] = arr2[left + i];
            i += 1;
        }
    }
    while (mid > left + i) {
        sorting1[i + j] = arr1[left + i];
        sorting2[i + j] = arr2[left + i];
        i += 1;
    }
    while (right > mid + j) {
        sorting1[i + j] = arr1[mid + j];
        sorting2[i + j] = arr2[mid + j];
        j += 1;
    }
    for (int p = 0; p < i + j; p++) {
        arr1[left + p] = sorting1[p];
        arr2[left + p] = sorting2[p];
    }
}
void mergeSort(long long arr1[], long long arr2[], long long left, long long right) {
    long long middle;

    if (left >= right - 1)
        return;
    middle = (right + left) / 2;
    mergeSort(arr1, arr2, left, middle);
    mergeSort(arr1, arr2, middle, right);
    merge(arr1, arr2, left, middle, right);
}
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    long long tens = 1000000000 + 7;

    long long coeffs_a[n];
    long long votes[m];
    long long indexes[m];
    long long values[m][n];

    for (int i = 0; i < n; i++) {
        cin >> coeffs_a[i];
    }
    for (int i = 0; i < m; i++) {
        indexes[i] = i + 1;
    }

    for (int i = 0; i < m; ++i) {
        long long value_4_film = 0;
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            values[i][j] = x;
            value_4_film = value_4_film + coeffs_a[j] * values[i][j];
        }
        votes[i] = value_4_film % tens;
    }

    mergeSort(votes, indexes, 0, m);

    //for (int i = 0; i < m; ++i) {
    //    cout << votes[i] << " " << indexes[i] << "\n";
    //}

    for (int t = 0; t < k; ++t) {
        cout << indexes[t] << " ";
    }
    return 0;
}