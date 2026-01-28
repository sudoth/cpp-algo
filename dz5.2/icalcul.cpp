#include <iostream>
#include <queue>

int main() {
  size_t n;
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<int>> data;
  for (size_t i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    data.emplace(tmp);
  }
  double tax;
  while (data.size() > 1) {
    int tmp = data.top();
    data.pop();
    tmp += data.top();
    data.pop();
    data.push(tmp);
    tax += tmp * 0.05;
  }
  std::cout << tax;
}