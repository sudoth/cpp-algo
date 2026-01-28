#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

struct Vosminashki {
  explicit Vosminashki(const std::string& state) {
    start = state;
    adj_state.resize(16);
    AddAdj();
  }
  void Solver();
  void AddAdj();
  std::string start;
  std::string final = "123456780";
  std::vector<std::vector<int>> adj_state;
  std::unordered_map<std::string, int> state_dist;
  std::unordered_map<std::string, std::string> state_path;
};

int ZeroIndex(const std::string& state) {
  int zero_index = 0;
  for (int i = 0; i < 9; ++i) {
    if (state[i] == '0') {
      zero_index = i;
      break;
    }
  }
  return zero_index;
}

char FromTo(const int& zero_idx, const int& new_zero_idx) {
  if (new_zero_idx - zero_idx == 1) {
    return 'R';
  }
  if (new_zero_idx - zero_idx == -1) {
    return 'L';
  }
  if (new_zero_idx - zero_idx == 3) {
    return 'D';
  }
  return 'U';
}

void Vosminashki::AddAdj() {
  for (int i = 0; i < 9; ++i) {
    if (i % 3 < 2) {
      adj_state[i].push_back(i + 1);
    }
    if (i % 3 > 0) {
      adj_state[i].push_back(i - 1);
    }
    if (i < 6) {
      adj_state[i].push_back(i + 3);
    }
    if (i > 2) {
      adj_state[i].push_back(i - 3);
    }
  }
}

void Vosminashki::Solver() {
  std::queue<std::string> queue;
  queue.push(start);
  state_dist[start] = 0;
  state_path[start] = "";
  while (!queue.empty()) {
    std::string state = queue.front();
    queue.pop();
    if (state == final) {
      break;
    }
    int zero_idx = ZeroIndex(state);
    for (const auto& new_zero_idx : adj_state[zero_idx]) {
      std::string tmp = state;
      std::swap(tmp[zero_idx], tmp[new_zero_idx]);
      if (state_dist.find(tmp) == state_dist.end()) {
        state_dist[tmp] = state_dist[state] + 1;
        state_path[tmp] = state_path[state] + FromTo(zero_idx, new_zero_idx);
        queue.push(tmp);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string start;
  for (int i = 0; i < 9; ++i) {
    char num = 0;
    std::cin >> num;
    start.push_back(num);
  }

  Vosminashki table(start);
  table.Solver();

  if (table.state_dist.find(table.final) != table.state_dist.end()) {
    std::cout << table.state_dist[table.final] << '\n' << table.state_path[table.final];
  } else {
    std::cout << -1;
  }
}