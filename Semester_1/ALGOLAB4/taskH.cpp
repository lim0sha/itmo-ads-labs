#include <iostream>
#include <vector>

typedef std::vector<long long> BlockArray;

void make_parts(const std::string& string_number, BlockArray& parts) {
  for (int i = string_number.length(); i > 0; i -= 9) {
    parts.push_back(stoll(string_number.substr(std::max(i - 9, 0), std::min(9, i))));
  }
}

void summ_parts(BlockArray& first, const BlockArray& second) {
  long long carry = 0;
  for (size_t i = 0; i < std::max(first.size(), second.size()) or carry; ++i) {
    if (i == first.size()) first.push_back(0);
    first[i] += (i < second.size() ? second[i] : 0) + carry;
    carry = first[i] / 1000000000;
    first[i] %= 1000000000;
  }
}

void minus_parts(BlockArray& first, const BlockArray& second) {
  long long borrow = 0;
  for (size_t i = 0; i < std::max(first.size(), second.size()); ++i) {
    first[i] -= (i < second.size() ? second[i] : 0) + borrow;
    borrow = 0;
    if (first[i] < 0) {
      first[i] += 1000000000;
      borrow = 1;
    }
  }
  while (first.size() > 1 && first.back() == 0) {
    first.pop_back();
  }
}

bool compare_first_x_sec(const BlockArray& first, const BlockArray& second) {
  if (first.size() != second.size()) {
    return first.size() > second.size();
  }
  for (int i = first.size() - 1; i >= 0; --i) {
    if (first[i] != second[i]) return first[i] > second[i];
  }
  return false;
}

void cout_bigint(const BlockArray& blocks, bool is_negative) {
  if (is_negative && !blocks.empty()) {
    std::cout << "-";
  }
  if (!blocks.empty()) {
    std::cout << blocks.back();
    for (int i = blocks.size() - 2; i >= 0; --i) {
      std::cout << std::string(9 - std::to_string(blocks[i]).length(), '0') << blocks[i];
    }
  } else {
    std::cout << "0";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  BlockArray positive_ns;
  BlockArray negative_ns;

  std::string string_number;
  for (int i = 0; i < N; ++i) {
    std::cin >> string_number;
    bool is_negative = string_number[0] == '-';
    if (is_negative) {
      string_number = string_number.substr(1);
    }

    BlockArray main_parts;
    make_parts(string_number, main_parts);

    if (is_negative) {
      summ_parts(negative_ns, main_parts);
    } else {
      summ_parts(positive_ns, main_parts);
    }
  }

  if (compare_first_x_sec(negative_ns, positive_ns)) {
    minus_parts(negative_ns, positive_ns);
    cout_bigint(negative_ns, true);
  } else {
    minus_parts(positive_ns, negative_ns);
    cout_bigint(positive_ns, false);
  }
  return 0;
}
