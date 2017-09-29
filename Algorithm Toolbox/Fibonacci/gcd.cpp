#include <iostream>

int gcd_naive(int a, int b) {
	int current_gcd = 1;
	int aa = a >= b ? a : b;
	int bb = a < b ? a : b;
	while (bb != 0) {
		int q = aa%bb;
		aa = bb;
		bb = q;
	}

	return aa;
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << gcd_naive(a, b) << std::endl;
	return 0;
}
