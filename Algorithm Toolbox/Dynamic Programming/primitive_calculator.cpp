#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long min_num(long long a, long long b, long long c) {
	long long temp_min = ((a < b) ? a : b);
	return temp_min < c ? temp_min : c;
}

vector<long long > optimal_sequence(long long  n) {
	std::vector<long long> seq(n + 1, 0);
	for (long long i = 2; i <= n; i++) {
		long long  add = seq[i - 1] + 1, multi2 = seq[i - 1] + 1, multi3 = seq[i - 1] + 1;
		if (i % 2 == 0) multi2 = seq[i / 2] + 1;
		if (i % 3 == 0) multi3 = seq[i / 3] + 1;
		seq[i] = min_num(add, multi2, multi3);
	}
	vector<long long>cnt(seq[n] + 1, 1);
	cnt[seq[n]] = n;
	for (long long i = n, j = seq[n] - 1; i>1 && j>0;) {
		if (i % 3 == 0 && seq[i / 3] == seq[i] - 1) {
			i /= 3;
			cnt[j--] = i;
		}
		else if (i % 2 == 0 && seq[i / 2] == seq[i] - 1) {
			i /= 2;
			cnt[j--] = i;
		}
		else {
			--i;
			cnt[j--] = i;
		}

	}
	cout << seq[n] << endl;
	return cnt;
}
int main() {
  long long n;
  std::cin >> n;
  vector<long long> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
