#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  bool DFSCycle(const int&, const std::pair<int, int>&, std::vector<int>&);
  void DFSSCC(const int&, std::vector<int>&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  bool HasCycle();
  bool IsOneSCC();
  bool CarbonCorrect(std::vector<char>&);
};

void Graph::AddEdge(const int& v, const int& u, const int& w) {
  adj_[v].emplace_back(std::pair<int, int>(u, w));
}

bool Graph::DFSCycle(const int& v, const std::pair<int, int>& p, std::vector<int>& color) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (v == u.first) {
      return true;
    }
    if (u.first == p.first) {
      if (u.second != p.second) {
        return true;
      }
      continue;
    }
    if (color[u.first] == 1) {
      return true;
    }
    if (color[u.first] == 0) {
      if (DFSCycle(u.first, std::pair(v, u.second), color)) {
        return true;
      }
    }
  }
  color[v] = 2;
  return false;
}

bool Graph::HasCycle() {
  std::vector<int> color(size_);
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      if (this->DFSCycle(i, std::pair(-1, -1), color)) {
        return true;
      }
    }
  }
  return false;
}

void Graph::DFSSCC(const int& v, std::vector<int>& color) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u.first] == 0) {
      DFSSCC(u.first, color);
    }
  }
  color[v] = 2;
}

bool Graph::IsOneSCC() {
  std::vector<int> color(size_);
  DFSSCC(0, color);
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      return false;
    }
  }
  return true;
}

bool Graph::CarbonCorrect(std::vector<char>& atom_type) {
  if (size_ == 2) {
    if (atom_type[0] == 'H' && atom_type[1] == 'H') {
      return false;
    }
  }
  for (int i = 0; i < size_; ++i) {
    if (atom_type[i] == 'C' && adj_[i].size() != 4) {
      return false;
    }
    if (atom_type[i] == 'H' && adj_[i].size() != 1) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  std::vector<char> atom_type(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> atom_type[i];
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph.AddEdge(u, v, i);
    graph.AddEdge(v, u, i);
  }
  if (!graph.IsOneSCC()) {
    std::cout << "NO";
    return 0;
  }
  if (graph.HasCycle()) {
    std::cout << "NO";
    return 0;
  }
  if (!graph.CarbonCorrect(atom_type)) {
    std::cout << "NO";
    return 0;
  }
  std::cout << "YES";
  return 0;
}