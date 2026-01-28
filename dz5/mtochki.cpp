#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  void DFS(const int&, std::vector<int>&, std::vector<int>&, std::vector<int>&, std::vector<bool>&, int&, bool);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  std::vector<bool> FindAP();
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].emplace_back(u);
}

void Graph::DFS(const int& v, std::vector<int>& color, std::vector<int>& time_in, std::vector<int>& time_up,
                std::vector<bool>& ap, int& time, bool is_root = false) {
  color[v] = 1;
  time_in[v] = time_up[v] = ++time;
  int children = 0;
  for (const auto& u : adj_[v]) {
    if (color[u] == 1) {
      time_up[v] = std::min(time_up[v], time_in[u]);
    }
    if (color[u] == 0) {
      ++children;
      DFS(u, color, time_in, time_up, ap, time);
      time_up[v] = std::min(time_up[v], time_up[u]);
      if (!is_root && (time_in[v] <= time_up[u])) {
        ap[v] = true;
      }
    }
  }
  if (is_root && children > 1) {
    ap[v] = true;
  }
  color[v] = 2;
}

std::vector<bool> Graph::FindAP() {
  std::vector<int> color(size_);
  std::vector<int> time_in(size_, -1);
  std::vector<int> time_up(size_, -1);
  std::vector<bool> ap(size_);
  int time = -1;
  for (int i = 4; i < size_; ++i) {
    if (color[i] == 0) {
      DFS(i, color, time_in, time_up, ap, time, true);
    }
  }
  return ap;
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
    graph.AddEdge(v, u);
  }
  std::vector<bool> ap = graph.FindAP();
  int k = ap.size();
  std::cout << std::count(ap.begin(), ap.end(), true) << '\n';
  for (int i = 0; i < k; ++i) {
    if (ap[i]) {
      std::cout << i + 1 << ' ';
    }
  }
}