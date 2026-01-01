#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>

using namespace std;

class Drone_Field {
 private:
  vector<vector<vector<long long>>> actual_space_;
  vector<vector<vector<long long>>> distance_;
  long long plants_number{};
  long long drone_energy_{};
  vector<int> start_position_;
  vector<int> finish_position_;

 public:
  Drone_Field(long long size) {
    actual_space_.resize(size, vector<vector<long long>>(size, vector<long long>(size, 0)));
    distance_.resize(size, vector<vector<long long>>(size, vector<long long>(size, INT_MAX)));
  }

  void add_plant(long long x, long long y, long long z, long long height) {
    for (long long h = 0; h < height; ++h) {
      actual_space_[x][y][z + h] = -1; // где -1 - там не дрон пролетит
    }
  }

  void set_start(int x, int y, int z) {
    start_position_ = {x, y, z};
  }

  void set_finish(int x, int y, int z) {
    finish_position_ = {x, y, z};
  }

  void set_plants_number(long long num) {
    plants_number = num;
  }

  void set_drone_energy(long long en) {
    drone_energy_ = en;
  }

  size_t navigate() {
    queue<vector<int>> Queue;
    Queue.push(start_position_);
    distance_[start_position_[0]][start_position_[1]][start_position_[2]] = 0;

    while (!Queue.empty()) {
      vector<int> v = Queue.front();
      Queue.pop();

      for (size_t i = 0; i < 5; ++i) {
        vector<int> speed = v;
        speed[i] += 1;
        speed[i] = max(speed[i], 0);
        speed[i] = min(speed[i], 104);
        if (actual_space_[speed[0]][speed[1]][speed[2]] != -1 and distance_[speed[0]][speed[1]][speed[2]] == INT_MAX) {
          distance_[speed[0]][speed[1]][speed[2]] = distance_[v[0]][v[1]][v[2]] + 1;
          Queue.push(speed);
        }

        speed = v;
        speed[i] -= 1;
        speed[i] = max(speed[i], 0);
        speed[i] = min(speed[i], 104);
        if (actual_space_[speed[0]][speed[1]][speed[2]] != -1 and distance_[speed[0]][speed[1]][speed[2]] == INT_MAX) {
          distance_[speed[0]][speed[1]][speed[2]] = distance_[v[0]][v[1]][v[2]] + 1;
          Queue.push(speed);
        }
      }
    }

    size_t result = distance_[finish_position_[0]][finish_position_[1]][finish_position_[2]];
    return (result > drone_energy_) ? -1 : result;
  }
};

int main() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
  size_t size = 105;
  Drone_Field navigator(size);

  long long n, nrg;
  cin >> n >> nrg;

  navigator.set_plants_number(n);
  navigator.set_drone_energy(nrg);

  long long x_1, y_1, z_1;
  long long x_2, y_2, z_2;
  cin >> x_1 >> y_1 >> z_1;
  navigator.set_start(x_1, y_1, z_1);
  cin >> x_2 >> y_2 >> z_2;
  navigator.set_finish(x_2, y_2, z_2);

  for (int i = 0; i < n; ++i) {
    long long x, y, z, height;
    cin >> x >> y >> z >> height;
    navigator.add_plant(x, y, z, height);
  }
  cout << navigator.navigate();
  return 0;
}
