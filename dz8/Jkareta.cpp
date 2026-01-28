#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int64_t> ZFunction(const std::string& str) {
  auto size_str = static_cast<int64_t>(str.size());
  std::vector<int64_t> z_function(size_str, 0);
  z_function[0] = size_str;
  int64_t left = 0;
  int64_t right = 0;
  for (int64_t i = 1; i < size_str; ++i) {
    if (std::min(right - i, z_function[i - left]) > 0) {
      z_function[i] = std::min(right - i, z_function[i - left]);
    }
    while ((i + z_function[i] < size_str) && (str[z_function[i]] == str[i + z_function[i]])) {
      ++z_function[i];
    }
    if (i + z_function[i] > right) {
      right = i + z_function[i];
      left = i;
    }
  }
  return z_function;
}

std::vector<int64_t> PrefixPosition(bool& correct_word, int64_t& words_number, const std::string& first_word,
                                    const std::string& second_word) {
  std::vector<int64_t> z_function(ZFunction(first_word + '#' + second_word));
  auto first_size = static_cast<int64_t>(first_word.size() + 1);
  auto second_size = static_cast<int64_t>(second_word.size());
  int64_t size = first_size + second_size;
  int64_t max_ind_pos = first_size;
  std::vector<int64_t> prefix_position(second_size);
  if (z_function[first_size] != 0) {
    for (int64_t i = first_size; i < size; i++) {
      if ((i >= max_ind_pos) && (z_function[i] == 0)) {
        correct_word = true;
        break;
      }
      if (max_ind_pos <= z_function[i] + i) {
        max_ind_pos = z_function[i] + i;
        prefix_position[words_number] = i;
        ++words_number;
      }
    }
  } else {
    correct_word = true;
  }
  return prefix_position;
}

int main() {
  std::string first_word;
  std::string second_word;
  std::cin >> first_word >> second_word;
  bool correct_word = false;
  auto first_size = static_cast<int64_t>(first_word.size() + 1);
  auto second_size = static_cast<int64_t>(second_word.size());
  int64_t words_number = 0;
  std::vector<int64_t> prefix_position(PrefixPosition(correct_word, words_number, first_word, second_word));
  if (correct_word) {
    std::cout << "Yes";
  } else {
    std::cout << "No" << '\n';
    int64_t new_pos = prefix_position[1] - first_size;
    int64_t last_pos = 0;
    for (int64_t i = 1; i < words_number; i++) {
      for (int64_t j = last_pos; j < new_pos; j++) {
        std::cout << second_word[j];
      }
      std::cout << ' ';
      last_pos = new_pos;
      new_pos = prefix_position[(i + 1) % second_size] - first_size;
    }
    for (int64_t j = last_pos; j < second_size; j++) {
      std::cout << second_word[j];
    }
  }
  return 0;
}
