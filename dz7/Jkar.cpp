#include <iostream>
#include <random>

struct Node {
  int key;
  int priority;
  int quantity;
  Node* left;
  Node* right;

  explicit Node(const int& n) : key(n), priority(rand()), quantity(1), left(nullptr), right(nullptr) {
  }
};

class Treap {
  Node* treap_;

  int Count(Node* root) {
    return root ? root->quantity : 0;
  }

  void UpdateCount(Node* root) {
    if (root) {
      root->quantity = 1 + Count(root->left) + Count(root->right);
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

  std::pair<Node*, Node*> Split(Node* root, const int& key) {
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

  void Insert(const int& key) {
    auto splitted = Split(treap_, key);
    treap_ = Merge(Merge(splitted.first, new Node(key)), splitted.second);
  }

  void Delete(const int& key) {
    auto splitted1 = Split(treap_, key);
    auto splitted2 = Split(splitted1.second, key + 1);
    delete splitted2.first;
    treap_ = Merge(splitted1.first, splitted2.second);
  }

  bool Exists(Node* root, const int& key) {
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

  bool Exists(const int& key) {
    return Exists(treap_, key);
  }

  int Next(Node* root, const int& key) {
    int result = INT32_MAX;
    while (root) {
      if (root->key > key) {
        result = root->key;
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return result;
  }

  int Next(const int& key) {
    return Next(treap_, key);
  }

  int Prev(Node* root, const int& key) {
    int result = INT32_MIN;
    while (root) {
      if (root->key < key) {
        result = root->key;
        root = root->right;
      } else {
        root = root->left;
      }
    }
    return result;
  }

  int Prev(const int& key) {
    return Prev(treap_, key);
  }

  int Kth(Node* root, int k) {
    if (Count(root) <= k) {
      return INT32_MIN;
    }
    while (root) {
      int left_count = Count(root->left);
      if (left_count == k) {
        return root->key;
      }
      if (left_count < k) {
        k -= left_count + 1;
        root = root->right;
      } else {
        root = root->left;
      }
    }
    return 0;
  }

  int Kth(const int& key) {
    return Kth(treap_, key);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  std::string query;
  Treap treap(nullptr);
  while (std::cin >> query) {
    int key = 0;
    std::cin >> key;
    if (query == "insert" && !treap.Exists(key)) {
      treap.Insert(key);
    } else if (query == "delete" && treap.Exists(key)) {
      treap.Delete(key);
    } else if (query == "exists") {
      std::cout << (treap.Exists(key) ? "true" : "false") << '\n';
    } else if (query == "next") {
      int result = treap.Next(key);
      if (result == INT32_MAX) {
        std::cout << "none" << '\n';
      } else {
        std::cout << result << '\n';
      }
    } else if (query == "prev") {
      int result = treap.Prev(key);
      if (result == INT32_MIN) {
        std::cout << "none" << '\n';
      } else {
        std::cout << result << '\n';
      }
    } else if (query == "kth") {
      int result = treap.Kth(key);
      if (result == INT32_MIN) {
        std::cout << "none" << '\n';
      } else {
        std::cout << result << '\n';
      }
    }
  }
}