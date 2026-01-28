#include <iostream>
#include <cstdint>

void Fill(int64_t n, int64_t w, int64_t h, int64_t& ans, int64_t x = 0, int64_t y = 0) {
  if (n <= 0) {
    ans = std::max(x, y);
    return;
  }
  if (x + w < y + h) {
    Fill(n - y / h, w, h, ans, x + w, y);
  } else {
    Fill(n - x / w, w, h, ans, x, y + h);
  }
}

int main() {
  int64_t w;
  int64_t h;
  int64_t n;
  std::cin >> w;
  std::cin >> h;
  std::cin >> n;
  int64_t ans = 0;
  Fill(n, w, h, ans);
  std::cout << ans;
}