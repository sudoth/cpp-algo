#include <map>
#include <string>
#include <iostream>

int main() {
  freopen("input.txt", "r", stdin);
  std::string name;
  std::string product;
  int64_t quantity;
  std::map<std::string, std::map<std::string, int64_t>> data;
  while (std::cin >> name) {
    std::cin >> product;
    std::cin >> quantity;
    data[name][product] += quantity;
  }
  for (auto name_it = data.begin(); name_it != data.end(); ++name_it) {
    std::cout << name_it->first << ":\n";
    for (auto product_it = name_it->second.begin(); product_it != name_it->second.end(); ++product_it) {
      std::cout << product_it->first << ' ' << product_it->second << '\n';
    }
  }
}