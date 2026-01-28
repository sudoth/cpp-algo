#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct Bounds {
  int left;
  int right;
  int index;

  Bounds(const int& new_left, const int& new_right, const int& new_index)
      : left(new_left), right(new_right), index(new_index) {
  }
};

struct Node {
  std::unordered_map<char, int> next;
  std::vector<Bounds> bounds;
  int link;
  int exit_link;
  int pattern_index;
  int pattern_length;
  bool is_terminal = false;

  Node() = default;
};

struct SuffixQueue {
  char symbol;
  int root;
  int index;

  SuffixQueue(const char& new_symbol, const int& new_root, const int& new_index)
      : symbol(new_symbol), root(new_root), index(new_index) {
  }

  SuffixQueue() = default;
};

class Trie {
 public:
  std::vector<Node> states;
  std::vector<char> result_index;

  explicit Trie(const int& size) {
    std::string dict_str;
    states.emplace_back();
    result_index.resize(size);

    for (int i = 0; i < size; ++i) {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      std::cin >> dict_str;
      Insert(dict_str, i, left, right);
    }

    BuildSuffixReferences();
    BuildExitLinks();
  }

  void Insert(std::string& string, const int& pattern, const int& left, const int& right) {
    int index = 0;

    for (const auto& symbol : string) {
      int next = states[index].next[symbol];

      if (next == 0) {
        states.emplace_back();
        next = static_cast<int>(states.size()) - 1;
        states[index].next[symbol] = next;
      }

      index = next;
    }

    states[index].is_terminal = true;
    states[index].pattern_index = pattern;
    states[index].pattern_length = static_cast<int>(string.size());
    states[index].bounds.emplace_back(left, right, pattern);
  }

  void BuildSuffixReferences() {
    states[0].link = -1;
    std::queue<SuffixQueue> queue;

    for (const auto& [symbol, neighbour] : states[0].next) {
      queue.emplace(symbol, 0, neighbour);
    }

    SuffixQueue suffix_queue;

    while (!queue.empty()) {
      suffix_queue = queue.front();
      queue.pop();

      int suffix_index = suffix_queue.root;
      int suffix_link = states[suffix_index].link;

      while ((suffix_link != -1) &&
             (states[suffix_link].next.find(suffix_queue.symbol) == states[suffix_link].next.end())) {
        suffix_link = states[suffix_index].link;
        suffix_index = suffix_link;
      }

      states[suffix_queue.index].link = (suffix_link == -1 ? 0 : states[suffix_link].next[suffix_queue.symbol]);

      for (const auto& [symbol, neighbour] : states[suffix_queue.index].next) {
        queue.emplace(symbol, suffix_queue.index, neighbour);
      }
    }
  }

  void BuildExitLinks() {
    states[0].exit_link = -1;
    std::queue<int> queue;

    for (const auto& [symbol, neighbour] : states[0].next) {
      queue.push(neighbour);
    }

    while (!queue.empty()) {
      int tmp = queue.front();
      queue.pop();

      int suffix_link = states[tmp].link;

      if (suffix_link != 0) {
        states[tmp].exit_link = (states[suffix_link].is_terminal ? suffix_link : states[suffix_link].exit_link);
      }

      for (const auto& [symbol, neighbour] : states[tmp].next) {
        queue.push(neighbour);
      }
    }
  }

  int NextState(const char& symbol, int index) {
    while ((index != -1) && (states[index].next.find(symbol) == states[index].next.end())) {
      index = states[index].link;
    }

    return (index == -1 ? 0 : states[index].next[symbol]);
  }

  void PrintEntries(const int& i, int index) {
    if (!states[index].is_terminal) {
      index = states[index].exit_link;
    }

    while ((index != 0) && (index != -1)) {
      int size = static_cast<int>(states[index].bounds.size());
      for (int j = 0; j < size; ++j) {
        if ((i + 1 <= states[index].bounds[j].right) &&
            ((i - states[index].pattern_length + 2) >= states[index].bounds[j].left)) {
          result_index[states[index].bounds[j].index] = true;
        }
      }
      index = states[index].exit_link;
    }
  }
};

void AhoCorasik(const std::string& string, const int& patterns_size) {
  Trie trie(patterns_size);
  int node = 0;
  int size = static_cast<int>(string.size());

  for (int i = 0; i < size; ++i) {
    node = trie.NextState(string[i], node);
    trie.PrintEntries(i, node);
  }

  int total_patterns = static_cast<int>(trie.result_index.size());

  for (int i = 0; i < total_patterns; ++i) {
    std::cout << (trie.result_index[i] ? '+' : '-');
  }
}

int main() {
  std::string string;
  int size = 0;
  std::cin >> string;
  std::cin >> size;
  AhoCorasik(string, size);
}
