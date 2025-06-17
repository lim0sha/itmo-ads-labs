#include <iostream>
#include <string>
#include <vector>
using namespace std;

std::string decodeRLE(const std::string& encoded) {
  std::string decoded;
  int count = 0;
  char currentChar = '\0';
  for (char c : encoded) {
    if (isdigit(c)) {
      count = count * 10 + (c - '0');
    } else {
      if (count > 0) {
        decoded += std::string(count, currentChar);
        count = 0;
      }
      currentChar = static_cast<char>(c);
    }
  }
  if (count > 0) {
    decoded += std::string(count, currentChar);
    count = 0;
  }
  return decoded;
}

int main() {
  int n, k, errors;
  cin >> n >> k >> errors;
  string line_1, line_2;
  int len_1 = 0, len_2 = 0;
  vector<pair<char, int>> letters_1;
  vector<pair<char, int>> letters_2;
  int number = 0;
  char prev = '\0';
  char c;
  line_1 += ' ';
  line_2 += ' ';
  for (int i = 0; i < n; ++i) {
    std::cin >> c;
    if (isdigit(c)) {
      number *= 10;
      number += (int)(c - '0');
    } else {
      if (i > 0) {
        letters_1.push_back({prev, number});
      }
      prev = c;
      len_1 += number;
      number = 0;
    }
  }
  number = 0;
  prev = '\0';
  char ca;
  for (int i = 0; i < k; ++i) {
    std::cin >> c;
    if (isdigit(c)) {
      number *= 10;
      number += (int)(c - '0');
    } else {
      if (i > 0) {
        letters_2.push_back({prev, number});
      }
      prev = c;
      len_2 += number;
      number = 0;
    }
  }
  int index_1 = 0;
  int index_2 = 0;
  int dif = abs(len_1 - len_2);
  while (index_1 < letters_1.size() && index_2 < letters_2.size()) {
    int seq_len = min(letters_1[index_1].second, letters_2[index_2].second);
    if (letters_1[index_1].first != letters_2[index_2].first) {
      dif += seq_len;
    }
    letters_1[index_1].second -= seq_len;
    letters_2[index_2].second -= seq_len;
    if (letters_1[index_1].second == 0) {
      ++index_1;
    }
    if (letters_2[index_2].second == 0) {
      ++index_2;
    }
  }
  if (dif >= errors) {
    cout << "No";
  } else {
    cout << "Yes";
  }
  return 0;
}
