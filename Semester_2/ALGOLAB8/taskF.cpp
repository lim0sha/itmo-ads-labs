#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAX_SIZE = 100000;

struct Queue {
  int elements[MAX_SIZE];
  int front, back;
  unsigned int size;

  Queue() {
    front = 0;
    back = -1;
    size = 0;
  }

  bool isEmpty() {
    return size == 0;
  }

  bool isFull() {
    return size == MAX_SIZE;
  }

  void enqueue(int item) {
    if (!isFull()) {
      back = (back + 1) % MAX_SIZE;
      elements[back] = item;
      size++;
    }
  }

  int dequeue() {
    if (!isEmpty()) {
      int item = elements[front];
      front = (front + 1) % MAX_SIZE;
      size--;
      return item;
    }
    return numeric_limits<int>::min();
  }

  int peek() {
    if (!isEmpty()) {
      return elements[front];
    }
    return numeric_limits<int>::min();
  }
};

void bfs(const vector<vector<int>> &Gn, int begin_point, vector<int> &d_array) {
  Queue q;
  q.enqueue(begin_point);
  d_array[begin_point] = 0;
  while (!q.isEmpty()) {
    int v = q.dequeue();
    for (int i = 0; i < Gn[v].size(); ++i) {
      int to = Gn[v][i];
      if (d_array[to] == numeric_limits<int>::max()) {
        d_array[to] = d_array[v] + 1;
        q.enqueue(to);
      }
    }
  }
}

int main() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
  int n, m, k;
  bool have_ans = false;
  cin >> n >> m >> k;

  vector<vector<int>> adj_list(n);
  vector<int> d_array(n, numeric_limits<int>::max());

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj_list[a - 1].push_back(b - 1);
    adj_list[b - 1].push_back(a - 1);
  }

  bfs(adj_list, 0, d_array);

  for (int i = 0; i < n; ++i) {
    if (d_array[i] == k) {
      have_ans = true;
      cout << i + 1 << '\n';
    }
  }
  if (!have_ans) {
    cout << "NO";
  }

  return 0;
}
