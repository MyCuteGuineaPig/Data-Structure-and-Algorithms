#include <iostream>
#include <vector>

using namespace std;

long long max(long long a, long long b) {
	return a > b ? a : b;
}


long long optimal_weight(long long W, const vector<long long> &w) {
	//write your code here
	vector<vector<long long>>knapsack(w.size(), vector<long long>(W + 1, 0));
	long long current_weight = 0;
	for (size_t i = 1; i <w.size(); ++i) {
		for (size_t j = 1; j <= W; ++j) {
			knapsack[i][j] = knapsack[i - 1][j];
			if (w[i] <= j && knapsack[i - 1][j - w[i]] + w[i] <= W) {
				knapsack[i][j] = max(knapsack[i - 1][j - w[i]] + w[i], knapsack[i][j]);
			}
		}
	}
	return knapsack[w.size() - 1][W];
}

int main() {
	long long n, W;
  std::cin >> W >> n;
  vector<long long> w(n+1,0);
  for (long long i = 1; i <= n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
