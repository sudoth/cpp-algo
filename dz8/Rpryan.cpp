#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

class Trie {
  struct Node {
    std::map<char, int64_t> dict;
    bool is_terminal = false;
    int64_t depth = 0;
    int64_t sum_cakes = 0;
    std::string city;
  };

  int64_t max_digit_ = 0;
  std::vector<Node> trie_;

 public:
  explicit Trie(int64_t max_digit_new) : max_digit_(max_digit_new) {
    Node root;
    trie_.emplace_back(root);
  }

  void Insert(const std::string &string, const std::string &city_name) {
    int64_t state = 0;
    auto size = static_cast<int64_t>(string.size());

    for (int64_t i = 0; i < size; ++i) {
      InsertNode(state, string[i], i);
    }

    trie_[state].depth = size;
    trie_[state].city = city_name;
    trie_[state].is_terminal = true;
  }

  int64_t CountCakes(int64_t ind = 0) {
    Node &current_node = trie_[ind];

    if ((current_node.depth > max_digit_) && (current_node.is_terminal)) {
      current_node.sum_cakes = 0;
      PrintCityAndCakes(current_node);
      for (auto &[char_val, next_state] : current_node.dict) {
        CountCakes(next_state);
      }
      return 0;
    }

    if (current_node.is_terminal) {
      current_node.sum_cakes = static_cast<int64_t>(std::pow(10, max_digit_ - current_node.depth));
      for (auto &[char_val, next_state] : current_node.dict) {
        if (trie_[next_state].depth <= max_digit_) {
          if (trie_[next_state].is_terminal) {
            CountCakes(next_state);
            current_node.sum_cakes -= static_cast<int64_t>(std::pow(10, max_digit_ - current_node.depth - 1));
          } else {
            current_node.sum_cakes -= CountCakes(next_state);
          }
        } else {
          CountCakes(next_state);
        }
      }
      PrintCityAndCakes(current_node);
      return current_node.sum_cakes;
    }

    for (auto &[char_val, next_state] : current_node.dict) {
      if (trie_[next_state].depth <= max_digit_) {
        if (trie_[next_state].is_terminal) {
          CountCakes(next_state);
          current_node.sum_cakes += static_cast<int64_t>(std::pow(10, max_digit_ - current_node.depth - 1));
        } else {
          current_node.sum_cakes += CountCakes(next_state);
        }
      } else {
        CountCakes(next_state);
      }
    }
    return current_node.sum_cakes;
  }

 private:
  void InsertNode(int64_t &state, char char_val, int64_t depth) {
    if (!trie_[state].dict.count(char_val)) {
      trie_.emplace_back();
      trie_[state].dict[char_val] = static_cast<int64_t>(trie_.size()) - 1;
      trie_[state].depth = depth;
    }
    state = trie_[state].dict[char_val];
  }

  void PrintCityAndCakes(const Node &current_node) {
    std::cout << current_node.city << ' ' << current_node.sum_cakes << '\n';
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t size = 0;
  std::cin >> size;

  int64_t max_digit = 0;
  std::cin >> max_digit;

  Trie trie(max_digit);

  std::string city_name;
  std::string city_index;

  for (int64_t i = 0; i < size; ++i) {
    std::cin >> city_index >> city_name;
    trie.Insert(city_index, city_name);
  }

  trie.CountCakes();

  return 0;
}