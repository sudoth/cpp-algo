#include <iostream>

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int64_t value;
  int64_t height;
};

struct BinSearchTree {
  int64_t n = 0;
  int64_t height = 0;
  Node* root = nullptr;
};

void Push(BinSearchTree* bintree, int64_t& value) {
  if (bintree->n == 0) {
    auto node = new Node;
    node->value = value;
    node->height = 1;
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
    node->height = curent->height + 1;
    node->value = value;
    node->parent = curent;
    curent->left = node;
    bintree->n++;
  }
  if (curent->value < value) {
    node->height = curent->height + 1;
    node->value = value;
    node->parent = curent;
    curent->right = node;
    bintree->n++;
  }
  if (node->height > bintree->height) {
    bintree->height = node->height;
  }
}

void Clear(BinSearchTree* bintree) {
  Node* removable = bintree->root;
  Node* to_delete = nullptr;
  while (bintree->n > 0) {
    if (removable->left != nullptr) {
      removable = removable->left;
      continue;
    }
    if (removable->right != nullptr) {
      removable = removable->right;
      continue;
    }
    if (bintree->n == 1) {
      delete bintree->root;
      return;
    }
    if (removable->parent->left == removable) {
      removable = removable->parent;
      to_delete = removable->left;
      removable->left = nullptr;
      delete to_delete;
      bintree->n--;
    } else {
      removable = removable->parent;
      to_delete = removable->right;
      removable->right = nullptr;
      delete to_delete;
      bintree->n--;
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  BinSearchTree bintree;
  int64_t value;
  while (std::cin >> value) {
    if (value == 0) {
      break;
    }
    Push(&bintree, value);
  }
  std::cout << bintree.height;
  Clear(&bintree);
}