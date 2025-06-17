#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Node {
  // некст предыдущий значение и индекс в очереди
  Node *next = NULL;
  Node *prev = NULL;
  int value{};
  int position{};
};

struct QueueOnDoubleList {
 public:
  // начало и хвост
  Node *head{};
  Node *tail{};
  int size_ = 0;

  void pushback(const int n, const int newposition) {
    // новый узел
    Node *newNode = new Node;
    if (size_ != 0) {
      // вставка в непустую очередь
      newNode->value = n;
      newNode->position = newposition;
      newNode->prev = head;
      head->next = newNode;
      head = newNode;
    } else {
      // втсавка в пустую очередь
      head = newNode;
      head->value = n;
      head->position = newposition;
      tail = head;
    }
    size_ += 1;
  }
  void popback() {
    // удаление верхнего элемента
    if (head == tail) {
      head = tail = NULL;
    } else {
      head = head->prev;
    }
    size_ -= 1;
  }
  int headpos() const {
    // значение верхнего элемента
    return head->position;
  }
  int headvalue() const {
    // индекс верхнего элемента
    return head->value;
  }
  int queuesize() const {
    // размер очереди в текущий момент
    if (size_ == 0) {
      return 0;
    } else {
      return size_;
    }
  }
};

void PrintAns(int array[], int arraySize){
  for (int i = 0; i < arraySize; ++i) {
    if (array[i] == 0) {
      cout << -1 << " ";
    } else {
      cout << array[i] << " ";
    }
  }
}

int main() {
  int n;
  cin >> n;
  int days[n];
  int total[n];
  int i, k = 1;
  for ( i = 0; i < n; ++i) {
    total[i] = 0;
    cin >> days[i];
  }
  QueueOnDoubleList numbers;
  numbers.pushback(days[0], 0);
  for (;k < n; ++k) {
    while (!(numbers.queuesize() == 0) and (days[k] > numbers.headvalue())) {
      total[numbers.headpos()] = k - numbers.headpos();
      numbers.popback();
    }
    numbers.pushback(days[k], k);
  }
  PrintAns(total, n);
}