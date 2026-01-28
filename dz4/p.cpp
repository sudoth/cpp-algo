#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

ostream& operator<<(ostream& os, const vector<int>& s) {
  for (size_t i = 0; i < s.size(); ++i) {
    os << s[i];
  }
  return os;
}

int main(int argc, char** argv) {
  std::string s("abcdefdefabc");
  std::string v("erabcd");
  std::cout << prefix_function(s) << '\n';
  std::cout << prefix_function(v);
}