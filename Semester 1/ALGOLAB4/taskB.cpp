#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

void SiftDown(vector<int> &array, int n, long size) {
  while (2 * n + 1 < size) {
    // левый деть
    long left = 2 * n + 1;
    // правый деть
    long right = 2 * n + 2;
    long j = left;
    if (right < size && array[right] < array[left]) {
      j = right;
    }
    if (array[j] >= array[n]) {
      break;
    }
    swap(array[j], array[n]);
    n = j;
  }
}

void CreateMinHeap(vector<int> &array, long size) {
  for (int i = (size / 2); i >= 0; i--) {
    // просеили массив
    SiftDown(array, i, size);
  }
}

struct PriorutyQueue {
  vector<int> arr;
  void create() {
    CreateMinHeap(arr, arr.size());
  }

  void insert(int x_element) {
    if (arr.empty()) {
      // добавили в пустой массив
      arr.push_back(x_element);
    } else {
      arr.push_back(x_element);
      // добавили, сделали кучей
      CreateMinHeap(arr, arr.size());
    }
  }

  void extract_min() {
    if (arr.empty()) {
      cout << "*" << "\n";
    } else {
      cout << arr[0] << "\n";
      swap(arr[0], arr[arr.size() - 1]);
      arr.pop_back();
      CreateMinHeap(arr, arr.size());
    }
  }

  void decrease_key(int &x_element, int &y_element) {
    for (int &i : arr) {
      if (x_element == i) {
        i = y_element;
        CreateMinHeap(arr, arr.size());
        break;
      }
    }
  }

  void merge(vector<int> &array_1, vector<int> &array_2) {
    for (int i : array_1) {
      arr.push_back(i);
    }
    for (int i : array_2) {
      arr.push_back(i);
    }
    CreateMinHeap(arr, arr.size());
  }
};

int main() {
  vector<vector<int>> all_queues;
  PriorutyQueue temp_PQ;
  ios::sync_with_stdio(0);
  cin.tie(0);
  while (cin) {
    string command;
    int k, x, y, m;
    //std::getline(cin, command);
    cin >> command;
    if (command[0] == 'c') {
      k = -1;
      x = -1;
      y = -1;
      m = -1;
      PriorutyQueue newPQ;
      newPQ.create();
      all_queues.push_back(newPQ.arr);
    }
    if (command[0] == 'i') {
      cin >> k >> x;
      y = -1;
      m = -1;
      temp_PQ.arr = all_queues[k];
      temp_PQ.insert(x);
      all_queues[k] = temp_PQ.arr;
    }
    if (command[0] == 'e') {
      cin >> k;
      x = -1;
      y = -1;
      m = -1;
      temp_PQ.arr = all_queues[k];
      temp_PQ.extract_min();
      all_queues[k] = temp_PQ.arr;
    }
    if (command[0] == 'm') {
      cin >> k >> m;
      x = -1;
      y = -1;
      PriorutyQueue PQ_merge_1;
      PriorutyQueue PQ_merge_2;
      PriorutyQueue PQ_merged;
      PQ_merge_1.arr = all_queues[k];
      PQ_merge_2.arr = all_queues[m];
      PQ_merged.merge(PQ_merge_1.arr, PQ_merge_2.arr);
      all_queues.push_back(PQ_merged.arr);
    }
    if (command[0] == 'd') {
      cin >> k >> x >> y;
      m = -1;
      temp_PQ.arr = all_queues[k];
      temp_PQ.decrease_key(x, y);
      all_queues[k] = temp_PQ.arr;
    }
  }
  return 0;
}