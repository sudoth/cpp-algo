#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct State {
  std::unordered_map<char, int> transitions;
  int link = -1;
  int length = 0;
  int end_position = -1;
};

class SuffixAutomation {
  int prev_ = 0;

 public:
  std::vector<State> states;

  explicit SuffixAutomation(const std::string& string) {
    states.emplace_back();
    for (char symbol : string) {
      AddSymbol(symbol);
    }
  }

  void AddSymbol(const char& symbol) {
    int current = static_cast<int>(states.size());
    states.emplace_back();
    states[current].length = states[prev_].length + 1;
    states[current].end_position = states[prev_].end_position + 1;

    int p = prev_;
    while (p != -1 && states[p].transitions.find(symbol) == states[p].transitions.end()) {
      states[p].transitions[symbol] = current;
      p = states[p].link;
    }

    if (p == -1) {
      states[current].link = 0;
    } else {
      int q = states[p].transitions[symbol];
      if (states[p].length + 1 == states[q].length) {
        states[current].link = q;
      } else {
        int clone = static_cast<int>(states.size());
        states.emplace_back(states[q]);
        states[clone].length = states[p].length + 1;
        states[clone].end_position = states[q].end_position;
        while (p != -1 && states[p].transitions[symbol] == q) {
          states[p].transitions[symbol] = clone;
          p = states[p].link;
        }
        states[q].link = clone;
        states[current].link = clone;
      }
    }

    prev_ = current;
  }
};

struct Node {
  std::unordered_map<char, int> transitions;
  int begin = -1;
  int length = 0;
};

class SuffixTree {
 public:
  std::vector<Node> states_tree;
  int size;
  std::string string;

  void ExtractTransitions(SuffixAutomation& automation, int index) {
    int suffix_index = automation.states[index].link;
    states_tree[index].begin = static_cast<int>(string.size()) - 1 -
                               (automation.states[index].end_position - automation.states[suffix_index].length);
    states_tree[index].length = automation.states[index].length - automation.states[suffix_index].length;
    states_tree[suffix_index].transitions[string[states_tree[index].begin]] = index;
  }

  explicit SuffixTree(const std::string& new_string) : string(new_string) {
    std::string reversed_string = new_string;
    std::reverse(reversed_string.begin(), reversed_string.end());
    SuffixAutomation automation(reversed_string);
    int size = static_cast<int>(automation.states.size());
    states_tree.resize(size + 1);
    for (int i = 1; i < size; ++i) {
      ExtractTransitions(automation, i);
    }
  }
};

int main() {
  std::string string;
  std::cin >> string;
  string += '#';

  SuffixTree suffix_tree(string);
  int size = static_cast<int>(suffix_tree.states_tree.size());
  std::cout << size - 1 << '\n';
  for (int i = 0; i < size; ++i) {
    for (const auto& [symbol, vertex] : suffix_tree.states_tree[i].transitions) {
      std::cout << i << ' ' << symbol << ' ' << suffix_tree.states_tree[vertex].length << ' ' << vertex << '\n';
    }
  }
}
