#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n;
  std::cin >> n;
  std::vector<std::vector<int>> adjacency_list(n);
  size_t m;
  std::cin >> m;
  for (size_t i = 0; i < m; ++i) {
    int request;
    std::cin >> request;
    if (request == 1) {
      int u;
      int v;
      std::cin >> u;
      std::cin >> v;
      --u, --v;
      adjacency_list[u].emplace_back(v);
      adjacency_list[v].emplace_back(u);
    } else {
      int u;
      std::cin >> u;
      --u;
      for (size_t j = 0; j < adjacency_list[u].size(); ++j) {
        std::cout << adjacency_list[u][j] + 1 << ' ';
      }
      std::cout << '\n';
    }
  }
}