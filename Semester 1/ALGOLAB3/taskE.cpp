#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Node {
 public:
  int data;
  Node *next;
};

struct Stack {
 private:
  Node *top;
 public:
  Stack() : top(nullptr) {}

  void push_back(int value) {
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = top;
    top = newNode;
  }

  void pop_back() {
    if (top == nullptr) {
      return;
    }
    Node *temp = top;
    top = top->next;
    delete temp;
  }

  int back() {
    if (top == nullptr) {
      return -1;
    }
    return top->data;
  }

  ~Stack() {
    while (top != nullptr) {
      Node *temp = top;
      top = top->next;
      delete temp;
    }
  }
};

int Rev(int value) {
  int revs180 = 0;
  while (value != 0) {
    int digit = value % 10;
    revs180 = revs180 * 10 + digit;
    value /= 10;
  }
  return revs180;
}

bool NotACoeff(string str, int i) {
  if ((str[i + 1] > '9' || str[i + 1] == '(' || str[i + 1] == ')') || (i == str.size() - 1)) {
    return true;
  }
  return false;
}

bool IsCoeff(string str, int i) {
  if (str[i] >= '0' && str[i] <= '9') {
    return true;
  }
  return false;
}

bool CoeffAfterBraces(string str, int i) {
  if (!(str[i + 1] >= '0' && str[i + 1] <= '9')) {
    return true;
  }
  return false;
}

bool IsBraces(string str, int i) {
  if (str[i] == '(' || str[i] == ')') {
    return true;
  }
  return false;
}

bool CoeffToReverse(string str, int i) {
  if (!(str[i - 1] >= '0' && str[i - 1] <= '9')) {
    return true;
  }
  return false;
}

void Printfunction(long long *array) {
  for (int k = 0; k < 26; ++k) { // 26 англ букв
    if (array[k] != 0) {
      // коэфф не пустой - выводим букву
      cout << static_cast<char>(65 + k); // 65 - код буквы А в аски
      if (array[k] != 1) {
        // коэфф после элемента
        cout << array[k];
      }
    }
  }
}

int main() {
  Stack coefficents;
  string s;
  cin >> s;
  int nested = 1;
  long long letters[26]; // 26 англ букв
  for (int i = 0; i < 26; ++i) {
    letters[i] = 0;
  }
  int value = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    // символ - коэфф
    if (IsCoeff(s, i)) {
      value *= 10;
      value += static_cast<int>(s[i] - 48); // 48 - код нуля в аски
      if (CoeffToReverse(s, i)) {
        value = Rev(value);
        coefficents.push_back(value);
        value = 0;
      }
      // символ - скобка "(" или ")"
    } else if (IsBraces(s, i)) {
      if (s[i] == ')') {
        if (CoeffAfterBraces(s, i)) {
          // коэфф после скобок равен 1
          coefficents.push_back(1);
        }
        nested += 1;
      } else {
        // скобка открылась - удаляем ласт коэфф
        coefficents.pop_back();
        nested -= 1;
      }
      // иначе символ - буква
    } else {
      if (NotACoeff(s, i)) {
        // это буква - коэфф = 1
        coefficents.push_back(1);
      }
      // кол-во вложенных уровней коэфф-в для перемножения
      int nestedCoeffs[nested];
      // для вложенных коэфф-в
      long long coeffproduct = 1;
      for (int k = 0; k < nested; ++k) {
        // перемножаем вложенные коэфф-ты
        coeffproduct = coeffproduct * coefficents.back();
        nestedCoeffs[k] = coefficents.back();
        coefficents.pop_back();
      }
      for (int j = nested - 1; j > 0; --j) {
        coefficents.push_back(nestedCoeffs[j]);
      }
      // закидываем в массив букв коды букв по аски
      letters[static_cast<int>(s[i] - 65)] += coeffproduct; // 65 - код буквы А в аски
    }
  }
  // вывод
  Printfunction(letters);
  return 0;
}