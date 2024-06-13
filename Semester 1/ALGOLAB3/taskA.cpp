#include <iostream>
#include <list>
using namespace std;

struct Node {
  int data;
  Node *next;
};

struct Stack {
 private:
  Node *top;

 public:
  Stack() { top = NULL; }

  void push(int data) {
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = top;
    top = newNode;
  }

  int pop() {
    if (top == NULL) {
      return -1;
    }

    int data = top->data;
    Node *temp = top;
    top = top->next;
    delete temp;
    return data;
  }

  int peek() {
    if (top == NULL) {
      return -1;
    }
    return top->data;
  }
};

int main() {
  int n;
  cin >> n;
  Stack s;
  int answers[n];
  int top = -1;

  string oper, value;
  int int_value;
  for (int i = 0; i < n; ++i) {
    cin >> oper;
    if (oper == "+") {
      cin >> value;
      int_value = stoi(value);
      s.push(int_value);
    }
    if (oper == "-") {
      top++;
      answers[top] = s.peek();
      s.pop();
    }
  }
  for (int i = 0; i <= top; i++)
    std::cout << answers[i] << "\n";
  return 0;
}