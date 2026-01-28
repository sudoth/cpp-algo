#include <iostream>
#include <vector>
#include <queue>

int BFS(const int& s, const std::vector<int>& height, std::vector<int>& used, const int& m, const int& n) {
  std::queue<int> q;
  q.push(s);
  int c = 1;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v < m + 2 || v % (m + 2) == 0 || v % (m + 2) == m + 1 || v >= (m + 2) * (n + 1)) {
      continue;
    }
    if (used[v] == 1) {
      continue;
    }
    used[v] = 1;
    if (height[v + 1] < height[v]) {
      c = 0;
    }
    if (height[v - 1] < height[v]) {
      c = 0;
    }
    if (height[v + m + 2] < height[v]) {
      c = 0;
    }
    if (height[v - m - 2] < height[v]) {
      c = 0;
    }
    if (height[v + 1] == height[v] && used[v + 1] == 0) {
      q.push(v + 1);
    }
    if (height[v - 1] == height[v] && used[v - 1] == 0) {
      q.push(v - 1);
    }
    if (height[v + m + 2] == height[v] && used[v + m + 2] == 0) {
      q.push(v + m + 2);
    }
    if (height[v - m - 2] == height[v] && used[v - m - 2] == 0) {
      q.push(v - m - 2);
    }
  }
  return c;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  int k = (n + 2) * (m + 2);
  std::vector<int> height(k, 10001);
  std::vector<int> used(k);
  for (int i = 0; i < k; ++i) {
    if (i < m + 2 || i % (m + 2) == 0 || i % (m + 2) == m + 1 || i >= (m + 2) * (n + 1)) {
      continue;
    }
    std::cin >> height[i];
  }
  std::vector<int> count(k);
  for (int i = 0; i < k; ++i) {
    if (height[i] != 10001 && used[i] == 0) {
      count[i] = BFS(i, height, used, m, n);
    } else {
      count[i] = 0;
    }
  }
  int counter = 0;
  for (int i = 0; i < k; ++i) {
    counter += count[i];
  }
  std::cout << counter;
}