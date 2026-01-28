#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int speed_limits[10];
  for (int i = 0; i < n; i++) {
    std::cin >> speed_limits[i];
  }
  int distance[10];
  for (int i = 0; i < n; i++) {
    std::cin >> distance[i];
  }
  int m;
  std::cin >> m;
  auto edge = new int[m];
  edge[0] = 0;
  for (int i = 1; i < m; i++) {
    std::cin >> edge[i];
  }
  auto fine = new int[m];
  for (int i = 0; i < m; i++) {
    std::cin >> fine[i];
  }
  int q;
  std::cin >> q;
  auto entry = new int[q];
  auto exit = new int[q];
  for (int i = 0; i < q; i++) {
    std::cin >> entry[i];
    std::cin >> exit[i];
  }
  for (int i = 0; i < q; i++) {
    int left = -1;
    int right = m;
    while (right - left > 1) {
      int middle = left + (right - left) / 2;
      double time = 0;
      for (int j = 0; j < n; j++) {
        time += distance[j] / (static_cast<double>(speed_limits[j]) + edge[middle]);
      }
      if (static_cast<double>(entry[i]) + time < static_cast<double>(exit[i])) {
        right = middle;
      } else {
        left = middle;
      }
    }
    if (left == -1) {
      std::cout << '0' << '\n';
      continue;
    }
    std::cout << fine[left] << '\n';
  }
  delete[] edge;
  delete[] fine;
  delete[] entry;
  delete[] exit;
}