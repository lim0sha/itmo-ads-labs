#include <iostream>
#include <map>
#include <string>

using namespace std;

string* encodeLZW(const string& s, int& resultSize) {
  string default_buf = "";
  map<string, int> pairs;
  string main_buf = default_buf;
  int bufferSize = s.size() * 2;
  auto* result = new string[bufferSize];
  resultSize = 0;

  for (char c : s) {
    if (pairs.count(main_buf + c) == 1) {
      main_buf += c;
    } else {
      result[resultSize++] = to_string(pairs[main_buf]) + " " + c;
      int psize = pairs.size();
      pairs[main_buf + c] = psize;
      main_buf = default_buf;
    }
  }

  if (!(main_buf.size() == 0)) {
    result[resultSize++] = to_string(pairs[main_buf]) + " " + '\0';
  }

  return result;
}

int main() {
  string input;
  cin >> input;

  int compressedSize;
  string* compressed = encodeLZW(input, compressedSize);

  for (int i = 0; i < compressedSize; ++i) {
    cout << compressed[i] << "\n";
  }

  delete[] compressed;
  return 0;
}
