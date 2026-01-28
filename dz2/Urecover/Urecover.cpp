#include <iostream>

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
  bool was = false;
  bool outputed = false;
};

struct BinarySearchTree {
  Node* root = nullptr;
  int64_t n = 0;
};

void Push(BinarySearchTree* bintree, int64_t& value) {
  if (bintree->n == 0) {
    auto node = new Node;
    node->value = value;
    bintree->root = node;
    bintree->n++;
    return;
  }
  Node* curent = bintree->root;
  while (true) {
    if (curent->value == value) {
      break;
    }
    if (value < curent->value) {
      if (curent->left == nullptr) {
        break;
      }
      curent = curent->left;
    }
    if (value > curent->value) {
      if (curent->right == nullptr) {
        break;
      }
      curent = curent->right;
    }
  }
  if (curent->value == value) {
    return;
  }
  auto node = new Node;
  if (curent->value > value) {
    node->value = value;
    node->parent = curent;
    curent->left = node;
    bintree->n++;
  }
  if (curent->value < value) {
    node->value = value;
    node->parent = curent;
    curent->right = node;
    bintree->n++;
  }
}

void Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->left);
  Clear(node->right);
  delete node;
}

Node* NextLeaf(Node* curent) {
  while (true) {
    if (curent->parent != nullptr) {
      curent->was = true;
      curent = curent->parent;
      if (curent->left != nullptr && curent->right != nullptr && !curent->outputed) {
        std::cout << curent->value << '\n';
        curent->outputed = true;
      }
      if (curent->right != nullptr && !curent->right->was) {
        curent = curent->right;
        break;
      }
    }
  }
  while (true) {
    if (curent->left != nullptr) {
      curent = curent->left;
      continue;
    }
    if (curent->right != nullptr) {
      curent = curent->right;
      continue;
    }

    return curent;
  }
}

void InOrder(BinarySearchTree* bintree) {
  Node* curent = bintree->root;
  Node* tmp = nullptr;
  if (curent == nullptr) {
    return;
  }
  while (curent != nullptr) {
    if (curent->left == nullptr) {
      std::cout << curent->value << ' ';
      curent = curent->right;
    } else {
      tmp = curent->left;
      while (tmp->right != nullptr && tmp->right != curent) {
        tmp = tmp->right;
      }
      if (tmp->right == nullptr) {
        tmp->right = curent;
        curent = curent->left;
      } else {
        tmp->right = nullptr;
        std::cout << curent->value << ' ';
        curent = curent->right;
      }
    }
  }
}

int MakeBinarySearchTree(Node* current, int left, int right, int* pre_order, int n, int i) {
  if (i == n || pre_order[i] < left || pre_order[i] > right) {
    return i;
  }
  if (pre_order[i] < current->value) {
    auto node = new Node;
    node->value = pre_order[i];
    current->left = node;
    i += 1;
    i = MakeBinarySearchTree(current->left, left, current->value - 1, pre_order, n, i);
  }
  if (i == n || pre_order[i] < left || pre_order[i] > right) {
    return i;
  }
  auto node = new Node;
  node->value = pre_order[i];
  current->right = node;
  i += 1;
  i = MakeBinarySearchTree(current->right, current->value + 1, right, pre_order, n, i);
  return i;
}

void PostOrder(Node* node) {
  if (node != nullptr) {
    PostOrder(node->left);
    PostOrder(node->right);
    std::cout << node->value << ' ';
  }
}

int main() {
  int n;
  std::cin >> n;
  BinarySearchTree bst;
  auto pre_order = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> pre_order[i];
  }
  if (n == 1) {
    std::cout << pre_order[0];
  }
  auto node = new Node;
  node->value = pre_order[0];
  bst.root = node;
  MakeBinarySearchTree(bst.root, -1e9, 1e9, pre_order, n, 1);
  PostOrder(bst.root);
  Clear(bst.root);
  bst.root = nullptr;
  delete[] pre_order;
}