#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int> data;
  for (size_t i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    data.emplace_back(tmp);
  }
  size_t m;
  std::cin >> m;
  for (size_t i = 0; i < m; ++i) {
    int request;
    std::cin >> request;
    std::cout << std::upper_bound(data.begin(), data.end(), request) -
                     std::lower_bound(data.begin(), data.end(), request)
              << '\n';
  }
}