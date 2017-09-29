#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int get_majority_element(vector<long long> &a) {
		int ct = 1;
		long long major = a[0];
		for (int i = 1; i < a.size(); i++)
		{
			if (ct == 0) {
				ct = 1;
				major = a[i];
			}
			else if (major == a[i]) ct++;
			else ct--;
		}
	
		return count(a.begin(), a.end(),major) > a.size()/2 ? 1 : 0;
	}


int main() {
  int n;
  std::cin >> n;
  vector<long long> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << get_majority_element(a) << '\n';
}
