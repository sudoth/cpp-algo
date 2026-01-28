#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  bool DFS(const int&, std::vector<int>&, std::vector<int>&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  std::vector<int> TopSort();
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].emplace_back(u);
}

bool Graph::DFS(const int& v, std::vector<int>& color, std::vector<int>& top_sort) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 1) {
      return false;
    }
    if (color[u] == 0) {
      if (!DFS(u, color, top_sort)) {
        return false;
      }
    }
  }
  color[v] = 2;
  top_sort.push_back(v);
  return true;
}

std::vector<int> Graph::TopSort() {
  std::vector<int> color(size_);
  std::vector<int> top_sort;
  top_sort.reserve(size_);
  for (int v = 0; v < size_; ++v) {
    if (color[v] == 0) {
      if (!DFS(v, color, top_sort)) {
        return {};
      }
    }
  }
  return top_sort;
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
  auto top_sort = graph.TopSort();
  if (!top_sort.empty()) {
    for (auto it = top_sort.rbegin(); it != top_sort.rend(); ++it) {
      std::cout << *it + 1 << ' ';
    }
  } else {
    std::cout << -1;
  }
}