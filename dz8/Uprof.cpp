#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Trie {
 public:
  int current_max_index = 0;
  std::vector<char> res_operations;
  std::string max_str;

  Trie() {
    Node root;
    trie_.emplace_back(root);
  }

  void Print(int ind = 0, bool max_str_found = true) {
    Node &current_node = trie_[ind];
    if (current_node.is_terminal) {
      res_operations.emplace_back('P');
      if (current_node.dict.empty()) {
        return;
      }
    }
    for (auto &[char_val, next_state] : current_node.dict) {
      if (!max_str_found || (char_val != max_str[current_max_index])) {
        res_operations.emplace_back(char_val);
        Print(next_state, false);
        res_operations.emplace_back('-');
      }
    }
    if (max_str_found) {
      res_operations.emplace_back(max_str[current_max_index]);
      current_max_index++;
      Print(current_node.dict[max_str[current_max_index - 1]], true);
    }
  }

  void Insert(const std::string &string) {
    int state = 0;
    int size = static_cast<int>(string.size());
    for (int i = 0; i < size; ++i) {
      InsertNode(state, string[i]);
    }
    trie_[state].is_terminal = true;
  }

  void InsertNode(int &state, char char_val) {
    if (!trie_[state].dict.count(char_val)) {
      trie_.emplace_back();
      trie_[state].dict[char_val] = static_cast<int>(trie_.size()) - 1;
    }
    state = trie_[state].dict[char_val];
  }

 private:
  struct Node {
    std::map<char, int> dict;
    bool is_terminal = false;
    Node() = default;
    int order = 0;
  };
  std::vector<Node> trie_;
};

int main() {
  int n = 0;
  std::cin >> n;
  std::string surname;
  int max_length = 0;
  Trie trie;
  for (int i = 0; i < n; ++i) {
    std::cin >> surname;
    if (static_cast<int>(surname.size()) > max_length) {
      max_length = static_cast<int>(surname.size());
      trie.max_str = surname;
    }
    trie.Insert(surname);
  }
  trie.Print();
  int size = static_cast<int>(trie.res_operations.size());
  std::cout << size << '\n';
  for (int i = 0; i < size; ++i) {
    std::cout << trie.res_operations[i] << '\n';
  }
  return 0;
}