#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  void DFS(const int&, std::vector<int>&, std::vector<std::pair<int, int>>&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  std::vector<std::pair<int, int>> Numerize();
  bool IsOK(const int&, const std::vector<std::pair<int, int>>);
  int FindPermutation(const std::vector<std::pair<int, int>>&);
};

void Graph::AddEdge(const int& v, const int& u, const int& w) {
  adj_[v].emplace_back(std::pair<int, int>(u, w));
}

void Graph::DFS(const int& v, std::vector<int>& color, std::vector<std::pair<int, int>>& permutation) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u.first] == 0) {
      permutation[u.first].first = -permutation[v].first;
      permutation[u.first].second = u.second - permutation[v].second;
      DFS(u.first, color, permutation);
    }
  }
  color[v] = 2;
}

// N = ax + b
std::vector<std::pair<int, int>> Graph::Numerize() {
  std::vector<std::pair<int, int>> permutation(size_);
  std::vector<int> color(size_);
  permutation[0].first = 1;
  DFS(0, color, permutation);
  return permutation;
}

bool Graph::IsOK(const int& x, const std::vector<std::pair<int, int>> permutation) {
  std::vector<bool> checker(size_);
  for (int i = 0; i < size_; ++i) {
    int n = permutation[i].first * x + permutation[i].second;
    if (n > size_ + 1 || n < 0) {
      return false;
    }
    checker[n - 1] = true;
  }
  for (int i = 0; i < size_; ++i) {
    if (!checker[i]) {
      return false;
    }
  }
  for (int v = 0; v < size_; ++v) {
    for (const auto& u : adj_[v]) {
      int v_weight = permutation[v].first * x + permutation[v].second;
      int u_weight = permutation[u.first].first * x + permutation[u.first].second;
      if (v_weight + u_weight != u.second) {
        return false;
      }
    }
  }
  return true;
}

int Graph::FindPermutation(const std::vector<std::pair<int, int>>& permutation) {
  int minus_min = 1000007;
  int plus_min = 1000007;
  for (const auto& u : permutation) {
    if (u.first == 1) {
      if (u.second < plus_min) {
        plus_min = u.second;
      }
    }
    if (u.first == -1) {
      if (u.second < minus_min) {
        minus_min = u.second;
      }
    }
  }
  int plus_x = 1 - plus_min;
  int minus_x = minus_min - 1;

  if (IsOK(plus_x, permutation)) {
    return plus_x;
  }
  return minus_x;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    graph.AddEdge(v, u, w);
    graph.AddEdge(u, v, w);
  }
  auto permutation = graph.Numerize();
  int x = graph.FindPermutation(permutation);
  for (int i = 0; i < n; ++i) {
    std::cout << permutation[i].first * x + permutation[i].second << ' ';
  }
}