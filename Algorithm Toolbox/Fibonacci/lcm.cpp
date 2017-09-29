#include <iostream>

long long lcm_naive(int a, int b) {
	int aa = a >= b ? a : b;
	int bb = a < b ? a : b;
	while (bb != 0) {
		int q = aa % bb;
		aa = bb;
		bb = q;
	}

	return (long long)a / aa*b;
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << lcm_naive(a, b) << std::endl;
	return 0;
}
