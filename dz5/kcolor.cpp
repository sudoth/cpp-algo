#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

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
  bool HasCycle();
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

bool Graph::HasCycle() {
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
        return true;
      }
    }
  }
  return false;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n;
  std::cin >> n;
  Graph graph(n);
  for (int i = 0; i < n - 1; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = i + 1; j < n; ++j) {
      if (s[j - i - 1] == 'R') {
        graph.AddEdge(j, i);
      } else {
        graph.AddEdge(i, j);
      }
    }
  }
  std::cout << (graph.HasCycle() ? "NO" : "YES");
}