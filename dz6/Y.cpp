#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

struct VectorHash {
  template <typename T>
  size_t operator()(const std::vector<T>& vec) const {
    size_t h = vec.size();
    for (const auto& i : vec) {
      h ^= i + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
  }
};

struct Pyatnashki {
  explicit Pyatnashki(const std::vector<int>& state) {
    start = state;
    adj_state.resize(16);
    dist_to_fianl = 0;
    path_to_final = "";
    AddAdj();
  }
  int dist_to_fianl;
  std::string path_to_final;
  void Solver();
  bool IsSolvable();
  void AddAdj();
  std::vector<int> start;
  std::vector<int> final{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
  std::vector<std::vector<int>> adj_state;
  std::unordered_map<std::vector<int>, int, VectorHash> state_dist;
  std::unordered_map<std::vector<int>, std::vector<int>, VectorHash> state_prev;
};

int ZeroIndex(const std::vector<int>& state) {
  int zero_index = 0;
  for (int i = 0; i < 16; ++i) {
    if (state[i] == 0) {
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
  if (new_zero_idx - zero_idx == 4) {
    return 'D';
  }
  return 'U';
}

void Pyatnashki::AddAdj() {
  for (int i = 0; i < 16; ++i) {
    if (i % 4 < 3) {
      adj_state[i].push_back(i + 1);
    }
    if (i % 4 > 0) {
      adj_state[i].push_back(i - 1);
    }
    if (i < 12) {
      adj_state[i].push_back(i + 4);
    }
    if (i > 3) {
      adj_state[i].push_back(i - 4);
    }
  }
}

bool Pyatnashki::IsSolvable() {
  int inversions = 0;
  for (int i = 0; i < 16; ++i) {
    if (start[i] != 0) {
      for (int j = 0; j < i; ++j) {
        if (start[j] > start[i]) {
          ++inversions;
        }
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    if (start[i] == 0) {
      inversions += 1 + i / 4;
    }
  }
  return inversions % 2 == 0;
}

int Heuristic(const std::vector<int>& state) {
  int h = 0;
  for (int i = 0; i < 16; ++i) {
    if (state[i] == 0) {
      continue;
    }
    h += std::abs((state[i] - 1) / 4 - i / 4) + std::abs((state[i] - 1) % 4 - i % 4);
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = j + 1; k < 4; ++k) {
        if (4 * i + j != ZeroIndex(state) && 4 * i + k != ZeroIndex(state) && (state[4 * i + j] - 1) / 4 == i &&
            (state[4 * i + k] - 1) / 4 == i && state[4 * i + j] > state[4 * i + k]) {
          h += 2;
        }
      }
    }
  }
  if (state[15] != 15 && state[15] != 12) {
    h += 2;
  }
  return h;
}

void Pyatnashki::Solver() {
  std::priority_queue<std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::greater<>>
      queue;
  state_dist[start] = 0;
  state_prev[start] = start;
  queue.emplace(state_dist[start] + Heuristic(start), start);
  while (!queue.empty()) {
    auto top = queue.top();
    auto state = top.second;
    auto w = top.first;
    queue.pop();
    if (state == final) {
      break;
    }
    if (w > state_dist[state] + Heuristic(state)) {
      continue;
    }
    int zero_idx = ZeroIndex(state);
    for (const auto& new_zero_idx : adj_state[zero_idx]) {
      auto tmp = state;
      std::swap(tmp[zero_idx], tmp[new_zero_idx]);
      if (state_dist.find(tmp) == state_dist.end()) {
        state_dist[tmp] = INT32_MAX;
      }
      if (state_dist[state] + 1 < state_dist[tmp]) {
        state_prev[tmp] = state;
        state_dist[tmp] = state_dist[state] + 1;
        queue.emplace(state_dist[tmp] + Heuristic(tmp), tmp);
      }
    }
  }

  auto cur = final;
  while (cur != start) {
    ++dist_to_fianl;
    path_to_final += FromTo(ZeroIndex(cur), ZeroIndex(state_prev[cur]));
    cur = state_prev[cur];
  }
  std::reverse(path_to_final.begin(), path_to_final.end());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::vector<int> start(16);
  for (int i = 0; i < 16; ++i) {
    std::cin >> start[i];
  }

  Pyatnashki table(start);

  if (!table.IsSolvable()) {
    std::cout << -1;
    return 0;
  }

  table.Solver();

  std::cout << table.dist_to_fianl << '\n' << table.path_to_final;
}