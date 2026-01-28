#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Trie {
 public:
  Trie() {
    Node root;
    trie_.emplace_back(root);
  };

  bool Search(const std::string& string) {
    int64_t state = 0;
    auto size = static_cast<int64_t>(string.size());
    for (int64_t i = 0; i < size; ++i) {
      if (trie_[state].dict.count(string[i]) == 0) {
        return false;
      }
      state = trie_[state].dict[string[i]];
    }
    return trie_[state].is_terminal;
  }

  void Insert(const std::string& string) {
    int64_t state = 0;
    auto size = static_cast<int64_t>(string.size());
    for (int64_t i = 0; i < size; ++i) {
      if (!trie_[state].dict.count(string[i])) {
        trie_.emplace_back();
        trie_[state].dict[string[i]] = static_cast<int64_t>(trie_.size()) - 1;
      }
      state = trie_[state].dict[string[i]];
    }
    trie_[state].is_terminal = true;
  }

 private:
  struct Node {
    std::unordered_map<char, int64_t> dict;
    bool is_terminal = false;
    Node() = default;
  };
  std::vector<Node> trie_;
};
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str_request;
  char symbol_request = 0;
  std::cin >> symbol_request;
  Trie trie;
  while (symbol_request != '#') {
    std::cin >> str_request;
    if (symbol_request == '+') {
      trie.Insert(str_request);
    }
    if (symbol_request == '?') {
      if (trie.Search(str_request)) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
    std::cin >> symbol_request;
  }
  return 0;
}