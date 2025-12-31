#include <iostream>

using namespace std;

struct Node {
  long long data;
  [[maybe_unused]] Node *next;
  Node *prev;
};

struct Queue {
 private:
  Node *front_;
  Node *back_;

 public:
  void push_back(long long x) {
    Node *node = new Node;
    node->data = x;
    node->next = nullptr;
    node->prev = back_;

    if (back_ != nullptr) {
      back_->next = node;
    }

    if (front_ == nullptr) {
      front_ = node;
    }

    back_ = node;
  }

  long long back() const {
    return back_->data;
  }

  void pop_back() {
    if (back_ == nullptr) {
      return;
    }

    Node *temp = back_;
    back_ = back_->prev;

    if (back_ != nullptr) {
      back_->next = nullptr;
    }

    if (front_ == temp) {
      front_ = nullptr;
    }

    delete temp;
  }
};

int main() {
  Queue sequence{};
  char symbol;
  long long total;
  while (cin >> symbol) {
    if (symbol == '\n') {
      break;
    }
    if (symbol != '+' and symbol != '-' and symbol != '*') {
      int ia = symbol - '0';
      sequence.push_back(ia);
    } else if (symbol == '-') {
      total = sequence.back();
      sequence.pop_back();
      total -= sequence.back();
      sequence.pop_back();
      sequence.push_back(-total);
    } else if (symbol == '*') {
      total = sequence.back();
      sequence.pop_back();
      total *= sequence.back();
      sequence.pop_back();
      sequence.push_back(total);
    } else {
      total = sequence.back();
      sequence.pop_back();
      total += sequence.back();
      sequence.pop_back();
      sequence.push_back(total);
    }
    cout << sequence.back() << "\n";
  }
  cout << sequence.back() << "\n";
  return 0;
}
