#include <iostream>

using namespace std;

void QsortRecursive(int *mas, int size) {
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

int main() {
    long long n;
    cin >> n;
    int durations[n];
    int timeisover[n];
    for (long long i = 0; i < n; ++i) {
        cin >> durations[i] >> timeisover[i];
    }
    QsortRecursive(durations, n);
    QsortRecursive(timeisover, n);
    long long day = 0;
    long long summa = 0;
    for (long long i = 0; i < n; ++i) {
        day += durations[i];
        summa += timeisover[i] - day;
    }
    cout << summa;
}