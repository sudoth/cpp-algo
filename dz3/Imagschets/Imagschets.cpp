#include <iostream>

int main() {
  int n;
  std::cin >> n;
  auto number = new int[n + 1];
  number[1] = 0;
  for (int i = 2; i < n + 1; i++) {
    number[i] = number[i - 1] + 1;
    if (i % 2 == 0) {
      number[i] = std::min(number[i], number[i / 2] + 1);
    }
    if (i % 3 == 0) {
      number[i] = std::min(number[i], number[i / 3] + 1);
    }
  }
  std::cout << number[n];
  delete[] number;
}