#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int> data;
  data.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    data.emplace_back(tmp);
  }
  int x;
  std::cin >> x;
  std::cout << std::count(data.begin(), data.end(), x);
}