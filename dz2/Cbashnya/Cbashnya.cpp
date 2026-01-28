#include <iostream>

int Max(int a, int b) {
  if (a < b) {
    return b;
  }
  return a;
}

int main() {
  int n;
  std::cin >> n;
  int64_t ans = 0;
  for (int i = 0; i < n; i++) {
    int w;
    int h;
    std::cin >> w;
    std::cin >> h;
    ans += Max(w, h);
  }
  std::cout << ans;
}