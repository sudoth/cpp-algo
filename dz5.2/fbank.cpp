#include <unordered_map>
#include <string>
#include <iostream>

int main() {
  size_t n;
  std::cin >> n;
  std::unordered_map<std::string, int> data;
  for (size_t i = 0; i < n; ++i) {
    int request;
    std::cin >> request;
    std::string name;
    std::cin >> name;
    if (request == 1) {
      int sum;
      std::cin >> sum;
      data[name] += sum;
    } else {
      if (data.find(name) == data.end()) {
        std::cout << "ERROR\n";
      } else {
        std::cout << data[name] << '\n';
      }
    }
  }
}