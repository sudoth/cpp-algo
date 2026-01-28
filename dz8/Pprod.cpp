#include <iostream>
#include <unordered_map>
#include <vector>

struct State {
  std::unordered_map<char, int64_t> transitions;
  int64_t link = -1;
  int64_t length = 0;
  int64_t prefix_number = 0;
};

class SuffixAutomaton {
  int64_t prev_ = 0;

 public:
  std::vector<State> states;

  explicit SuffixAutomaton(const std::string& string) {
    states.emplace_back();
    for (char symbol : string) {
      AddSymbol(symbol);
    }
  }

  void AddSymbol(const char& symbol) {
    auto current = static_cast<int64_t>(states.size());
    states.emplace_back();
    states[current].length = states[prev_].length + 1;

    int64_t p = prev_;
    while (p != -1 && states[p].transitions.find(symbol) == states[p].transitions.end()) {
      states[p].transitions[symbol] = current;
      p = states[p].link;
    }

    if (p == -1) {
      states[current].link = 0;
    } else {
      int64_t q = states[p].transitions[symbol];
      if (states[p].length + 1 == states[q].length) {
        states[current].link = q;
      } else {
        auto clone = static_cast<int64_t>(states.size());
        states.emplace_back(states[q]);
        states[clone].length = states[p].length + 1;
        while (p != -1 && states[p].transitions[symbol] == q) {
          states[p].transitions[symbol] = clone;
          p = states[p].link;
        }
        states[q].link = clone;
        states[current].link = clone;
      }
    }

    states[current].prefix_number =
        states[current].length + states[prev_].prefix_number - states[states[current].link].length;
    std::cout << states[current].prefix_number << '\n';
    prev_ = current;
  }
};

int main() {
  std::string string;
  std::cin >> string;

  SuffixAutomaton automaton(string);
}