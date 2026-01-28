#include <iostream>
#include <unordered_map>
#include <vector>

struct State {
  std::unordered_map<char, int> transitions;
  int link = -1;
  int length = 0;
};

class SuffixAutomaton {
  int prev_ = 0;

 public:
  std::vector<State> states;

  explicit SuffixAutomaton(const std::string& string) {
    states.emplace_back();
    for (char symbol : string) {
      AddSymbol(symbol);
    }
  }

  void AddSymbol(const char& symbol) {
    int current = static_cast<int>(states.size());
    states.emplace_back();
    states[current].length = states[prev_].length + 1;

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
        while (p != -1 && states[p].transitions[symbol] == q) {
          states[p].transitions[symbol] = clone;
          p = states[p].link;
        }
        states[q].link = states[current].link = clone;
      }
    }

    prev_ = current;
  }

  void PrintAutomaton() {
    std::cout << states.size() << '\n';
    int size = static_cast<int>(states.size());

    for (int i = 0; i < size; ++i) {
      for (const auto& transition : states[i].transitions) {
        std::cout << i << ' ' << transition.first << ' ' << transition.second << '\n';
      }
    }
  }
};

int main() {
  std::string string;
  std::cin >> string;

  SuffixAutomaton automaton(string);
  automaton.PrintAutomaton();
}