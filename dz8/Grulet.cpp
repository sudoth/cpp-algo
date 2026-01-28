#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> PrefixFunction(const std::string& string) {
  int size = static_cast<int>(string.size());
  std::vector<int> prefix_function(size);
  for (int i = 1; i < size; ++i) {
    int k = prefix_function[i - 1];
    while (k > 0 && string[i] != string[k]) {
      k = prefix_function[k - 1];
    }
    if (string[i] == string[k]) {
      ++k;
    }
    prefix_function[i] = k;
  }
  return prefix_function;
}

bool IsPermutation(const std::string& first_string, const std::string& second_string) {
  std::string str = first_string + '#' + second_string + second_string;
  std::vector<int> prefix_function = PrefixFunction(str);
  size_t size = str.size();
  for (size_t i = first_string.size(); i < size; ++i) {
    if (prefix_function[i] == static_cast<int>(first_string.size())) {
      return true;
    }
  }
  return false;
}

int main() {
  int size = 0;
  std::cin >> size;
  std::string string;
  std::cin >> string;
  std::string rolled_string;
  std::cin >> rolled_string;
  int bullets_in_first = static_cast<int>(std::count(string.begin(), string.end(), '1'));
  int bullets_in_second = static_cast<int>(std::count(rolled_string.begin(), rolled_string.end(), '1'));

  if (bullets_in_first > bullets_in_second) {
    std::cout << "Yes";
    return 0;
  }

  if (bullets_in_first < bullets_in_second) {
    std::cout << "No";
    return 0;
  }

  if (IsPermutation(string + '0', rolled_string + '0') && IsPermutation(string + '1', rolled_string + '1')) {
    std::cout << "Random";
    return 0;
  }

  if (IsPermutation(string + '0', rolled_string + '0')) {
    std::cout << "No";
    return 0;
  }

  std::cout << "Yes";
}