#include <iostream>
#include <vector>

struct Edge {
  Edge() = default;
  Edge(const int& u, const int& v, const int& w) : u_(u), v_(v), w_(w) {
  }
  int u_;
  int v_;
  int w_;
};

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) : vertices(n) {
  }
  int vertices;
  std::vector<Edge> edges;
};

auto BellmanFord(const Graph& graph) {
  std::vector<int> dist(graph.vertices, 30000);
  dist[0] = 0;
  for (int i = 0; i < graph.vertices - 1; ++i) {
    for (const auto& edge : graph.edges) {
      if (dist[edge.u_] < 30000) {
        dist[edge.v_] = std::min(dist[edge.v_], dist[edge.u_] + edge.w_);
      }
    }
  }
  return dist;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    graph.edges.emplace_back(u, v, w);
  }
  auto distance = BellmanFord(graph);
  for (const auto& dist : distance) {
    std::cout << dist << " ";
  }
}