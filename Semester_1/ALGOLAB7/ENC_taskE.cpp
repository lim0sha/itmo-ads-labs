#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Segment {
  double left;
  double right;
};

map<char, Segment> define_segments(const vector<char>& letters, const vector<double>& probability) {
  map<char, Segment> segments;
  double l = 0.0;
  for (size_t i = 0; i < letters.size(); ++i) {
    char letter = letters[i];
    segments[letter].left = l;
    segments[letter].right = l + probability[i];
    l = segments[letter].right;
  }
  return segments;
}

double arithmetic_coding(const vector<char>& letters, const vector<double>& probability, const string& s) {
  map<char, Segment> segments = define_segments(letters, probability);
  size_t n = s.size();
  double left = 0.0, right = 1.0;

  for (size_t i = 0; i < n; ++i) {
    char symb = s[i];
    double new_right = left + (right - left) * segments[symb].right;
    double new_left = left + (right - left) * segments[symb].left;
    left = new_left;
    right = new_right;
  }

  return left;
}

int main() {
  string input_str;
  cin >> input_str;

  vector<char> letters_list(input_str.begin(), input_str.end());
  sort(letters_list.begin(), letters_list.end());
  letters_list.erase(unique(letters_list.begin(), letters_list.end()), letters_list.end());

  vector<double> probability_list;
  for (char letter : letters_list) {
    probability_list.push_back(count(input_str.begin(), input_str.end(), letter) / static_cast<double>(input_str.size()));
  }

  double result = arithmetic_coding(letters_list, probability_list, input_str);
  cout << fixed << setprecision(6) << result << endl;

  return 0;
}
