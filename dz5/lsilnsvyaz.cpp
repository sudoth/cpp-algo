#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  auto DFS(const std::vector<int>&);
  void DFSVisit(const int&, std::vector<int>&, std::vector<int>&);
  void DFSVisitNoCycles(const int&, std::vector<int>&, std::vector<int>&);
  std::vector<int> TopSortNoCycles();
  std::vector<int> TopSort();

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  auto SCC();
  void Transpose();
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].emplace_back(u);
}

auto Graph::DFS(const std::vector<int>& order) {
  std::vector<int> color(size_);
  std::vector<std::vector<int>> components;
  for (const auto& v : order) {
    if (color[v] == 0) {
      components.emplace_back();
      DFSVisit(v, color, components.back());
    }
  }
  return components;
}

void Graph::DFSVisit(const int& v, std::vector<int>& color, std::vector<int>& component) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 0) {
      DFSVisit(u, color, component);
    }
  }
  color[v] = 2;
  component.push_back(v);
}

void Graph::DFSVisitNoCycles(const int& v, std::vector<int>& color, std::vector<int>& component) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 0) {
      DFSVisitNoCycles(u, color, component);
    }
  }
  color[v] = 2;
  component.push_back(v);
}

std::vector<int> Graph::TopSortNoCycles() {
  std::vector<int> color(size_);
  std::vector<int> top_sort_no_cycles;
  top_sort_no_cycles.reserve(size_);
  for (int v = 0; v < size_; ++v) {
    if (color[v] == 0) {
      DFSVisitNoCycles(v, color, top_sort_no_cycles);
    }
  }
  std::reverse(top_sort_no_cycles.begin(), top_sort_no_cycles.end());
  return top_sort_no_cycles;
}

void Graph::Transpose() {
  std::vector<std::vector<int>> new_adj(size_);
  for (int i = 0; i < size_; ++i) {
    for (const auto& u : adj_[i]) {
      new_adj[u].push_back(i);
    }
  }
  adj_ = std::move(new_adj);
}

auto Graph::SCC() {
  std::vector<int> order = TopSortNoCycles();
  Transpose();
  std::vector<std::vector<int>> components = DFS(order);
  return components;
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
  std::vector<std::vector<int>> scc = graph.SCC();
  std::cout << scc.size() << '\n';
  std::vector<int> answer(n);
  int k = scc.size();
  for (int i = 0; i < k; ++i) {
    for (const auto& element : scc[i]) {
      answer[element] = i;
    }
  }
  for (const auto& it : answer) {
    std::cout << it + 1 << ' ';
  }
}