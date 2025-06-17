#include <iostream>
#include <list>
#include <string>
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
    int n, m;
    cin >> n >> m;
    list<int> bag;
    int treasure;
    int taken[3];
    int to_add1, to_add2;
    int founded[n];
    for (int i = 0; i < n; ++i) {
        cin >> founded[i];
    }
    for (int i = 0; i < n; ++i) {
        treasure = founded[i];
        if (bag.size() < m) {
            bag.push_back(treasure);
        } else {
            taken[0] = treasure;
            taken[1] = bag.front();
            bag.pop_front();
            taken[2] = bag.back();
            bag.pop_back();
            QquickSort(taken, 3);
            to_add1 = taken[0];
            to_add2 = taken[1];
            bag.push_back(to_add2);
            bag.push_back(to_add1);
        }
    }
    for (auto v : bag)
        std::cout << v << " ";
    return 0;
}