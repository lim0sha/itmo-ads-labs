#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct tour_piece {
  long long number_value;
  long long rating_value;
  long long money_value;
};

int first_rating_bigger(const tour_piece &piece1, const tour_piece &piece2) {
  if (piece1.rating_value > piece2.rating_value) {
    return 1;
  }
  if (piece1.rating_value == piece2.rating_value) {
    if (piece1.number_value > piece2.number_value) {
      return 1;
    } else {
      return 0;
    }
  }
  return 0;
}

int first_money_bigger(const tour_piece &piece1, const tour_piece &piece2) {
  if (piece1.money_value > piece2.money_value) {
    return 1;
  }
  if (piece1.money_value == piece2.money_value) {
    if (piece1.number_value > piece2.number_value)
    return 1;
  }
  return 0;
}

void sift_down_by_rating(vector<tour_piece> &heap_array, long long i) {
  long long bigger = i;

  if (2 * i + 1 < heap_array.size() and first_rating_bigger(heap_array[2 * i + 1], heap_array[bigger]) == 1) {
    bigger = 2 * i + 1;
  }

  if (2 * i + 2 < heap_array.size() and first_rating_bigger(heap_array[2 * i + 2], heap_array[bigger]) == 1) {
    bigger = 2 * i + 2;
  }

  if (i != bigger) {
    swap(heap_array[bigger], heap_array[i]);
    sift_down_by_rating(heap_array, bigger);
  }
}

void sift_down_by_money(vector<tour_piece> &heap_array, long long i) {
  long long bigger = i;

  if (2 * i + 1 < heap_array.size() and first_money_bigger(heap_array[2 * i + 1], heap_array[bigger]) == 1) {
    bigger = 2 * i + 1;
  }

  if (2 * i + 2 < heap_array.size() and first_money_bigger(heap_array[2 * i + 2], heap_array[bigger]) == 1) {
    bigger = 2 * i + 2;
  }

  if (i != bigger) {
    swap(heap_array[bigger], heap_array[i]);
    sift_down_by_money(heap_array, bigger);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  vector<tour_piece> all_city_ratings;
  vector<tour_piece> all_city_moneys;

  vector<long long> answered;
  vector<long long> good_for_toour;

  long long n_1;
  cin >> n_1;

  for (long long i = 0; i < n_1; ++i) {
    long long number, rating, money;
    cin >> number >> rating >> money;
    tour_piece temporary_city;
    temporary_city.number_value = number;
    temporary_city.rating_value = rating;
    temporary_city.money_value = money;
    all_city_ratings.push_back(temporary_city);
    all_city_moneys.push_back(temporary_city);
  }

  for (long long i = all_city_ratings.size() / 2; i > -1; --i) {
    sift_down_by_rating(all_city_ratings, i);
  }
  for (long long i = all_city_moneys.size() / 2; i > -1; --i) {
    sift_down_by_money(all_city_moneys, i);
  }

  long long n_2;
  cin >> n_2;

  bool all_answers[n_2];
  string answer;

  for (long long i = 0; i < n_2; ++i) {
    cin >> answer;
    if (answer == "NO") {
      all_answers[i] = false;
    } else {
      all_answers[i] = true;
    }
  }

  long long r = 0;
  while (r < n_1) {
    if (all_city_ratings[0].number_value == all_city_moneys[0].number_value) {
      good_for_toour.push_back(all_city_ratings[0].number_value);

      long long key = all_city_ratings[0].number_value;
      swap(all_city_ratings[0], all_city_ratings[all_city_ratings.size() - 1]);
      all_city_ratings.pop_back();
      sift_down_by_rating(all_city_ratings, 0);

      int key_swap = -1;
      for (int i = all_city_moneys.size() - 1; i > -1; --i) {
        if (all_city_moneys[i].number_value == key) {
          key_swap = i;
          break;
        }
      }
      if (key_swap > -1) {
        swap(all_city_moneys[key_swap], all_city_moneys[all_city_moneys.size() - 1]);
        all_city_moneys.pop_back();
        sift_down_by_money(all_city_moneys, 0);
      }

    } else if (answered.size() < n_2) {
      if (all_answers[answered.size()]) {
        good_for_toour.push_back(all_city_ratings[0].number_value);
      }
      answered.push_back(all_city_ratings[0].number_value);

      long long key = all_city_ratings[0].number_value;
      swap(all_city_ratings[0], all_city_ratings[all_city_ratings.size() - 1]);
      all_city_ratings.pop_back();
      sift_down_by_rating(all_city_ratings, 0);

      int key_swap = -1;
      for (int i = all_city_moneys.size() - 1; i > -1; --i) {
        if (all_city_moneys[i].number_value == key) {
          key_swap = i;
          break;
        }
      }
      if (key_swap > -1) {
        swap(all_city_moneys[key_swap], all_city_moneys[all_city_moneys.size() - 1]);
        all_city_moneys.pop_back();
        sift_down_by_money(all_city_moneys, 0);
      }

    } else {
      swap(all_city_ratings[0], all_city_ratings[all_city_ratings.size() - 1]);
      all_city_ratings.pop_back();
      sift_down_by_rating(all_city_ratings, 0);
    }
    ++r;
  }

  for (long long i : answered) {
    cout << i << " ";
  }
  cout << "\n";
  for (long long i : good_for_toour) {
    cout << i << " ";
  }
}