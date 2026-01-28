#include <iostream>

int Sum(int* number, int n = 10) {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || i == 8) {
      continue;
    }
    ans += number[i];
  }
  return ans;
}

int main() {
  int number[10]{};
  std::fill_n(number, 10, 1);
  int n;
  std::cin >> n;
  n--;
  for (int i = 0; i < n; i++) {
    int number0 = number[0];
    int number1 = number[1];
    int number2 = number[2];
    int number3 = number[3];
    int number4 = number[4];
    int number6 = number[6];
    number[0] = number[4] + number[6];
    number[1] = number[6] + number[8];
    number[2] = number[7] + number[9];
    number[3] = number[4] + number[8];
    number[4] = number0 + number3 + number[9];
    number[5] = 0;
    number[6] = number0 + number1 + number[7];
    number[7] = number2 + number6;
    number[8] = number1 + number3;
    number[9] = number2 + number4;
  }
  std::cout << Sum(number);
}