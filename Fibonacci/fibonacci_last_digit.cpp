
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


int get_fibonacci_last_digit_naive(long long n) {
	if (n == 0) return 0;
	long long remainder = (n + 1) % 60, quote = (n + 1) / 60;
	vector<int>digit;
	digit.push_back(0); digit.push_back(1);
	for (int i = 2; i < 60; i++)
		digit.push_back((digit[i - 1] + digit[i - 2]) % 10);
	return ((accumulate(digit.begin(), digit.end(), 0))*quote + accumulate(digit.begin(), digit.begin() + remainder, 0)) % 10;
}


int main() {
	long long n;
	std::cin >> n;
	int c = get_fibonacci_last_digit_naive(n);
	std::cout << c << '\n';
}
