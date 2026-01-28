#include <iostream>
#include <vector>
#include <cmath>

struct Node {
  int max_subscribers;
  int counter;
};

class SegmentTree {
  std::vector<Node> segment_tree_;

  int Left(int i) {
    return 2 * i + 1;
  }
  int Right(int i) {
    return 2 * i + 2;
  }

  Node Combine(Node a, Node b) {
    if (a.max_subscribers > b.max_subscribers) {
      return {a.max_subscribers, a.counter};
    }
    if (a.max_subscribers < b.max_subscribers) {
      return {b.max_subscribers, b.counter};
    }
    return {a.max_subscribers, a.counter + b.counter};
  }

 public:
  explicit SegmentTree(const int& n) {
    segment_tree_ = std::vector<Node>(2 * (1 << (static_cast<int>(log2(n)) + 1)) - 1, {INT32_MIN, 1});
  }

  void Build(const std::vector<int>& values, int left, int right, int i) {
    if (left == right) {
      segment_tree_[i].max_subscribers = values[left];
      segment_tree_[i].counter = 1;
      return;
    }

    int mid = (left + right) / 2;

    Build(values, left, mid, Left(i));
    Build(values, mid + 1, right, Right(i));
    segment_tree_[i] = Combine(segment_tree_[Left(i)], segment_tree_[Right(i)]);
  }

  Node Query(int q_left, int q_right, int left, int right, int i) {
    if (q_left > right || q_right < left) {
      return {INT32_MIN, 1};
    }
    if (q_left <= left && q_right >= right) {
      return segment_tree_[i];
    }
    int mid = (left + right) / 2;
    auto left_node = Query(q_left, q_right, left, mid, Left(i));
    auto right_node = Query(q_left, q_right, mid + 1, right, Right(i));
    return Combine(left_node, right_node);
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> subscribers(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> subscribers[i];
  }
  SegmentTree segment_tree(n);
  segment_tree.Build(subscribers, 0, n - 1, 0);

  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int left = 0;
    int right = 0;
    std::cin >> left >> right;
    auto result = segment_tree.Query(left - 1, right - 1, 0, n - 1, 0);
    std::cout << result.max_subscribers << ' ' << result.counter << '\n';
  }
}