#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Node {
    int data;
    Node *next;
};

class Queue {
private:
    Node *head;
    Node *tail;

public:
    Queue() {
        head = NULL;
        tail = NULL;
    }

    void enqueue(int data) {
        Node *new_node = new Node();
        new_node->data = data;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    int dequeue() {
        if (head == NULL) {
            return -1;
        } else {
            int data = head->data;
            Node *temp = head;
            head = head->next;
            delete temp;
            return data;
        }
    }

    int front() {
        if (head == NULL) {
            return -1;
        } else {
            return head->data;
        }
    }
};

int main() {
    int n;
    cin >> n;
    Queue q;
    std::list<int> answers;
    string oper, value;
    int int_value;
    for (int i = 0; i < n; ++i) {
        cin >> oper;
        if (oper == "+") {
            cin >> value;
            int_value = stoi(value);
            q.enqueue(int_value);
        }
        if (oper == "-") {
            answers.push_back(q.front());
            q.dequeue();
        }
    }

    for (auto v : answers)
        std::cout << v << "\n";
    return 0;
}