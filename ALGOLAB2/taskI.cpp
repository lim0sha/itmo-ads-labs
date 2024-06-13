#include <iostream>
using namespace std;

int Qqsort(int arr[], int left, int right, int k_th) {
    while (right > left) {
        int i = left;
        int j = right;
        int x = arr[k_th];
        while (i <= j) {
            while (arr[i] < x) {
                i += 1;
            }
            while (arr[j] > x) {
                j -= 1;
            }
            if (i <= j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i += 1;
                j -= 1;
            }
        }
        if (k_th < i) {
            right = j;
        }
        if (j < k_th) {
            left = i;
        }
    }
    return arr[k_th];
}

int main() {
    int n, k;
    cin >> n >> k;
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int A = a[0];
    int B = a[1];
    int C = a[2];
    int c[n];
    c[0] = a[3];
    c[1] = a[4];
    long long ans = 0;
    delete[] a;
    a = nullptr;
    for (int i = 2; i < n; i++) {
        c[i] = c[i - 2] * A + c[i - 1] * B + C;
    }

    int kth = Qqsort(c, 0, n - 1, n - k);
    for (int i = n - 1; i >= n - k; i--) {
        if (kth <= c[i]) {
            ans ^= c[i];
        }
    }
    cout << ans;
    return 0;
}