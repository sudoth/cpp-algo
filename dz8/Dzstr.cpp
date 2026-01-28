#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

std::string PrefixFunctionToString(const std::vector<int>& prefix_function) {
  int n = static_cast<int>(prefix_function.size());
  std::string string;
  string.resize(n);
  string[0] = 'a';
  for (int i = 1; i < n; ++i) {
    if (prefix_function[i] > 0) {
      string[i] = string[prefix_function[i] - 1];
    } else {
      std::unordered_set<char> ban;
      int k = prefix_function[i - 1];
      while (k > 0) {
        ban.insert(string[k]);
        k = prefix_function[k - 1];
      }
      for (int j = 'b'; j <= 'z'; ++j) {
        if (ban.find(static_cast<char>(j)) == ban.end()) {
          string[i] = static_cast<char>(j);
          break;
        }
      }
    }
  }
  return string;
}

std::vector<int> ZToPrefix(const std::vector<int>& z_function) {
  int n = static_cast<int>(z_function.size());
  std::vector<int> prefix_function(n);
  for (int i = 1; i < n; ++i) {
    for (int delta = z_function[i] - 1; delta >= 0; --delta) {
      if (prefix_function[i + delta] > 0) {
        break;
      }
      prefix_function[i + delta] = delta + 1;
    }
  }
  return prefix_function;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n = 0;
  std::cin >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  std::cout << PrefixFunctionToString(ZToPrefix(v));
}