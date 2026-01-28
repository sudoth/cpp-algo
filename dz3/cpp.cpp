#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

double degree(std::pair<long long int, long long int> dot1,
           std::pair<long long int, long long int> dot2,
           std::pair<long long int, long long int> dot3) {
  if (dot1 == dot2  dot2 == dot3  dot1 == dot3) {
    return -2.0;
  }
  double x1 = dot2.first - dot1.first;
  double y1 = dot2.second - dot1.second;
  double x2 = dot3.first - dot2.first;
  double y2 = dot3.second - dot2.second;
  double cos = (x1 * x2 + y1 * y2) / std::sqrt(x1 * x1 + y1 * y1) / std::sqrt(x2 * x2 + y2 * y2);
  return cos;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int x_min = 1000000001;
  int y_min = 0;
  int zero = 0;
  std::cin >> n;
  std::vector<std::pair<long long int, long long int>> ans;
  std::vector<std::pair<long long int, long long int>> dots(n);
  for (int i = 0; i != n; ++i) {
    std::cin >> dots[i].first >> dots[i].second;
    if (x_min > dots[i].first) {
      y_min = dots[i].second;
      x_min = dots[i].first;
      zero = i;
    } else if (x_min == dots[i].first) {
      if (y_min > dots[i].second) {
        zero = i;
        y_min= dots[i].second;
      }
    }
  }
  ans.push_back(std::make_pair(x_min, -1000000001));
  ans.push_back(dots[zero]);
  while (true) {
    double max = -3.0;
    std::pair<long long int, long long int> dot_ans;
    std::pair<long long int, long long int> dot1 = ans[ans.size() - 2];
    std::pair<long long int, long long int> dot2 = ans[ans.size() - 1];
    for (int i = 0; i != n; ++i) {
      if (dot1 == dot2  dot2 == dots[i]  dot1 == dots[i]) {
        continue;
      }
      double cos1 = degree(dot1, dot2, dots[i]);
      if (cos1 - max > 0.00000000001) {
        dot_ans = dots[i];
        max = cos1;
      } else if (cos1 - max > -0.00000000001 && cos1 - max < 0.00000000001) {
        long long int delta_x = dot2.first - dot_ans.first;
        long long int delta_y = dot2.second - dot_ans.second;
        long long int delta_x1 = dot2.first - dots[i].first;
        long long int delta_y1 = dot2.second - dots[i].second;
        if (delta_x * delta_x + delta_y * delta_y < delta_x1 * delta_x1 + delta_y1 * delta_y1) {
          dot_ans = dots[i];
        }
      }
    }
    // dkffks
    if (dot_ans == ans[1]) {
      break;
    }
    ans.push_back(dot_ans);
  }
  std::cout << ans.size() - 1 << "\n";
  for (std::vector<std::pair<long long int, long long int> >::size_type i = 1; i != ans.size(); ++i) {
    std::cout << ans[i].first << " " << ans[i].second << "\n";
  }
  int64_t square = 0;
  int64_t add = 0;
  ans.push_back(ans[1]);
  for (std::vector<std::pair<long long int, long long int> >::size_type i = 1; i != ans.size() - 1; ++i) {
    std::pair<long long int, long long int> dot1 = ans[i];
    std::pair<long long int, long long int> dot2 = ans[i + 1];
    if ((dot1.first * dot2.second - dot2.first * dot1.second) % 2 != 0) {
      ++add;
      if (add == 2) {
        add = 0;
        ++square;
      }
    }
    square += (dot1.first * dot2.second - dot2.first * dot1.second - std::abs((dot1.first * dot2.second - dot2.first * dot1.second) % 2)) / 2;
  }
  std::cout << std::abs(square) - (add != 0 && std::abs(square) != square ? 1 : 0) << "." << (add == 0 ? 0 : 5) << "\n"  ;
}

