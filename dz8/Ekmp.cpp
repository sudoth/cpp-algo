#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(const std::string& s) {
  int size = static_cast<int>(s.size());
  std::vector<int> prefix_function(size, 0);
  for (int i = 1; i < size; ++i) {
    int k = prefix_function[i - 1];
    while (k > 0 && s[i] != s[k]) {
      k = prefix_function[k - 1];
    }
    if (s[i] == s[k]) {
      ++k;
    }
    prefix_function[i] = k;
  }
  return prefix_function;
}

std::vector<size_t> KMP(const std::string& string, const std::string& pattern) {
  std::vector<size_t> position;
  std::string str = pattern + '#' + string;
  std::vector<int> prefix_function = PrefixFunction(str);
  size_t size = str.size();
  for (size_t i = pattern.size(); i < size; ++i) {
    if (prefix_function[i] == static_cast<int>(pattern.size())) {
      position.push_back(i - 2 * pattern.size());
    }
  }
  return position;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::string string;
  std::cin >> string;
  std::string pattern;
  std::cin >> pattern;
  std::vector<size_t> kmp = KMP(string, pattern);
  for (const auto& v : kmp) {
    std::cout << v << '\n';
  }
}