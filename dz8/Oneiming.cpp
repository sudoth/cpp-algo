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

  SuffixAutomaton() {
    states.emplace_back();
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
        states[q].link = clone;
        states[current].link = clone;
      }
    }

    prev_ = current;
  }

  bool Check(const int& length) {
    int max_length = states[prev_].link;
    return states[max_length].length < length;
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  SuffixAutomaton automation;

  for (int i = 0; i < n; ++i) {
    char type = 0;
    std::cin >> type;

    if (type == '+') {
      char c = 0;
      std::cin >> c;
      automation.AddSymbol(c);
    }

    if (type == '?') {
      int position = 0;
      std::cin >> position;
      std::cout << (automation.Check(position) ? "+\n" : "-\n");
    }
  }
}
