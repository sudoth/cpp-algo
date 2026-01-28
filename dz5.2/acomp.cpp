#include <algorithm>
#include <iostream>
#include <vector>

struct Team {
  int number;
  int score;
  int penalty;
};

int main() {
  size_t n;
  std::cin >> n;
  std::vector<Team> data;
  data.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    Team tmp;
    std::cin >> tmp.score >> tmp.penalty;
    tmp.number = i + 1;
    data.emplace_back(tmp);
  }
  std::sort(data.begin(), data.end(), [](const Team& lhs, const Team& rhs) {
    if (lhs.score == rhs.score && lhs.penalty == rhs.penalty) {
      return lhs.number < rhs.number;
    }
    if (lhs.score == rhs.score) {
      return lhs.penalty < rhs.penalty;
    }
    return lhs.score > rhs.score;
  });
  for (size_t i; i < n; ++i) {
    std::cout << data[i].number << '\n';
  }
}