#include <iostream>
using namespace std;


void counting_sort(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int count[max + 1];
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    int j = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[j] = i;
            j++;
            count[i]--;
        }
    }
}
int main() {
    int n;
    cin >> n;
    int a[n];
    int maximum = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] += i;
        if (a[i] > maximum) {
            maximum = a[i];
        }
    }

    counting_sort(a, n);
    maximum += 1;
    int duplicates[maximum];
    for (int i = 0; i < maximum; i++) {
        duplicates[i] = 1;
    }

    for (int j = 0; j < n; j++) {
        if (duplicates[a[j]] == 1) {
            duplicates[a[j]] = 0;
        } else {
            cout << ":(";
            return 0;
        }
    }

    for (int k = 0; k < n; ++k) {
        cout << a[k] - k << " ";
    }
    return 0;
}
