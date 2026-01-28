#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n;
  std::cin >> n;
  std::unordered_map<std::string, std::string> data(2 * n);
  for (size_t i = 0; i < n; ++i) {
    std::string lhs;
    std::string rhs;
    std::cin >> lhs;
    std::cin >> rhs;
    data[lhs] = rhs;
    data[rhs] = lhs;
  }
  size_t m;
  std::cin >> m;
  for (size_t i = 0; i < m; ++i) {
    std::string tmp;
    std::cin >> tmp;
    std::cout << data[tmp] << '\n';
  }
}