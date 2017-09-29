#include <iostream>
#include <vector>

using std::vector;

vector<long long> optimal_summands(long long n) {
	vector <long long > summands;
	int i = 1;
	while (n > 0) {
		if (n <= 2 * i) {
			summands.push_back(n);
			n = 0;
		}
		else {
			summands.push_back(i);
			n = n - i;
			i++;
		}
	}
	//write your code here
	return summands;
}

int main() {
	long long n;
  std::cin >> n;
  vector<long long> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
