#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdint>
#include <utility>

#define ll long long
#define ndl std::cout << "\n"

template<typename T>
void double_add(std::vector<std::vector<T>> &adj_list_, std::vector<std::vector<T>> &adj_list_rev_, const std::string &bool_operation, T a, T b) {
  T index_not_a = a * 2;
  T index_not_b = b * 2;
  if (bool_operation == "->") {
    adj_list_[index_not_a + 1].push_back(index_not_b + 1);
    adj_list_rev_[index_not_b + 1].push_back(index_not_a + 1);
    adj_list_[index_not_b].push_back(index_not_a);
    adj_list_rev_[index_not_a].push_back(index_not_b);
  } else if (bool_operation == "&") {
    adj_list_[index_not_a].push_back(index_not_a + 1);
    adj_list_rev_[index_not_a + 1].push_back(index_not_a);
    adj_list_[index_not_b].push_back(index_not_b + 1);
    adj_list_rev_[index_not_b + 1].push_back(index_not_b);
  } else if (bool_operation == "||") {
    adj_list_[index_not_a].push_back(index_not_b + 1);
    adj_list_rev_[index_not_b + 1].push_back(index_not_a);
    adj_list_[index_not_b].push_back(index_not_a + 1);
    adj_list_rev_[index_not_a + 1].push_back(index_not_b);
  } else if (bool_operation == "^") {
    adj_list_[index_not_a].push_back(index_not_b + 1);
    adj_list_rev_[index_not_b + 1].push_back(index_not_a);
    adj_list_[index_not_b].push_back(index_not_a + 1);
    adj_list_rev_[index_not_a + 1].push_back(index_not_b);
    adj_list_[index_not_a + 1].push_back(index_not_b);
    adj_list_rev_[index_not_b].push_back(index_not_a + 1);
    adj_list_[index_not_b + 1].push_back(index_not_a);
    adj_list_rev_[index_not_a].push_back(index_not_b + 1);
  }
}

template<typename T>
void topsort_dfs(std::vector<T> &visited, T i, std::vector<std::vector<T>> &adjlst_rev, std::vector<T> &way_order) {
  visited[i] = 1;
  for (T i : adjlst_rev[i]) {
    if (!visited[i]) {
      topsort_dfs(visited, i, adjlst_rev, way_order);
    }
  }
  way_order.push_back(i);
}

template<typename T>
void dfs(std::vector<T> &visited, T v, T scc_index, std::vector<std::vector<T>> &adjlst_) {
  visited[v] = scc_index;
  for (T to : adjlst_[v]) {
    if (!visited[to]) {
      dfs(visited, to, scc_index, adjlst_);
    }
  }
}

template<typename T>
void graph_process(std::vector<std::vector<T>>& adj_list_, std::vector<std::vector<T>> adj_list_reversed_, std::vector<T>& visited, std::vector<T>& way_order, T scc_index) {
  visited.assign(adj_list_.size(), 0);
  for (T i = 0; i < adj_list_.size(); ++i) {
    if (!visited[i]) {
      topsort_dfs(visited, i, adj_list_reversed_, way_order);
    }
  }

  std::reverse(way_order.begin(), way_order.end());
  visited.assign(adj_list_.size(), 0);

  for (T i : way_order) {
    if (visited[i] == 0) {
      ++scc_index;
      dfs(visited, i, scc_index, adj_list_);
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios::sync_with_stdio(false);

  ll n, m;
  static ll scc_index;
  bool ans = true;
  std::cin >> n >> m;
  if (n == 0 || m == 0) {
    std::cout << "NO";
    ndl;
    return 0;
  }

  std::vector<std::vector<ll>> adj_list_, adj_list_reversed_;
  adj_list_.resize(n * 2);
  adj_list_reversed_.resize(n * 2);
  std::string operation;
  char ch;
  std::vector<ll> visited, way_order;

  for (ll i = 0; i < m; ++i) {
    std::cin >> operation;
    if (std::isdigit(operation[0]) == false) {
      ll a;
      ch = operation[1];
      a = std::stoi(&operation[1]);
      --a;
      if (m == 1) {
        std::cout << "NO";
        ndl;
        return 0;
      }
      adj_list_[a * 2 + 1].push_back(a * 2);
      adj_list_reversed_[a * 2].push_back(a * 2 + 1);
    } else {
      ll a, b;
      a = std::stoi(operation) - 1;
      std::cin >> operation >> b;
      --b;
      double_add(adj_list_, adj_list_reversed_, operation, a, b);
    }
  }

  graph_process(adj_list_, adj_list_reversed_, visited, way_order, scc_index);

  for (ll i = 0; i < adj_list_.size() - 1 && ans; ++i) {
    ans = (visited[i] != visited[i + 1]);
  }

  std::cout << (ans ? "YES\n" : "NO\n");

  return 0;
}
