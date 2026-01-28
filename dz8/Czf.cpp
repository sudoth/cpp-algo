#include <iostream>
#include <vector>
#include <string>

std::vector<int> ZFunction(const std::string& string) {
  int size = static_cast<int>(string.size());
  std::vector<int> z_function(size);
  z_function[0] = size;
  int left = 0;
  int right = 0;
  for (int i = 1; i < size; ++i) {
    if (i < right) {
      z_function[i] = std::min(z_function[i - left], right - i);
    }
    while (i + z_function[i] < size && string[z_function[i]] == string[i + z_function[i]]) {
      ++z_function[i];
    }
    if (right < i + z_function[i]) {
      left = i;
      right = i + z_function[i];
    }
  }
  return z_function;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::string string;
  std::cin >> string;
  std::vector<int> z_function = ZFunction(string);
  for (const auto& v : z_function) {
    std::cout << v << ' ';
  }
}