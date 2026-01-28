#include <iostream>
#include <algorithm>
#include <cstdint>

int main() {
  int n;
  int k;
  std::cin >> n;
  std::cin >> k;
  auto all_cards = new int[100007];
  for (int i = 0; i < n; i++) {
    std::cin >> all_cards[i];
  }
  std::sort(all_cards, all_cards + n);
  auto cards = new int64_t[100007];
  auto number = new int[100007];
  auto ones = new int64_t[100007];
  int m = 0;
  int l = 0;
  int counter = 1;
  for (int i = 0; i < n; i++) {
    if (all_cards[i + 1] == all_cards[i] && i + 1 < n) {
      counter++;
    } else {
      if (counter > 1) {
        ones[l] = all_cards[i];
        l++;
      }
      number[m] = counter;
      cards[m] = all_cards[i];
      counter = 1;
      m++;
    }
  }
  int64_t first_ans = 0;
  for (int i = 0; i < m; i++) {
    if (number[i] > 2) {
      first_ans++;
    }
  }
  int64_t second_ans = 0;
  int64_t third_ans = 0;
  int64_t it1 = 0;
  for (int64_t it2 = 1; it2 < m; it2++) {
    while (cards[it1] * k < cards[it2]) {
      it1++;
    }
    second_ans += std::lower_bound(ones, ones + l, cards[it2]) - std::lower_bound(ones, ones + l, cards[it1]);
    if (number[it2] > 1) {
      second_ans += it2 - it1;
    }

    if (it2 - it1 > 1) {
      third_ans += (it2 - it1) * (it2 - it1 - 1) / 2;
    }
  }
  int64_t ans = first_ans + 3 * second_ans + 6 * third_ans;
  std::cout << ans;
  delete[] ones;
  delete[] number;
  delete[] cards;
  delete[] all_cards;
}