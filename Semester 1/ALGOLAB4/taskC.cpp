#include <iostream>
#include <queue>
#include <vector>

struct Order {
  long salary;
  long start_time;
  Order(long s, long st) : salary(s), start_time(st) {}
};

class PriorityQueue {
 private:
  std::priority_queue<std::pair<long, long>, std::vector<std::pair<long, long>>, std::greater<>> not_on_order;
  std::priority_queue<std::pair<long, long>, std::vector<std::pair<long, long>>, std::greater<>> on_order;

 public:
  void addOrder(Order order) {
    not_on_order.emplace(order.salary, order.start_time);
  }

  void processOrders(int current_time) {
    while (!on_order.empty() && on_order.top().first <= current_time) {
      not_on_order.emplace(on_order.top().second, on_order.top().first);
      on_order.pop();
    }
  }

  bool hasPendingOrders() const {
    return !not_on_order.empty();
  }

  long processNextOrder(int order_time, int current_time) {
    long total = 0;
    if (!not_on_order.empty()) {
      total = not_on_order.top().first * order_time;
      long summary = current_time + order_time;
      on_order.emplace(summary, not_on_order.top().first);
      not_on_order.pop();
    }
    return total;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  PriorityQueue priorityQueue;

  for (int i = 0; i < n; ++i) {
    long salary;
    std::cin >> salary;
    priorityQueue.addOrder(Order(salary, 0));
  }

  int order_start, order_time;
  long total = 0;

  for (int i = 0; i < m; ++i) {
    std::cin >> order_start >> order_time;
    priorityQueue.processOrders(order_start);
    if (priorityQueue.hasPendingOrders()) {
      total += priorityQueue.processNextOrder(order_time, order_start);
    }
  }
  std::cout << total << "\n";

  return 0;
}
