#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  void DFS(const int&, std::vector<int>&, int&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  int CyclesNumber();
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].emplace_back(u);
}

void Graph::DFS(const int& v, std::vector<int>& color, int& count) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u] == 1) {
      count++;
    }
    if (color[u] == 0) {
      this->DFS(u, color, count);
    }
  }
  color[v] = 2;
}

int Graph::CyclesNumber() {
  int count = 0;
  std::vector<int> color(size_);
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      this->DFS(i, color, count);
    }
  }
  return count;
}

int main() {
  int n;
  std::cin >> n;
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    int u;
    std::cin >> u;
    --u;
    graph.AddEdge(u, i);
  }
  std::cout << graph.CyclesNumber();
}