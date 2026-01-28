#include <iostream>
#include <vector>

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

int main() {
  std::string string;
  std::cin >> string;
  std::vector prefix_function = PrefixFunction(string);
  for (const auto& v : prefix_function) {
    std::cout << v << ' ';
  }
}