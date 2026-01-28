#include <iostream>
using namespace std;


int main() {
  int cnt = 0;
for ( unsigned char i = 1; i > 0; i += 7, ++cnt) {
  std::cout << (int) i << ' ' << cnt << '\n';
}
}