#include <iostream>

void DeleteToN(int);
void FillToN(int);

void DeleteToN(int n) {
  if (n <= 0) {
    return;
  }
  DeleteToN(n - 2);
  std::cout << -n << " ";
  FillToN(n - 2);
  DeleteToN(n - 1);
}

void FillToN(int n) {
  if (n <= 0) {
    return;
  }
  FillToN(n - 1);
  DeleteToN(n - 2);
  std::cout << n << " ";
  FillToN(n - 2);
}

int main() {
  int n;
  std::cin >> n;
  FillToN(n);
}