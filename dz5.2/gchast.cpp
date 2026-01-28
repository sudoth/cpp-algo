#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  std::map<std::string, int> data;
  std::string word;
  while (std::cin >> word) {
    data[word]++;
  }
  std::vector<std::pair<std::string, int>> tmp;
  tmp.reserve(data.size());
  for (auto it = data.begin(); it != data.end(); ++it) {
    tmp.emplace_back(std::pair(it->first, it->second));
  }
  std::sort(tmp.begin(), tmp.end(), [](const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) {
    return (lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second > rhs.second);
  });
  for (size_t i = 0; i < tmp.size(); ++i) {
    std::cout << tmp[i].first << '\n';
  }
}