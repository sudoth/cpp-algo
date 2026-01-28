#include <cstring>
#include <iostream>

int main() {
  int k;
  auto script = new char[1000000];
  std::cin >> k;
  std::cin.get();
  std::cin.getline(script, 1e6);
  int n = strlen(script);
  int answer = 0;
  int counter = 0;
  for (int i = 0; i < n - k + 1; i++) {
    if (script[i] == script[i + k]) {
      counter++;
    } else {
      counter = 0;
    }
    answer += counter;
  }
  std::cout << answer;
  delete[] script;
}