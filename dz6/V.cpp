#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct Edge {
  Edge() = default;
  Edge(const int& v, const int& w, const int& t) : v_(v), w_(w), t_(t) {
  }
  int v_;
  int w_;
  int t_;
};

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    adj.resize(n);
    parent.resize(n, -1);
  }
  std::vector<int> parent;
  std::vector<std::vector<Edge>> adj;
};

auto Dijkstra(Graph& graph, const int& t) {
  std::vector<int> dist(graph.adj.size(), INT32_MAX);
  std::vector<int> dist_time(graph.adj.size(), INT32_MAX);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  dist_time[0] = 0;
  dist[0] = 0;
  queue.emplace(0, 0);
  while (!queue.empty()) {
    auto top = queue.top();
    int w = top.first;
    int v = top.second;
    queue.pop();
    if (w > dist[v]) {
      continue;
    }
    for (const auto& u : graph.adj[v]) {
      if (t >= dist_time[v] + u.t_ && dist[u.v_] > dist[v] + u.w_) {
        dist[u.v_] = dist[v] + u.w_;
        dist_time[u.v_] = dist_time[v] + u.t_;
        graph.parent[u.v_] = v;
        queue.emplace(dist[u.v_], u.v_);
      }
    }
  }
  return std::make_pair(dist, dist_time);
}

int main() {
  int n = 0;
  int m = 0;
  int t = 0;

  std::cin >> n >> m >> t;

  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    int time = 0;
    std::cin >> u >> v >> w >> time;
    --u;
    --v;
    graph.adj[u].emplace_back(v, w, time);
    graph.adj[v].emplace_back(u, w, time);
  }

  auto dist = Dijkstra(graph, t);
  if (dist.second[n - 1] <= t) {
    std::cout << dist.first[n - 1] << '\n';
    std::vector<int> path;
    for (int i = n - 1; i != -1; i = graph.parent[i]) {
      path.push_back(i);
    }
    std::reverse(path.begin(), path.end());
    std::cout << path.size() << '\n';
    for (const auto& p : path) {
      std::cout << p + 1 << " ";
    }
  } else {
    std::cout << -1;
  }
}