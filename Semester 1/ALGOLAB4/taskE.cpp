#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// преобразоване в двоичную кучу поддерева с корневым узлом i

void Heapify(int* array, int size, int index) {

  int largest = index;
  // Инициализируем наибольший элемент как корень
  int l = 2 * index + 1; // левый = 2 * index + 1
  int r = 2 * index + 2; // правый = 2 * index + 2

  // левый больше корня
  if (l < size and array[l] > array[largest]) {
    largest = l;
  }

  // правый больше, чем самый большой элемент на данный момент
  if (r < size and array[r] > array[largest]) {
    largest = r;
  }

  // самый большой элемент не корень
  if (largest != index) {
    swap(array[index], array[largest]);
    // преобразуем в двоичную кучу затронутое поддерево
    Heapify(array, size, largest);
  }
}

// Основная функция, выполняющая пирамидальную сортировку
void HeapSort(int* array, int size) {
  // Построение кучи (перегруппируем массив)
  for (int i = size / 2 - 1; i >= 0; i--)
    Heapify(array, size, i);

  // Один за другим извлекаем элементы из кучи
  for (int i = size - 1; i >= 0; i--) {
    // Перемещаем текущий корень в конец
    swap(array[0], array[i]);

    // вызываем Heapify на уменьшенной куче
    Heapify(array, i, 0);
  }
}

int main() {
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  HeapSort(arr, n);

  for (int i = 0; i < n; ++i)
    cout << arr[i] << " ";
}