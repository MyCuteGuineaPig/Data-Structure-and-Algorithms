#include <iostream>
long long get_peroid(long long m) {
	int a = 0, b = 1, c = 0;
	for (int i = 0; i < m*m; i++) {
		c = (a + b) % m;
		a = b;
		b = c;
		if (a == 0 && b == 1) return i + 1;
	}
}

long long get_fibonacci_huge_naive(long long n, int m) {
	int period = n % get_peroid(m);
	int r[3] = { 0,1, period };
	for (int i = 2; i <= period; i++) {
		r[i % 3] = (r[(i - 1) % 3] + r[(i - 2) % 3]) % m;
	}
	return r[period % 3];
}
int main() {
	long long n, m;
	std::cin >> n >> m;
	std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
