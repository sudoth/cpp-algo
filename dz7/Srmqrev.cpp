#include <iostream>
#include <random>

struct Node {
  int key;
  int priority;
  int quantity;
  int minimum;
  int promise;
  Node* left;
  Node* right;

  explicit Node(const int& n) : key(n), priority(rand()), quantity(1), minimum(n), left(nullptr), right(nullptr) {
  }
};

class Treap {
  Node* treap_;

  int Count(Node* root) {
    return root ? root->quantity : 0;
  }

  int Min(Node* root) {
    return root ? root->minimum : INT32_MAX;
  }

  void UpdateCount(Node* root) {
    if (root) {
      root->quantity = 1 + Count(root->left) + Count(root->right);
      root->minimum = std::min(root->key, std::min(Min(root->left), Min(root->right)));
    }
  }

 public:
  explicit Treap(Node* node) : treap_(node) {
  }

  ~Treap() {
    Delete(treap_);
  }

  void Delete(Node* node) {
    if (!node) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
    node = nullptr;
  }

  Node* Root() {
    return treap_;
  }

  int Size(Node* node) {
    return node ? node->quantity : 0;
  }

  void Push(Node* node) {
    if (node && node->promise) {
      std::swap(node->left, node->right);
      if (node->left) {
        node->left->promise ^= 1;
      }
      if (node->right) {
        node->right->promise ^= 1;
      }
      node->promise = 0;
    }
  }

  std::pair<Node*, Node*> Split(Node* root, const int& key) {
    if (!root) {
      return {nullptr, nullptr};
    }
    Push(root);
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

  Node* Merge(Node* left, Node* right) {
    if (!left || !right) {
      return left ? left : right;
    }
    if (left->priority < right->priority) {
      Push(left);
      left->right = Merge(left->right, right);
      UpdateCount(left);
      return left;
    }
    Push(right);
    right->left = Merge(left, right->left);
    UpdateCount(right);
    return right;
  }

  void Reverse(const int& left, const int& right) {
    auto splited1 = Split(treap_, left);
    auto splited2 = Split(splited1.second, right - left + 1);
    splited2.first->promise ^= 1;
    treap_ = Merge(splited1.first, Merge(splited2.first, splited2.second));
  }

  void Permutation(const int& i, const int& x) {
    auto splitted = Split(treap_, i);
    treap_ = Merge(Merge(splitted.first, new Node(x)), splitted.second);
  }

  int MinValue(const int& left, const int& right) {
    auto splitted1 = Split(treap_, left);
    auto splitted2 = Split(splitted1.second, right - left + 1);
    int min_value = Min(splitted2.first);
    treap_ = Merge(Merge(splitted1.first, splitted2.first), splitted2.second);
    return min_value;
  }

  void Push(const int& i) {
    Node* new_node = new Node(i);
    treap_ = Merge(treap_, new_node);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  Treap treap(nullptr);
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  int query = 0;
  for (int i = 0; i < n; ++i) {
    int value = 0;
    std::cin >> value;
    treap.Push(value);
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> query;
    if (query == 1) {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      treap.Reverse(left - 1, right - 1);
    }
    if (query == 2) {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      std::cout << treap.MinValue(left - 1, right - 1) << '\n';
    }
  }
  return 0;
}