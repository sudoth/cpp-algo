#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int size_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  void DFS(const int&, const std::pair<int, int>&, std::vector<int>&, std::vector<int>&, std::vector<int>&,
           std::vector<int>&, int&);
  void DFS(const int&, const int&, std::vector<int>&, const std::vector<int>&, std::vector<int>&);
  void DFS(const int&, int&, std::vector<int>&);

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  int FindBridges(const int&);
  Graph SCC(const std::vector<int>&);
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

void Graph::DFS(const int& k, const int& v, std::vector<int>& color, const std::vector<int>& bridges,
                std::vector<int>& scc_mn) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u.first] == 0 && bridges[u.second] != 1) {
      DFS(k, u.first, color, bridges, scc_mn);
    }
  }
  scc_mn[v] = k;
  color[v] = 2;
}

Graph Graph::SCC(const std::vector<int>& bridges) {
  std::vector<int> scc_mn(size_);
  std::vector<int> color(size_);
  int k = 0;
  for (int i = 0; i < size_; ++i) {
    if (color[i] == 0) {
      DFS(k, i, color, bridges, scc_mn);
      ++k;
    }
  }
  Graph scc(k);
  for (int v = 0; v < size_; ++v) {
    for (const auto& u : adj_[v]) {
      if (bridges[u.second] == 1) {
        scc.AddEdge(scc_mn[v], scc_mn[u.first], 0);
      }
    }
  }
  return scc;
}

void Graph::DFS(const int& v, int& k, std::vector<int>& color) {
  color[v] = 1;
  for (const auto& u : adj_[v]) {
    if (color[u.first] == 0) {
      DFS(u.first, k, color);
    }
  }
  color[v] = 2;
  if (adj_[v].empty()) {
    k += 2;
  }
  if (adj_[v].size() == 1) {
    ++k;
  }
}

int Graph::FindBridges(const int& m) {
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

  Graph scc = SCC(bridges);
  std::vector<int> ends;
  for (int i = 0; i < scc.size_; ++i) {
    color[i] = 0;
  }
  int k = 0;
  for (int i = 0; i < scc.size_; ++i) {
    if (color[i] == 0) {
      scc.DFS(i, k, color);
      ends.push_back(k);
    }
  }
  if (scc.size_ == 1) {
    return 0;
  }
  return k;
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
  std::cout << (graph.FindBridges(m) + 1) / 2;
}