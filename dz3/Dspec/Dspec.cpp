#include <iostream>

int main() {
  int a = 1;
  int b = 1;
  int c = 1;
  int n;
  std::cin >> n;
  for (int i = 0; i < n - 1; i++) {
    b = a + b + c;
    c = b;
    a = b - a;
  }
  std::cout << a + b + c;
}