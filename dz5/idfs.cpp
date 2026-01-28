#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  void DFS(const int&, std::vector<int>&, std::vector<std::pair<std::vector<int>, int>>&);

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

void Graph::DFS(const int& v, std::vector<int>& color, std::vector<std::pair<std::vector<int>, int>>& part_list) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 0) {
      DFS(u, color, part_list);
    }
  }
  part_list.back().first.push_back(v);
  ++part_list.back().second;
  color[v] = 2;
}

auto Graph::HasCycle() {
  std::vector<int> color(size_);
  std::vector<std::pair<std::vector<int>, int>> part_list;
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      part_list.emplace_back(std::pair<std::vector<int>, int>());
      DFS(i, color, part_list);
    }
  }
  return part_list;
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
    graph.AddEdge(v, u);
    graph.AddEdge(u, v);
  }
  auto part_list = graph.HasCycle();
  std::cout << part_list.size() << '\n';
  for (const auto& it : part_list) {
    std::cout << it.second << '\n';
    for (const auto& v : it.first) {
      std::cout << v + 1 << ' ';
    }
    std::cout << '\n';
  }
}