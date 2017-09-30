#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

string largest_number(vector<string> a) {
	//write your code here
	string result;
	//ret >> result;
	for (size_t i = 0; i < a.size(); i++) {
		result.append(a[i]);
	}

	return result;
}


class sort_num {
public:
	bool operator()(string a, string b) {
		if (a.size() == b.size()) return a > b;
		else {
			string aa = a + b, bb = b + a;
			if (aa == bb) return true;
			for (size_t i = 0; i < aa.size(); i++) {
				if (aa[i] != bb[i]) return aa[i] > bb[i];
			}
		}
	}
};
int main() {
  long long n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  sort(a.begin(), a.end(), sort_num());
  std::cout << largest_number(a);
}
