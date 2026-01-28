#include <iostream>

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int value;
  int64_t height = 0;
};

class AVL {
 public:
  AVL() : root_(nullptr) {
  }

  void Add(int value) {
    root_ = Add(root_, value);
  }

  void Clear() {
    if (root_ != nullptr) {
      Clear(root_);
    }
    root_ = nullptr;
  }

  int Next(int value) {
    return Next(root_, value);
  }

 private:
  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  int BalanceFactor(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return (node->right == nullptr ? 0 : node->right->height) - (node->left == nullptr ? 0 : node->left->height);
  }

  Node* RightRotate(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    if (p != nullptr) {
      p->height =
          std::max((p->left == nullptr ? 0 : p->left->height), (p->right == nullptr ? 0 : p->right->height)) + 1;
    }
    if (q != nullptr) {
      q->height =
          std::max((q->left == nullptr ? 0 : q->left->height), (q->right == nullptr ? 0 : q->right->height)) + 1;
    }
    return q;
  }

  Node* LeftRotate(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    if (p != nullptr) {
      p->height =
          std::max((p->left == nullptr ? 0 : p->left->height), (p->right == nullptr ? 0 : p->right->height)) + 1;
    }
    if (q == nullptr) {
      q->height =
          std::max((q->left == nullptr ? 0 : q->left->height), (q->right == nullptr ? 0 : q->right->height)) + 1;
    }
    return p;
  }

  Node* Balancing(Node* node) {
    if (node != nullptr) {
      node->height = std::max((node->left == nullptr ? 0 : node->left->height),
                              (node->right == nullptr ? 0 : node->right->height)) +
                     1;
    }
    if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->left) == 1) {
        node->left = LeftRotate(node->left);
      }
      return RightRotate(node);
    }
    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->right) == -1) {
        node->right = RightRotate(node->right);
      }
      return LeftRotate(node);
    }
    return node;
  }

  int Next(Node* root, int value) {
    Node* current = root;
    int minimum = 2147483647;
    if (root == nullptr) {
      return -1;
    }
    while (true) {
      if (current->value == value) {
        return value;
      }
      if (current->value >= value) {
        minimum = std::min(minimum, current->value);
      }
      if (value < current->value) {
        if (current->left == nullptr) {
          break;
        }
        current = current->left;
      }
      if (value > current->value) {
        if (current->right == nullptr) {
          break;
        }
        current = current->right;
      }
    }
    return minimum == 2147483647 ? -1 : minimum;
  }

  Node* Add(Node* node, int value) {
    if (node == nullptr) {
      auto new_node = new Node;
      new_node->value = value;
      return new_node;
    }
    if (value == node->value) {
      return node;
    }
    if (value < node->value) {
      node->left = Add(node->left, value);
    }
    if (value > node->value) {
      node->right = Add(node->right, value);
    }
    return Balancing(node);
  }

  Node* root_ = nullptr;
};

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVL avl;
  int n;
  std::cin >> n;
  char prev_request = '+';
  int y = 0;
  for (int i = 0; i < n; i++) {
    char request;
    std::cin >> request;
    int value;
    std::cin >> value;
    if (request == '?') {
      std::cout << avl.Next(value) << '\n';
      y = avl.Next(value);
    }
    if (request == '+' && prev_request == '+') {
      avl.Add(value);
    }
    if (request == '+' && prev_request == '?') {
      avl.Add((value + y) % 1000000000);
    }
    prev_request = request;
  }
  avl.Clear();
  return 0;
}