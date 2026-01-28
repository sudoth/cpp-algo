#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  int m;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int begin, end;
    std::cin >> begin >> end;
    int sum;
    for (int j = begin; j <= end; ++j) {
      sum += v[j];
    }
    std::cout << sum << '\n';
  }
}