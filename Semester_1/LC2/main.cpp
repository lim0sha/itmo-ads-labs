#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node {
  long long data;
  Node* next = nullptr;
};

int DetectLoop(Node* head, vector<Node*>& loopNodes) {
  Node* current = head;
  unordered_set<Node*> visited;

  while (current != nullptr) {
    if (visited.find(current) != visited.end()) {
      // Detected a loop that is not a cycle
      auto it = find(loopNodes.begin(), loopNodes.end(), current);
      while (it != loopNodes.end()) {
        cout << "1\n";
        cout << (*it)->data << " ";
        ++it;
      }
      return loopNodes.size();
    }

    visited.insert(current);
    loopNodes.push_back(current);
    current = current->next;
  }

  return -1;
}

int Cycle(Node* head, vector<Node*>& cycleNodes) {
  Node* slow = head;
  Node* fast = head;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {
      Node* cycleStart = head;
      while (cycleStart != slow) {
        cycleStart = cycleStart->next;
        slow = slow->next;
      }

      Node* nodeInCycle = cycleStart;
      do {
        cycleNodes.push_back(nodeInCycle);
        nodeInCycle = nodeInCycle->next;
      } while (nodeInCycle != cycleStart);

      return cycleNodes.size();
    }
  }

  return DetectLoop(head, cycleNodes);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long N;
  cin >> N;

  if (N <= 0) {
    cout << "-1";
    return 0;
  }

  vector<Node> array(N);
  for (long long i = 0; i < N; ++i) {
    long long temp;
    cin >> temp;

    if (temp < 1 || temp > N) {
      cout << "-1";
      return 0;
    }

    array[i].data = temp;
    array[i].next = &array[temp - 1];
  }

  vector<Node*> cycleNodes;
  long long cycleLength = -1;

  for (long long j = 0; j < N; ++j) {
    if ((cycleLength = Cycle(&array[j], cycleNodes)) > 0) {
      cout << cycleLength << "\n";
      cout << cycleNodes.back()->data << " ";
      for (long long i = 0; i < cycleNodes.size() - 1; ++i) {
        cout << cycleNodes[i]->data << " ";
      }
      cout << "\n";
      return 0;
    }
  }

  cout << "-1";
  return 0;
}
