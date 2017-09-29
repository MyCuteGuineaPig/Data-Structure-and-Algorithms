#include <iostream>

int fibonacci_sum_naive(long long n) {
	if (n == 0) return 0;
	int r[3] = { 0,1,0 };
	int d = 1;
	for (long long i = 2; i <= n; d = (d + r[i % 3]) % 10, i++)
		r[i % 3] = (r[(i - 1) % 3] + r[(i - 2) % 3]) % 10;
	return d;
}

int main() {
	long long n = 0;
	std::cin >> n;
	std::cout << fibonacci_sum_naive(n);
}
