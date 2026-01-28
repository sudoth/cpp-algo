#include <iostream>

int main() {
  int64_t t = 1;
  int64_t o = 1;
  int n;
  std::cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int64_t tmp = o;
    o = t + o;
    t = tmp;
  }
  std::cout << t + o;
}