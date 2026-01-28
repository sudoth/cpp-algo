#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    adj.resize(n);
  }
  std::vector<std::vector<std::pair<int, int>>> adj;
};

std::vector<int> Dijkstra(const Graph& graph, const int& start) {
  std::vector<int> dist(graph.adj.size(), INT32_MAX);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  dist[start] = 0;
  queue.emplace(0, start);
  while (!queue.empty()) {
    auto top = queue.top();
    int w = top.first;
    int v = top.second;
    queue.pop();
    if (w > dist[v]) {
      continue;
    }
    for (const auto& u : graph.adj[v]) {
      if (dist[v] + u.second < dist[u.first]) {
        dist[u.first] = dist[v] + u.second;
        queue.emplace(dist[u.first], u.first);
      }
    }
  }
  return dist;
}

bool Find(std::vector<std::pair<int, int>> teleports, int tp_size, int tp) {
  for (int i = 0; i < tp_size; ++i) {
    if (teleports[i].first == tp) {
      return true;
    }
  }
  return false;
}

bool Cmp(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  return a.first < b.first;
}

int main() {
  int n = 0;
  int up = 0;
  int down = 0;
  int in = 0;
  int out = 0;
  int l = 0;

  std::cin >> n >> up >> down >> in >> out >> l;

  if (l == 0) {
    std::cout << (n - 1) * up;
    return 0;
  }

  int tp_size = 1;
  const int max_size = 1000;
  Graph graph(max_size);
  std::vector<std::pair<int, int>> teleports;
  for (int i = 0; i < l; ++i) {
    int k = 0;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      int tp = 0;
      std::cin >> tp;
      --tp;
      teleports.emplace_back(tp, tp_size);
      ++tp_size;
    }
    for (int t = 0; t < k; ++t) {
      for (int j = t + 1; j < k; ++j) {
        graph.adj[teleports[t].second].emplace_back(teleports[j].second, in + out);
        graph.adj[teleports[j].second].emplace_back(teleports[t].second, in + out);
      }
    }
  }

  std::sort(teleports.begin(), teleports.end(), Cmp);

  if (teleports[0].first >= n - 1) {
    std::cout << (n - 1) * up;
    return 0;
  }

  int start = 0;
  int final = tp_size + 1;

  if (teleports[0].first == 0) {
    start = teleports[0].second;
  }

  if (teleports.back().first == n - 1) {
    final = teleports.back().second;
  }

  if (teleports[0].first < n - 1 && teleports[0].first != 0) {
    graph.adj[start].emplace_back(teleports[start].second, teleports[start].first * up);
    graph.adj[teleports[start].second].emplace_back(start, teleports[start].first * down);
  }

  bool flag = true;
  for (int i = 0; i < tp_size - 1; ++i) {
    if (teleports[i + 1].first > n - 1 && teleports[i].first < n - 1 && flag) {
      graph.adj[teleports[i].second].emplace_back(final, (n - 1 - teleports[i].first) * up);
      graph.adj[final].emplace_back(teleports[i].second, (n - 1 - teleports[i].first) * down);
      graph.adj[final].emplace_back(teleports[i + 1].second, (teleports[i + 1].first - n + 1) * up);
      graph.adj[teleports[i + 1].second].emplace_back(final, (teleports[i + 1].first - n + 1) * down);
      flag = false;
      continue;
    }
    graph.adj[teleports[i].second].emplace_back(teleports[i + 1].second, (teleports[i + 1].first - teleports[i].first) * up);
    graph.adj[teleports[i + 1].second].emplace_back(teleports[i].second, (teleports[i + 1].first - teleports[i].first) * down);
  }

  if (teleports.back().first < n - 1) {
    graph.adj[teleports.back().second].emplace_back(final, (n - 1 - teleports.back().first) * up);
    graph.adj[final].emplace_back(teleports.back().second, (n - 1 - teleports.back().first) * down);
  }

  auto dist = Dijkstra(graph, start);
  std::cout << dist[final];
}