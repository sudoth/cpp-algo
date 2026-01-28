#include <iostream>
#include <vector>
#include <cmath>

struct Node {
  int max_subscribers;
  int counter;
  int promise;
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
      return {a.max_subscribers, a.counter, 0};
    }
    if (a.max_subscribers < b.max_subscribers) {
      return {b.max_subscribers, b.counter, 0};
    }
    return {a.max_subscribers, a.counter + b.counter, 0};
  }

  void Push(int i) {
    segment_tree_[Left(i)].promise += segment_tree_[i].promise;
    segment_tree_[Right(i)].promise += segment_tree_[i].promise;
    segment_tree_[i].promise = 0;
  }

 public:
  void Update(int q_left, int q_right, int left, int right, int i, int value) {
    if (q_left > right || q_right < left) {
      return;
    }
    if (q_left <= left && q_right >= right) {
      segment_tree_[i].promise += value;
      return;
    }

    Push(i);
    int mid = (left + right) / 2;
    Update(q_left, q_right, left, mid, Left(i), value);
    Update(q_left, q_right, mid + 1, right, Right(i), value);

    segment_tree_[i].max_subscribers =
        std::max(segment_tree_[Left(i)].max_subscribers + segment_tree_[Left(i)].promise,
                 segment_tree_[Right(i)].max_subscribers + segment_tree_[Right(i)].promise);
  }

  explicit SegmentTree(const int& n) {
    segment_tree_ = std::vector<Node>(2 * (1 << (static_cast<int>(log2(n)) + 1)) - 1, {INT32_MIN, 1, 0});
  }

  void Build(const std::vector<int>& values, int left, int right, int i) {
    if (left == right) {
      segment_tree_[i].max_subscribers = values[left];
      segment_tree_[i].counter = 1;
      segment_tree_[i].promise = 0;
      return;
    }

    int mid = (left + right) / 2;

    Build(values, left, mid, Left(i));
    Build(values, mid + 1, right, Right(i));
    segment_tree_[i] = Combine(segment_tree_[Left(i)], segment_tree_[Right(i)]);
  }

  int Query(int q_left, int q_right, int left, int right, int i) {
    if (q_left > right || q_right < left) {
      return INT32_MIN;
    }
    if (q_left <= left && q_right >= right) {
      return segment_tree_[i].max_subscribers + segment_tree_[i].promise;
    }
    Push(i);
    int mid = (left + right) / 2;
    int ans = std::max(Query(q_left, q_right, left, mid, Left(i)), Query(q_left, q_right, mid + 1, right, Right(i)));
    segment_tree_[i].max_subscribers =
        std::max(segment_tree_[Left(i)].max_subscribers + segment_tree_[Left(i)].promise,
                 segment_tree_[Right(i)].max_subscribers + segment_tree_[Right(i)].promise);
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;

  std::vector<int> values(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> values[i];
  }
  SegmentTree segment_tree(n);
  segment_tree.Build(values, 0, n - 1, 0);

  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    char type = 0;
    std::cin >> type;
    if (type == 'm') {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      int result = segment_tree.Query(left - 1, right - 1, 0, n - 1, 0);
      std::cout << result << '\n';
    }
    if (type == 'a') {
      int left = 0;
      int right = 0;
      int value = 0;
      std::cin >> left >> right >> value;
      segment_tree.Update(left - 1, right - 1, 0, n - 1, 0, value);
    }
  }
}