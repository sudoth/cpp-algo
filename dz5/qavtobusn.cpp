#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  void DFS(const int&, std::vector<int>&);
  void EulerDFS(const int&, std::vector<int>&, std::vector<int>&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  bool Connected(const int&);
  std::vector<int> EulerTour(const int&);
};

void Graph::AddEdge(const int& v, const int& u, const int& w) {
  adj_[v].emplace_back(std::pair<int, int>(u, w));
}

void Graph::DFS(const int& v, std::vector<int>& color) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u.first] == 0) {
      DFS(u.first, color);
    }
  }
  color[v] = 2;
}

bool Graph::Connected(const int& w) {
  std::vector<int> color(size_);
  DFS(w, color);
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0 && !adj_[i].empty()) {
      return false;
    }
  }
  return true;
}

void Graph::EulerDFS(const int& v, std::vector<int>& path, std::vector<int>& first) {
  while (first[v] < static_cast<int>(adj_[v].size())) {
    int u = adj_[v][first[v]].first;
    int i = adj_[v][first[v]].second;
    ++first[v];
    if (i == 1) {
      i = 0;
      EulerDFS(u, path, first);
    }
  }
  path.push_back(v);
}

std::vector<int> Graph::EulerTour(const int& w) {
  std::vector<int> path;
  std::vector<int> first(100001);
  EulerDFS(w, path, first);
  return path;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  Graph graph(100001);
  int w = 100001;
  for (int j = 0; j < n; ++j) {
    int k;
    std::cin >> k;
    int u, v;
    std::cin >> u;
    --u;
    if (u < w) {
      w = u;
    }
    for (int i = 0; i < k; ++i) {
      std::cin >> v;
      --v;
      if (v < w) {
        w = v;
      }
      graph.AddEdge(u, v, 1);
      graph.AddEdge(v, u, 0);
      u = v;
    }
  }
  if (n == 0 || !graph.Connected(w)) {
    std::cout << 0;
    return 0;
  }
  std::vector<int> path = graph.EulerTour(w);
  std::cout << path.size() << ' ';
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    std::cout << *it + 1 << ' ';
  }
}