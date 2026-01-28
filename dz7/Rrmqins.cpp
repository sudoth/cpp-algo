#include <iostream>
#include <random>
#include <memory>

struct Node {
  int key;
  int priority;
  int quantity;
  int minimum;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  explicit Node(const int& n) : key(n), priority(rand()), quantity(1), minimum(n), left(nullptr), right(nullptr) {
  }
};

class Treap {
  std::shared_ptr<Node> treap_;

  int Count(std::shared_ptr<Node> root) {
    return root ? root->quantity : 0;
  }

  int Min(std::shared_ptr<Node> root) {
    return root ? root->minimum : INT32_MAX;
  }

  void UpdateCount(std::shared_ptr<Node> root) {
    if (root) {
      root->quantity = 1 + Count(root->left) + Count(root->right);
      root->minimum = std::min(root->key, std::min(Min(root->left), Min(root->right)));
    }
  }

 public:
  explicit Treap(std::shared_ptr<Node> node) : treap_(node) {
  }

  std::shared_ptr<Node> Root() {
    return treap_;
  }

  int Size(std::shared_ptr<Node> node) {
    return node ? node->quantity : 0;
  }

  std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> root, const int& key) {
    if (!root) {
      return {nullptr, nullptr};
    }
    if (key <= Size(root->left)) {
      auto [t1, t2] = Split(root->left, key);
      root->left = t2;
      UpdateCount(root);
      return {t1, root};
    }
    auto [t1, t2] = Split(root->right, key - Size(root->left) - 1);
    root->right = t1;
    UpdateCount(root);
    return {root, t2};
  }

  std::shared_ptr<Node> Merge(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    if (!left || !right) {
      return left ? left : right;
    }
    if (left->priority < right->priority) {
      left->right = Merge(left->right, right);
      UpdateCount(left);
      return left;
    }
    right->left = Merge(left, right->left);
    UpdateCount(right);
    return right;
  }

  void Permutation(const int& i, const int& x) {
    auto splitted = Split(treap_, i);
    treap_ = Merge(Merge(splitted.first, std::make_shared<Node>(x)), splitted.second);
  }

  int MinValue(const int& left, const int& right) {
    auto splitted1 = Split(treap_, left);
    auto splitted2 = Split(splitted1.second, right - left + 1);
    int min_value = Min(splitted2.first);
    treap_ = Merge(Merge(splitted1.first, splitted2.first), splitted2.second);
    return min_value;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  Treap treap(nullptr);
  std::string query;
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> query;
    if (query == "+") {
      int i = 0;
      int x = 0;
      std::cin >> i >> x;
      treap.Permutation(i, x);
    }
    if (query == "?") {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      std::cout << treap.MinValue(left - 1, right - 1) << '\n';
    }
  }
}