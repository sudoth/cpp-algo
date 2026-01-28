#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  void DFS(const int&, const std::pair<int, int>&, std::vector<int>&, std::vector<int>&, std::vector<int>&,
           std::vector<int>&, int&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  std::vector<int> FindBridges(const int&);
};

void Graph::AddEdge(const int& v, const int& u, const int& i) {
  adj_[v].emplace_back(std::pair<int, int>(u, i));
}

void Graph::DFS(const int& v, const std::pair<int, int>& p, std::vector<int>& color, std::vector<int>& time_in,
                std::vector<int>& time_up, std::vector<int>& bridges, int& time) {
  color[v] = 1;
  time_in[v] = time_up[v] = ++time;
  for (const auto& u : adj_[v]) {
    if (u.first == p.first) {
      if (u.second != p.second) {
        bridges[u.second] = 2;
        bridges[p.second] = 2;
      }
      continue;
    }
    if (color[u.first] == 1) {
      time_up[v] = std::min(time_up[v], time_in[u.first]);
    }
    if (color[u.first] == 0) {
      DFS(u.first, std::pair(v, u.second), color, time_in, time_up, bridges, time);
      time_up[v] = std::min(time_up[v], time_up[u.first]);
      if (time_in[v] < time_up[u.first] && bridges[u.second] != 2) {
        bridges[u.second] = 1;
      }
    }
  }
  color[v] = 2;
}

std::vector<int> Graph::FindBridges(const int& m) {
  std::vector<int> color(size_);
  std::vector<int> time_in(size_, -1);
  std::vector<int> time_up(size_, -1);
  std::vector<int> bridges(m);
  int time = -1;
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      DFS(i, std::pair<int, int>(-1, -1), color, time_in, time_up, bridges, time);
    }
  }
  return bridges;
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
    graph.AddEdge(u, v, i);
    graph.AddEdge(v, u, i);
  }
  std::vector<int> bridges = graph.FindBridges(m);
  int k = bridges.size();
  std::cout << std::count(bridges.begin(), bridges.end(), 1) << '\n';
  for (int i = 0; i < k; ++i) {
    if (bridges[i] == 1) {
      std::cout << i + 1 << ' ';
    }
  }
}