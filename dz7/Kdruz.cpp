#include <iostream>
#include <random>

struct Node {
  int64_t key;
  int64_t priority;
  int64_t sum;
  Node* left;
  Node* right;

  explicit Node(const int64_t& n) : key(n), priority(rand()), sum(key), left(nullptr), right(nullptr) {
  }
};

class Treap {
  Node* treap_;

  int64_t Count(Node* root) {
    return root ? root->sum : 0;
  }

  void UpdateCount(Node* root) {
    if (root) {
      root->sum = root->key + Count(root->left) + Count(root->right);
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

  std::pair<Node*, Node*> Split(Node* root, const int64_t& key) {
    if (!root) {
      return {nullptr, nullptr};
    }
    if (key > root->key) {
      auto [t1, t2] = Split(root->right, key);
      root->right = t1;
      UpdateCount(root);
      return {root, t2};
    }
    auto [t1, t2] = Split(root->left, key);
    root->left = t2;
    UpdateCount(root);
    return {t1, root};
  }

  Node* Merge(Node* left, Node* right) {
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

  void Insert(const int64_t& key) {
    auto splitted = Split(treap_, key);
    treap_ = Merge(Merge(splitted.first, new Node(key)), splitted.second);
  }

  int64_t GetSum(Node* root) {
    return root ? root->sum : 0;
  }

  int64_t FindSum(const int64_t& left, const int64_t& right) {
    auto splitted1 = Split(treap_, left);
    auto splitted2 = Split(splitted1.second, right + 1);
    auto sub_sum = GetSum(splitted2.first);
    treap_ = Merge(splitted1.first, Merge(splitted2.first, splitted2.second));
    return sub_sum;
  }

  bool Exists(Node* root, const int64_t& key) {
    if (!root) {
      return false;
    }
    if (root->key == key) {
      return true;
    }
    if (root->key < key) {
      return Exists(root->right, key);
    }
    return Exists(root->left, key);
  }

  bool Exists(const int64_t& key) {
    return Exists(treap_, key);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  Treap treap(nullptr);
  std::string query;
  int64_t m = 0;
  std::cin >> m;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> query;
    if (query == "+") {
      int64_t key = 0;
      std::cin >> key;
      if (!treap.Exists(key)) {
        treap.Insert(key);
      }
    } else if (query == "?") {
      int64_t left = 0;
      int64_t right = 0;
      std::cin >> left >> right;
      std::cout << treap.FindSum(left, right) << '\n';
    }
  }
}