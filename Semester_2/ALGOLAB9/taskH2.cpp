#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

static set<pair<int, int>> all_bridges;
static int n_bridges = 0;
static int total = 0;
unordered_map<string, int> pairs;

// дфс для scc
void dfs_scc(int v, int parent, const vector<vector<int>> &scc_made_cond,
             vector<int> &scc_used, vector<int> &v_scc_index,
             int &index, vector<int> &numOfVertexInEachComp) {
  scc_used[v] = true;
  v_scc_index[v] = index;
  ++numOfVertexInEachComp[v_scc_index[v]];
  for (int i : scc_made_cond[v]) {
    if (!scc_used[i] && i != parent) {
      dfs_scc(i, v, scc_made_cond, scc_used, v_scc_index, index, numOfVertexInEachComp);
    }
  }
}

// дфс для ответа
void dfs_result(int a, int b, vector<vector<int>> &g,
                vector<int> &used, vector<int> &d, vector<int> &scc_v_amount,
                vector<int> &scc, int &result) {
  used[a] = true;
  for (auto i : g[a]) {
    if (i == b) {
      continue;
    }
    if (!used[i] && i != b) {
      dfs_result(i, a, g, used, d, scc_v_amount, scc, result);
    }
    d[a] += d[i];
  }
  // берем длину всех путей, начинающихся в вершине a (d[a])
  // умножаем ее на количество вершин в текущей scc
  // минус длина всех путей, проходящих через вершину a (scc_v_amount[scc[a]] - d[a])
  // так мы учитываем только пути, которые начинаются в вершине a и не проходят через нее снова = уникальные пути
  result += d[a] * (scc_v_amount[scc[a]] - d[a]);
}

// надо получать уникальный код для каждого элемента (26 - всего букв, as example)
auto hash_get(const int element_1, const int element_2, const int number) {
  auto get1 = std::hash<int>{}(element_1);
  auto get2 = std::hash<int>{}(element_2);
  auto temp = number * get1 ^ get2;
  auto result = temp + temp % 27;
  return result;
}

// дфс с маркерами для поиска мостов
void dfs_bridges(const vector<vector<int>> &g,
                 int &v, int previous, int &time_marker,
                 vector<int> &in_marker,
                 vector<int> &up_marker,
                 vector<int> &main_marker, unordered_map<int, int> &do_not_take, int n) {
  main_marker[v] = true;
  in_marker[v] = up_marker[v] = time_marker++;
  for (auto k : g[v]) {
    auto destination = k;
    if (destination == previous) {
      continue;
    }
    if (main_marker[destination]) {
      up_marker[v] = min(up_marker[v], in_marker[destination]);
    } else {
      dfs_bridges(g, destination, v, time_marker, in_marker, up_marker, main_marker, do_not_take, n);
      if (up_marker[v] > up_marker[destination]) {
        up_marker[v] = up_marker[destination];
      }
      if (up_marker[destination] > in_marker[v]) {
        auto xorr1 = hash_get(destination, v, n);
        auto xorr2 = hash_get(v, destination, n);
        if (!(do_not_take[xorr1] and do_not_take[xorr2])) {
          all_bridges.insert({destination, v});
          all_bridges.insert({v, destination});
          ++n_bridges;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  string word;
  string w1, w2;
  cin >> n >> m;
  vector<vector<int>> G(n);
  unordered_map<int, int> do_not_take_flags(n);
  unordered_map<int, int> multiple_edges_flags(n);

  // маркеры входа
  vector<int> tin(n);
  std::fill(tin.begin(), tin.end(), 0);
  // маркеры выхода
  vector<int> up(n);
  std::fill(up.begin(), up.end(), 0);
  // основные маркеры для вершин
  vector<int> main_marker(n);
  std::fill(main_marker.begin(), main_marker.end(), 0);
  // все вершины
  vector<int> V(n);

  // сколько вершин в каждой из частей конденсации (в scc)
  vector<int> scc_v_amount(n);
  std::fill(scc_v_amount.begin(), scc_v_amount.end(), 0);
  // массив visited для вершин в конденсации
  vector<int> scc_cond_used(n);
  std::fill(scc_cond_used.begin(), scc_cond_used.end(), 0);
  // компоненты сс - для каждой вершины (принадлежность той или иной scc)
  vector<int> component(n);
  std::fill(component.begin(), component.end(), -1);
  // массив visited для вершин в графе
  vector<int> used(n);
  std::fill(used.begin(), used.end(), 0);

  // конденсация графа
  vector<vector<int>> G_scc_made(n);
  // массив расстояний
  vector<int> d(n);

  for (int i = 0; i < n; ++i) {
    V.push_back(i);
    cin >> word;
    pairs[word] = i;
  }
  for (int i = 0; i < m; ++i) {
    cin >> w1 >> w2;
    auto w_1_key = hash_get(pairs[w1], pairs[w2], n);
    auto w_2_key = hash_get(pairs[w2], pairs[w1], n);
    if (!multiple_edges_flags[w_1_key] || !multiple_edges_flags[w_2_key]) {
      G[pairs[w1]].push_back(pairs[w2]);
      G[pairs[w2]].push_back(pairs[w1]);
      multiple_edges_flags[w_1_key] = 1;
      multiple_edges_flags[w_2_key] = 1;
    } else {
      do_not_take_flags[w_1_key] = 1;
      do_not_take_flags[w_2_key] = 1;
    }
  }

  // ищем мосты
  auto time_marker = 0;
  for (int i = 0; i < V.size(); ++i) {
    int vertex = V[i];
    if (!main_marker[vertex]) {
      int parent = -1;
      dfs_bridges(G, vertex, parent, time_marker, tin, up, main_marker, do_not_take_flags, n);
    }
  }

  // делаем конденсацию
  for (const std::pair<int, int> &bridge : all_bridges) {
    int a = bridge.first;
    int b = bridge.second;
    G_scc_made[a].push_back(b);
    d[a] = 1;
  }


  // помечаем вершины по компонентам
  auto scc_index = 0;
  for (int i = 0; i < n; ++i) {
    if (!scc_cond_used[i] && !G_scc_made[i].empty()) {
      dfs_scc(i, -1, G_scc_made, scc_cond_used, component, scc_index, scc_v_amount);
      ++scc_index;
    }
  }

  // сумма длин уникальных путей = по формуле в функции dfs_result
  for (int i = 0; i < n; ++i) {
    if (!(used[i] || G_scc_made[i].empty())) {
      dfs_result(i, -1, G_scc_made, used, d, scc_v_amount, component, total);
    }
  }
  cout << total;
  return 0;
}
