#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Compare {
  vector<long> triple;

  bool operator<(const Compare& other) const {
    return triple[0] > other.triple[0];
  }
};

class PriorityQueue {
 public:
  priority_queue<Compare> minHeap;

  void push(const vector<long>& triple) {
    minHeap.push({triple});
  }

  Compare top() const {
    return minHeap.top();
  }

  void pop() {
    minHeap.pop();
  }

  bool empty() const {
    return minHeap.empty();
  }
};



void indexingPrimes(PriorityQueue& array, unsigned long long length) {
  vector<bool> prime(length + 1, true);
  for (long p = 2; p <= static_cast<long>(sqrt(length)) + 1; ++p) {
    if (prime[p]) {
      array.push({{p, 1, p}});
      for (uint64_t i = p * p; i <= length; i += p) {
        prime[i] = false;
      }
    }
  }
  for (long p = max(2ull, static_cast<unsigned long long>(sqrt(length)) + 1); p <= length; ++p) {
    if (prime[p]) {
      array.push({{p, 1, p}});
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  uint64_t n;
  cin >> n;

  uint64_t number = 0;
  uint64_t divisors = 1;
  PriorityQueue minHeap;
  indexingPrimes(minHeap, 4500000);

  while (true) {
    auto heapTopElement = minHeap.top();
    long twos_ = heapTopElement.triple[0];
    long count = heapTopElement.triple[1];
    long orig = heapTopElement.triple[2];
    minHeap.pop();
    minHeap.push({{twos_ * twos_, count * 2, orig}});
    divisors *= twos_ * twos_;
    number += 1;

    if (number == n) {
      vector<uint64_t> total;

      while (!minHeap.empty()) {
        Compare heapTopElement = minHeap.top();
        long second = heapTopElement.triple[1];
        long toAppend = heapTopElement.triple[2];
        minHeap.pop();

        for (long u = 1; u < second; ++u) {
          if (second % 2 != 0) {
            break;
          }
          total.push_back(toAppend);
        }
      }
      sort(total.begin(), total.end());
      cout << total.size() << "\n";
      for (unsigned long j : total) {
        cout << j << " ";
      }
      return 0;
    }
  }
}
