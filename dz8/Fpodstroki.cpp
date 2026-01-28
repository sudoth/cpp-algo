#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> PrefixFunction(const std::string& string) {
  int size = static_cast<int>(string.size());
  std::vector<int> prefix_function(size, 0);
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

int NumberOfSubstrings(const std::string& string) {
  int size = static_cast<int>(string.size());
  std::string substring;
  substring.push_back(string[0]);
  int total_number = 1;
  for (int i = 1; i < size; ++i) {
    std::string tmp = substring + string[i];
    std::reverse(tmp.begin(), tmp.end());
    std::vector<int> prefix_function = PrefixFunction(tmp);
    total_number += (static_cast<int>(tmp.size()) - *std::max_element(prefix_function.begin(), prefix_function.end()));
    substring += string[i];
  }
  return total_number;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::string string;
  std::cin >> string;
  std::cout << NumberOfSubstrings(string);
}