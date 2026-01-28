#include <iostream>
#include <cstring>

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int value;
  int height = 0;
};

class AVL {
 public:
  Node* root = nullptr;
  int n = 0;

  Node* FindMin(Node* node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = FindMin(node->left);
    return FixBalance(node);
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  Node* Add(Node* node, int value) {
    if (node == nullptr) {
      auto new_node = new Node;
      new_node->value = value;
      return new_node;
    }
    if (value <= node->value) {
      node->left = Add(node->left, value);
    }
    if (value > node->value) {
      node->right = Add(node->right, value);
    }
    return FixBalance(node);
  }

  int GetHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
  }

  int BFactor(Node* node) {
    return node == nullptr ? 0 : GetHeight(node->right) - GetHeight(node->left);
  }

  void SetHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  Node* RightRotate(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    SetHeight(p);
    SetHeight(q);
    return q;
  }

  Node* LeftRotate(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    SetHeight(q);
    SetHeight(p);
    return p;
  }

  Node* FixBalance(Node* node) {
    SetHeight(node);
    if (BFactor(node) == 2) {
      if (BFactor(node->right) == -1) {
        node->right = RightRotate(node->right);
      }
      return LeftRotate(node);
    }
    if (BFactor(node) == -2) {
      if (BFactor(node->left) == 1) {
        node->left = LeftRotate(node->left);
      }
      return RightRotate(node);
    }
    return node;
  }

  Node* DeleteMax(Node* node) {
    if (node->right == nullptr) {
      Node* temp = node->left;
      std::cout << node->value << '\n';
      delete node;
      return FixBalance(temp);
    }
    node->right = DeleteMax(node->right);
    return FixBalance(node);
  }

  Node* DeleteMin(Node* node) {
    if (node->left == nullptr) {
      if (node->right == nullptr) {
        Node* temp = node->left;
        std::cout << node->value << '\n';
        delete node;
        return FixBalance(temp);
      }
      Node* right_min = node->right;
      while (right_min->left != nullptr) {
        right_min = right_min->left;
      }
      node->right = FindMin(node->right);
      right_min->left = node->left;
      right_min->right = node->right;
      std::cout << node->value << '\n';
      delete node;
      return FixBalance(right_min);
    }
    node->left = DeleteMin(node->left);
    return FixBalance(node);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVL avl;
  int_fast32_t m;
  int_fast32_t value;
  std::cin >> m;
  char request[69];
  for (int_fast32_t i = 0; i < m; ++i) {
    std::cin >> request;
    if (strcmp(request, "insert") == 0) {
      std::cin >> value;
      avl.n++;
      avl.root = avl.Add(avl.root, value);
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(request, "extract_min") == 0) {
      if (avl.n == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      avl.n--;
      avl.root = avl.DeleteMin(avl.root);
      continue;
    }
    if (strcmp(request, "get_min") == 0) {
      if (avl.n == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      Node* current = avl.root;
      while (current->left != nullptr) {
        current = current->left;
      }
      std::cout << current->value << '\n';
      continue;
    }
    if (strcmp(request, "extract_max") == 0) {
      if (avl.n == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      avl.n--;
      avl.root = avl.DeleteMax(avl.root);
      continue;
    }
    if (strcmp(request, "get_max") == 0) {
      if (avl.n == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      Node* current = avl.root;
      while (current->right != nullptr) {
        current = current->right;
      }
      std::cout << current->value << '\n';
      continue;
    }
    if (strcmp(request, "size") == 0) {
      std::cout << avl.n << '\n';
      continue;
    }
    if (strcmp(request, "clear") == 0) {
      avl.n = 0;
      if (avl.root != nullptr) {
        avl.Clear(avl.root);
      }
      avl.root = nullptr;
      std::cout << "ok" << '\n';
      continue;
    }
  }
  avl.Clear(avl.root);
}