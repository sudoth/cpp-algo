#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
  Edge() = default;
  Edge(const int& from, const int& time_in, const int& to, const int& time_out) {
    from_ = from;
    time_in_ = time_in;
    to_ = to;
    time_out_ = time_out;
  }
  int from_;
  int time_in_;
  int to_;
  int time_out_;
};

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
  }
  int vertices;
  std::vector<Edge> edges;
};

auto BellmanFord(const Graph& graph, const int& s) {
  std::vector<int> time(graph.vertices, INT32_MAX);
  time[s] = 0;
  for (int i = 0; i < graph.vertices; ++i) {
    for (const auto& edge : graph.edges) {
      if (time[edge.from_] < INT32_MAX) {
        if (time[edge.from_] <= edge.time_in_) {
          time[edge.to_] = std::min(time[edge.to_], edge.time_out_);
        }
      }
    }
  }
  return time;
}

bool Cmp(const Edge& edge1, const Edge& edge2) {
  return edge1.time_in_ > edge2.time_in_;
}

int main() {
  int n = 0;
  int a = 0;
  int b = 0;
  int k = 0;

  std::cin >> n >> a >> b >> k;
  --a;
  --b;

  Graph graph(n);
  for (int i = 0; i < k; ++i) {
    int from = 0;
    int time_in = 0;
    int to = 0;
    int time_out = 0;
    std::cin >> from >> time_in >> to >> time_out;
    --from;
    --to;
    graph.edges.emplace_back(from, time_in, to, time_out);
  }

  std::sort(graph.edges.begin(), graph.edges.end(), Cmp);

  auto time = BellmanFord(graph, a);
  std::cout << time[b];
}