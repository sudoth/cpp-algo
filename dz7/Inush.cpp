#include <iostream>
#include <vector>

struct Node {
  int key;
  int priority;
  int size;
  Node* left;
  Node* right;
  Node* parent;

  Node(const int& x, const int& y) : key(x), priority(y), size(1), left(nullptr), right(nullptr), parent(nullptr) {
  }
};

class Treap {
  Node* treap_;

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

  void Build(std::vector<std::pair<int, int>> arr, const int& n) {
    Node* last = nullptr;
    for (int i = 0; i < n; ++i) {
      int x = arr[i].first;
      int y = arr[i].second;
      Node* cur = last;
      while ((cur != nullptr) && (cur->priority >= y)) {
        cur = cur->parent;
      }
      Node* new_node(new Node(x, y));
      if (cur == nullptr) {
        new_node->left = treap_;
        if (treap_) {
          treap_->parent = new_node;
        }
        treap_ = new_node;
      } else {
        new_node->left = cur->right;
        if (cur->right) {
          cur->right->parent = new_node;
        }
        cur->right = new_node;
        new_node->parent = cur;
      }
      last = new_node;
    }
  }

  void Inorder(Node* t) {
    if (t != nullptr) {
      Inorder(t->left);
      std::cout << (t->parent ? t->parent->key : 0) << ' ';
      std::cout << (t->left ? t->left->key : 0) << ' ';
      std::cout << (t->right ? t->right->key : 0) << '\n';
      Inorder(t->right);
    }
  }

  void Inorder() {
    Inorder(treap_);
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

  int j = 0;
  std::vector<std::pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) {
    arr[i].first = i + 1;
    std::cin >> j >> arr[i].second;
  }

  treap.Build(arr, n);
  std::cout << "YES\n";
  treap.Inorder();
}