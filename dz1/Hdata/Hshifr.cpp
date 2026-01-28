#include <iostream>
#include <cstring>

int main() {
  char prev_str[200000];
  std::cin.getline(prev_str, 1e6);
  int n = strlen(prev_str) - 1;
  prev_str[n] = '\0';
  char new_str[200000];
  int k = 0;
  for (int i = 0; i < n; i += 2) {
    new_str[k] = prev_str[i];
    k++;
  }
  if (n % 2 == 0) {
    for (int i = n - (n - 1) % 2; i >= 0; i -= 2) {
      new_str[k] = prev_str[i];
      k++;
    }
    std::cout << new_str;
    return 0;
  }
  for (int i = n - (n - 1) % 2 - 2; i >= 0; i -= 2) {
    new_str[k] = prev_str[i];
    k++;
  }
  std::cout << new_str;
}