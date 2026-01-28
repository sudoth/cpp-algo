#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> ZFunction(const std::vector<int>& values) {
  int size_str = static_cast<int>(values.size());
  std::vector<int> palindrome(size_str, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < size_str; ++i) {
    if (i <= right) {
      palindrome[i] = std::max(0, std::min(right - i + 1, palindrome[right - i + 1 + left]));
    }
    while ((i + palindrome[i] < size_str) && (i - palindrome[i] - 1 >= 0) &&
           (values[i + palindrome[i]] == values[i - palindrome[i] - 1])) {
      ++palindrome[i];
    }
    if (i + palindrome[i] - 1 > right) {
      right = i + palindrome[i] - 1;
      left = i - palindrome[i];
    }
  }
  return palindrome;
}
int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> cubes(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cubes[i];
  }
  std::vector<int> palindrome(ZFunction(cubes));
  for (int i = n - 1; i >= 0; --i) {
    if (palindrome[i] - i == 0) {
      std::cout << n - palindrome[i] << ' ';
    }
  }
  return 0;
}