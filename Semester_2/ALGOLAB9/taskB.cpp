#include <iostream>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

vector<ordered_set::iterator> iterator_sets;
vector<int> prnt;
vector<int> rang;
vector<ordered_set> all_sets;

int find_set(int v) {
  if (v != prnt[v])
    prnt[v] = find_set(prnt[v]);
  return prnt[v];
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (rang[a] < rang[b])
      swap(a, b);
    prnt[b] = a;

    for (auto x : all_sets[b]) {
      all_sets[a].insert(x);
      if ((x < *iterator_sets[a]) and (all_sets[a].size() % 2 == 0))
        iterator_sets[a]--;
      else if ((x >= *iterator_sets[a]) and (all_sets[a].size() % 2 == 1))
        iterator_sets[a]++;
    }

    all_sets[b].clear();
    if (rang[a] == rang[b])
      ++rang[a];
  }
}

int median(ordered_set &n) {
  size_t size = n.size();
  if (size % 2 == 0) {
    return *n.find_by_order(size / 2 - 1);
  } else {
    return *n.find_by_order(size / 2);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;

  prnt.resize(n + 1);
  rang.assign(n + 1, 0);
  iterator_sets.resize(n + 1);
  all_sets.resize(n + 1);

  for (int i = 1; i <= n; ++i) {
    prnt[i] = i;
    iterator_sets[i] = all_sets[i].begin();
    all_sets[i].insert(i);
  }

  while (q--) {
    int t, a, b;
    cin >> t;
    if (t == 1) {
      cin >> a >> b;
      union_sets(a, b);
    } else {
      cin >> a;
      int galaxy = find_set(a);
      cout << median(all_sets[galaxy]) << "\n";
    }
  }

  return 0;
}
