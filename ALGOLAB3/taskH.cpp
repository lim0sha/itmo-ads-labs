#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Node {
 public:
  int x_coordinate;
  int height;
  Node *next;
};

struct Stack {
 private:
  Node *top;
 public:
  Stack() : top(nullptr) {}

  static Node *make_new_node(int new_x_coordinate, int new_height) {
    Node *newNode = new Node;
    newNode->x_coordinate = new_x_coordinate;
    newNode->height = new_height;
    newNode->next = NULL;
    return newNode;
  }

  void push_up(int x_coordinate, int height) {
    Node *newNode = make_new_node(x_coordinate, height);
    if (top == NULL)
      top = newNode;
    else {
      newNode->next = top;
      top = newNode;
    }
  }

  void pop() {
    Node *temp = top;
    top = top->next;
    delete temp;
  }

  int top_height() {
    return top->height;
  }

  int top_coordinate_x() {
    return top->x_coordinate;
  }
};

int main() {

  Stack Sticks;
  // нулевой прямоугольник никогда не будет удален со стека
  Sticks.push_up(0, -1);

  long long  n;
  cin >> n;
  long long a[n];
  // считываем палки
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  long long  stick_height;
  long long  total = 0; // total - максимально покрывающий прямоугольник

  // последовательно обрабатываем палки
  for (int i = 0; i <= n; ++i) {
    if (i < n) {
      stick_height = a[i];
    } else {
      // палки закончились
      stick_height = 0;
    }
    // порядковый номер палки
    int x_coordinate = i;
    // выталкиваем все прямоугольники из стека кроме первого с высотой -1 и пересчитываем площадь
    while (Sticks.top_height() >= stick_height) {
      x_coordinate = Sticks.top_coordinate_x();
      // верхняя добавленная палка
      long long  top_temporary = Sticks.top_height();
      Sticks.pop();
      // max площадь
      total = max(total, top_temporary * (i - x_coordinate));
    }
    long long  higher = Sticks.top_height();
    // тк высота идет по возрастающей то пока добавляем палки в стек
    if (higher < stick_height) {
      Sticks.push_up(x_coordinate, stick_height);
    }
  }
  cout << total;
  return 0;
}