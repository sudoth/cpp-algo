#include <iostream>
#include <vector>
#include <queue>
#include <type_traits>

struct Note {
  char symbol;
  int vertex;
};

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
  void Add(const int&, const int&, const int&);
  void AddEdges(const char&, const int&, const int&, int&);
};

void Graph::Add(const int& from, const int& to, const int& capacity) {
  int edge_size = static_cast<int>(edges.size());
  adj[from].push_back(edge_size);
  edges.emplace_back(to, capacity);
  adj[to].push_back(edge_size + 1);
  edges.emplace_back(from, 0);
}

void Graph::AddEdges(const char& symbol, const int& from, const int& to, int& flow) {
  if (symbol == 'H') {
    Add(from, to, 1);
    flow += 1;
  }
  if (symbol == 'O') {
    Add(from, to, 2);
    flow += 2;
  }
  if (symbol == 'N') {
    Add(from, to, 3);
    flow += 3;
  }
  if (symbol == 'C') {
    Add(from, to, 4);
    flow += 4;
  }
}

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

int FordFalkerson(Graph& graph) {
  int delta_flow = INT32_MAX;
  while (delta_flow > 0) {
    delta_flow = DFS(graph, 0, INT32_MAX);
    graph.used.clear();
    graph.used.resize(graph.vertices);
  }

  int max_flow = 0;
  for (const auto& i : graph.adj[0]) {
    max_flow += graph.edges[i].flow_;
  }
  return max_flow;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Note>> note(n);
  int size = 0;
  for (int i = 0; i < n; ++i) {
    note[i].resize(m);
    for (int j = 0; j < m; ++j) {
      std::cin >> note[i][j].symbol;
      if (note[i][j].symbol != '.') {
        note[i][j].vertex = size + 1;
        ++size;
      }
    }
  }

  if (size < 2) {
    std::cout << "Invalid";
    return 0;
  }

  int flow_in = 0;
  int flow_out = 0;
  Graph graph(size + 2);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (note[i][j].symbol == '.') {
        continue;
      }

      if ((i + j) % 2 == 0) {
        graph.AddEdges(note[i][j].symbol, 0, note[i][j].vertex, flow_in);
        if (j + 1 < m && note[i][j + 1].symbol != '.') {
          graph.Add(note[i][j].vertex, note[i][j + 1].vertex, 1);
        }
        if (j - 1 >= 0 && note[i][j - 1].symbol != '.') {
          graph.Add(note[i][j].vertex, note[i][j - 1].vertex, 1);
        }
        if (i + 1 < n && note[i + 1][j].symbol != '.') {
          graph.Add(note[i][j].vertex, note[i + 1][j].vertex, 1);
        }
        if (i - 1 >= 0 && note[i - 1][j].symbol != '.') {
          graph.Add(note[i][j].vertex, note[i - 1][j].vertex, 1);
        }
        continue;
      }

      if ((i + j) % 2 != 0) {
        graph.AddEdges(note[i][j].symbol, note[i][j].vertex, graph.vertices - 1, flow_out);
      }
    }
  }

  if (flow_in != flow_out) {
    std::cout << "Invalid";
    return 0;
  }

  int max_flow = FordFalkerson(graph);

  if (max_flow == flow_in) {
    std::cout << "Valid";
  } else {
    std::cout << "Invalid";
  }
}