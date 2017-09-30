#include <iostream>
#include <vector>

using namespace std;

long long maxx(long long a, long b, long long c) {
	long long temp_max = a > b ? a : b;
	long long temp_max2 = temp_max > c ? temp_max : c;
	return temp_max2;
}

long long lcs3(vector<long long > &a, vector<long long > &b, vector<long long > &c) {
	vector < vector<vector<long long>>> t(a.size() + 1,
		vector<vector<long long>>(b.size() + 1, vector<long long>(c.size() + 1, 0)));
	for (int i = 1; i <= a.size(); i++) {
		for (int j = 1; j <= b.size(); j++) {
			for (int k = 1; k <= c.size(); k++) {
				if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
					t[i][j][k] = t[i - 1][j - 1][k - 1] + 1;
				else
					t[i][j][k] = maxx(t[i - 1][j][k], t[i][j - 1][k], t[i][j][k - 1]);
			}
		}
	}

	//write your code here
	return t[a.size()][b.size()][c.size()];
}
int main() {
  size_t an;
  std::cin >> an;
  vector<long long> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<long long> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<long long> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
