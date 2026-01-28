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

auto BellmanFord(const Graph& graph, const int& s, const int& k) {
  std::vector<std::vector<int>> dist(k + 1, std::vector<int>(graph.vertices, INT32_MAX));
  dist[0][s] = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < graph.vertices - 1; ++j) {
      for (const auto& edge : graph.edges) {
        if (dist[i][edge.u_] < INT32_MAX) {
          dist[i + 1][edge.v_] = std::min(dist[i + 1][edge.v_], dist[i][edge.u_] + edge.w_);
        }
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  int k = 0;
  int s = 0;
  int f = 0;

  std::cin >> n >> m >> k >> s >> f;
  --s;
  --f;

  std::vector<std::vector<int>> matrix(n, std::vector<int>(n, INT32_MAX));

  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    if (w < matrix[u][v]) {
      matrix[u][v] = w;
    }
  }

  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] < INT32_MAX) {
        graph.edges.emplace_back(i, j, matrix[i][j]);
      }
    }
  }

  auto dist = BellmanFord(graph, s, k);

  int min = INT32_MAX;
  for (int i = 0; i < k + 1; ++i) {
    if (min > dist[i][f]) {
      min = dist[i][f];
    }
  }

  min == INT32_MAX ? std::cout << -1 : std::cout << min;
}