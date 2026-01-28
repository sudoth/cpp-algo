#include <iostream>
#include <vector>
#include <queue>

auto BFS(const std::vector<int>& s, const int& m, const int& n) {
  std::vector<int> dist((m + 2) * (n + 2), -1);
  std::queue<int> q;
  int p = s.size();
  for (int i = 0; i < p; ++i) {
    if (s[i] == 1) {
      q.push(i);
      dist[i] = 0;
    }
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v < m + 2 || v % (m + 2) == 0 || v % (m + 2) == m + 1 || v >= (m + 2) * (n + 1)) {
      continue;
    }
    if (dist[v + 1] == -1) {
      dist[v + 1] = dist[v] + 1;
      q.push(v + 1);
    }
    if (dist[v - 1] == -1) {
      dist[v - 1] = dist[v] + 1;
      q.push(v - 1);
    }
    if (dist[v + m + 2] == -1) {
      dist[v + m + 2] = dist[v] + 1;
      q.push(v + m + 2);
    }
    if (dist[v - m - 2] == -1) {
      dist[v - m - 2] = dist[v] + 1;
      q.push(v - m - 2);
    }
  }
  return dist;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  int k = (n + 2) * (m + 2);
  std::vector<int> subway(k);
  for (int i = 0; i < k; ++i) {
    if (i < m + 2 || i % (m + 2) == 0 || i % (m + 2) == m + 1 || i >= (m + 2) * (n + 1)) {
      continue;
    }
    std::cin >> subway[i];
  }
  std::vector<int> dist = BFS(subway, m, n);
  int p = dist.size();
  for (int i = 0; i < p; ++i) {
    if (i < m + 2 || i % (m + 2) == 0 || i % (m + 2) == m + 1 || i >= (m + 2) * (n + 1)) {
      continue;
    }
    std::cout << dist[i] << ' ';
    if (i % (m + 2) == m) {
      std::cout << '\n';
    }
  }
}