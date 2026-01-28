#include <iostream>
#include <vector>

struct Edge {
  Edge() = default;
  Edge(const int& v, const int& capacity) : v_(v), flow_(0), capacity_(capacity) {
  }
  int v_;
  int flow_;
  int capacity_;
};

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    used.resize(n);
    adj.resize(n);
  }
  int vertices;
  std::vector<bool> used;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> adj;
};

int DFS(Graph& graph, const int& v, int min_delta_flow) {
  if (graph.used[v]) {
    return 0;
  }
  if (v == graph.vertices - 1) {
    return min_delta_flow;
  }
  graph.used[v] = true;
  for (const auto& i : graph.adj[v]) {
    if (!graph.used[graph.edges[i].v_] && graph.edges[i].flow_ < graph.edges[i].capacity_) {
      int delta_flow =
          DFS(graph, graph.edges[i].v_, std::min(min_delta_flow, graph.edges[i].capacity_ - graph.edges[i].flow_));
      if (delta_flow > 0) {
        graph.edges[i].flow_ += delta_flow;
        graph.edges[i % 2 == 0 ? i + 1 : i - 1].flow_ -= delta_flow;
        return delta_flow;
      }
    }
  }
  return 0;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int capacity = 0;
    std::cin >> u >> v >> capacity;
    --u;
    --v;
    graph.adj[u].push_back(2 * i);
    graph.edges.emplace_back(v, capacity);
    graph.adj[v].push_back(2 * i + 1);
    graph.edges.emplace_back(u, 0);
  }

  int delta_flow = INT32_MAX;
  while (delta_flow > 0) {
    delta_flow = DFS(graph, 0, INT32_MAX);
    graph.used.clear();
    graph.used.resize(n);
  }

  int max_flow = 0;
  for (const auto& i : graph.adj[0]) {
    max_flow += graph.edges[i].flow_;
  }
  std::cout << max_flow;
}