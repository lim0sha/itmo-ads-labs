#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>

using namespace std;

const int INF = numeric_limits<int>::max();

bool is_valid_coordinate(int x, int y, int rows, int cols) {
  return x >= 0 and x < rows and y >= 0 and y < cols;
}

void dfs(int x, int y, int region_id, vector<vector<char>>& terrain_map, vector<vector<int>>& regions, int rows, int cols) {
  if (!is_valid_coordinate(x, y, rows, cols) || terrain_map[x][y] != 'X' ||  regions[x][y] != -1) {
    return;
  }
  regions[x][y] = region_id;
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  for (int i = 0; i < 4; ++i) {
    dfs(x + dx[i], y + dy[i], region_id, terrain_map, regions, rows, cols);
  }
}

void bfs(vector<vector<int>>& d, vector<pair<int, int>>& hill_positions, vector<vector<char>>& terrain_map, int rows, int cols) {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

  for (int i = 0; i < hill_positions.size(); ++i) {
    auto& hill = hill_positions[i];
    vector<vector<int>> distance_grid(rows, vector<int>(cols, INF));
    queue<pair<int, int>> queue;
    distance_grid[hill.first][hill.second] = 0;
    queue.push(hill);

    while (!queue.empty()) {
      auto curr = queue.front();
      queue.pop();

      for (int direction = 0; direction < 4; ++direction) {
        int next_x = curr.first + dx[direction];
        int next_y = curr.second + dy[direction];

        if (!is_valid_coordinate(next_x, next_y, rows, cols) || terrain_map[next_x][next_y] == '.') continue;

        int new_distance = distance_grid[curr.first][curr.second] + (terrain_map[next_x][next_y] == 'S' ? 1 : 0);
        if (distance_grid[next_x][next_y] > new_distance) {
          distance_grid[next_x][next_y] = new_distance;
          queue.push({next_x, next_y});
        }
      }
    }

    for (int j = 0; j < hill_positions.size(); ++j) {
      d[i][j] = distance_grid[hill_positions[j].first][hill_positions[j].second];
    }
  }
}

int memo[1 << 19][19];

int tsp(const vector<vector<int>>& distances, int visited, int current_pos, int num_hills) {
  if (visited == (1 << num_hills) - 1) return 0;
  if (memo[visited][current_pos] != -1) return memo[visited][current_pos];

  int best_distance = INF;
  for (int next_pos = 0; next_pos < num_hills; ++next_pos) {
    if (!(visited & (1 << next_pos))) {
      int next_visited = visited | (1 << next_pos);
      int dist = distances[current_pos][next_pos] + tsp(distances, next_visited, next_pos, num_hills);
      best_distance = min(best_distance, dist);
    }
  }

  return memo[visited][current_pos] = best_distance;
}

int main() {
  int rows, cols;
  cin >> rows >> cols;
  vector<vector<char>> terrain_map(rows, vector<char>(cols));
  vector<vector<int>> regions(rows, vector<int>(cols, -1));
  vector<pair<int, int>> hill_positions;

  for (int x = 0; x < rows; ++x) {
    for (int y = 0; y < cols; ++y) {
      cin >> terrain_map[x][y];
      if (terrain_map[x][y] == 'X') {
        hill_positions.emplace_back(x, y);
      }
    }
  }

  int region_id = 0;
  for (auto& hill : hill_positions) {

    if (regions[hill.first][hill.second] == -1) {
      dfs(hill.first, hill.second, region_id++, terrain_map, regions, rows, cols);
    }
  }

  vector<pair<int, int>> distinct_hills;
  for (int i = 0; i < region_id; ++i) {
    for (auto& hill : hill_positions) {
      if (regions[hill.first][hill.second] == i) {
        distinct_hills.push_back(hill);
        break;
      }
    }
  }

  if (distinct_hills.size() == 1) {
    cout << 0 << endl;
    return 0;
  }
  vector<vector<int>> distance_total(distinct_hills.size(), vector<int>(distinct_hills.size(), INF));
  bfs(distance_total, distinct_hills, terrain_map, rows, cols);

  memset(memo, -1, sizeof(memo));
  int N = distinct_hills.size();
  int best_answer = INF;

  for (int i = 0; i < N; ++i) {
    best_answer = min(best_answer, tsp(distance_total, 1 << i, i, N));
  }

  cout << (best_answer != INF ? best_answer : 0) << endl;

  return 0;
}

