#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bit>

int PrefixFunction(const std::string& string) {
  int n = static_cast<int>(string.size());
  std::vector<int> prefix_function(n);
  for (int i = 1; i < n; ++i) {
    int k = prefix_function[i - 1];
    while (k > 0 && string[i] != string[k]) {
      k = prefix_function[k - 1];
    }
    if (string[i] == string[k]) {
      ++k;
    }
    prefix_function[i] = k;
  }
  return prefix_function[n - 1];
}

std::string Merge(const std::vector<std::string>& arr) {
  std::string merged = arr[0];
  for (size_t i = 1; i < arr.size(); ++i) {
    std::string to_prefix;
    if (merged.size() > arr[i].size()) {
      to_prefix = arr[i] + '#' + merged.substr(merged.size() - arr[i].size());
    } else {
      to_prefix = arr[i] + '#' + merged;
    }
    int prefix_size = PrefixFunction(to_prefix);
    merged += arr[i].substr(prefix_size);
  }
  return merged;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<std::string> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cout << Merge(arr);
}