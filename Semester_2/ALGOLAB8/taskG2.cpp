#include <iostream>
#include <vector>
#include <set>

using namespace std;

int space[105][105][105];
int dist[105][105][105];

int main() {
  for (int i = 0; i < 105; ++i) {
    for (int j = 0; j < 105; ++j) {
      for (int k = 0; k < 105; ++k) {
        space[i][j][k] = 0;
        dist[i][j][k] = INT_MAX;
      }
    }
  }

  long long plants_number, energy;
  cin >> plants_number >> energy;
  long long x0, y0, z0;
  long long x1, y1, z1;
  cin >> x0 >> y0 >> z0;
  cin >> x1 >> y1 >> z1;
  dist[x0][y0][z0] = 0;
  for (int i = 0; i < plants_number; ++i) {
    long long x, y, z, h1;
    cin >> x >> y >> z >> h1;
    for (int h = 0; h < h1; ++h) {
      space[x][y][z + h] = -1;
    }
  }

  queue<vector<int>> q;
  vector<int> prev(5);
  prev[0] = x0;
  prev[1] = y0;
  prev[2] = z0;
  q.push(prev);
  space[x0][y0][z0] = 0;
  while (!q.empty()) {
    vector<int> v(5);
    v = q.front();
    q.pop();
    for (int i = 0; i < 5; ++i) {
      vector<int> speed(5);
      speed = v;
      speed[i] += 1;
      speed[i] = max(speed[i], 0);
      speed[i] = min(speed[i], 104);
      if (space[speed[0]][speed[1]][speed[2]] != -1 && dist[speed[0]][speed[1]][speed[2]] == INT_MAX) {
        dist[speed[0]][speed[1]][speed[2]] = dist[v[0]][v[1]][v[2]] + 1;
        q.push(speed);
      }
      speed = v;
      speed[i] -= 1;
      speed[i] = max(speed[i], 0);
      speed[i] = min(speed[i], 104);
      if (space[speed[0]][speed[1]][speed[2]] != -1 && dist[speed[0]][speed[1]][speed[2]] == INT_MAX) {
        dist[speed[0]][speed[1]][speed[2]] = dist[v[0]][v[1]][v[2]] + 1;
        q.push(speed);
      }

    }
  }
  int answer = dist[x1][y1][z1];
  if (answer > energy) {
    cout << -1;
  } else {
    cout << answer;
  }
  return 0;
}