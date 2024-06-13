#include <iostream>

using namespace std;

void QsortRecursive(int *mas, int size) {
    long i = 0;
    long j = size - 1;
    long mid = mas[size / 2];
    //Делим массив
    do {
        while (mas[i] < mid) {
            i++;
        }
        while (mas[j] > mid) {
            j--;
        }
        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    //Рекурсивные вызовы, если осталось что сортировать
    if (j > 0) {
        //Левый кусок
        QsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //Правый кусок
        QsortRecursive(&mas[i], size - i);
    }
}


int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    QsortRecursive(a, n);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}