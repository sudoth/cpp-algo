#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  bool DFS(const int&, std::vector<int>&, std::vector<int>&, int&, int&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  auto HasCycle();
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].emplace_back(u);
}

bool Graph::DFS(const int& v, std::vector<int>& color, std::vector<int>& parent, int& cycle_begin, int& cycle_end) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 1) {
      cycle_begin = u;
      cycle_end = v;
      return true;
    }
    if (color[u] == 0) {
      parent[u] = v;
      if (DFS(u, color, parent, cycle_begin, cycle_end)) {
        return true;
      }
    }
  }
  color[v] = 2;
  return false;
}

auto Graph::HasCycle() {
  struct Return {
    std::vector<int> parent;
    int cycle_begin = -1;
    int cycle_end = -1;
  };
  int cycle_begin = -1;
  int cycle_end = -1;
  std::vector<int> color(size_);
  std::vector<int> parent(size_, -1);
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      if (this->DFS(i, color, parent, cycle_begin, cycle_end)) {
        return Return{parent, cycle_begin, cycle_end};
      }
    }
  }
  return Return{parent};
}

std::vector<int> Recover(const std::vector<int>& parent, const int& begin, const int& end) {
  std::vector<int> path;
  int tmp = end;
  while (tmp != begin) {
    path.push_back(tmp);
    tmp = parent[tmp];
  }
  path.push_back(tmp);
  return path;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph.AddEdge(u, v);
  }
  auto[parent, cycle_begin, cycle_end] = graph.HasCycle();
  if (cycle_begin != -1) {
    std::cout << "YES" << '\n';
    std::vector<int> path = Recover(parent, cycle_begin, cycle_end);
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      std::cout << *it + 1 << ' ';
    }
  } else {
    std::cout << "NO";
  }
}