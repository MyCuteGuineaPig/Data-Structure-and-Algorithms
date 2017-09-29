#include <iostream>
#include <vector>
#include <numeric>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
	if (to == 0) return 0;
	long long remainder = (to + 1) % 60, quote = (to + 1) / 60;
	long long remainder0 = from % 60, quote0 = from / 60;
	vector<int>digit;
	digit.push_back(0); digit.push_back(1);
	for (int i = 2; i < 60; i++)
		digit.push_back((digit[i - 1] + digit[i - 2]) % 10);
	if (remainder0 <= remainder)
		return ((accumulate(digit.begin(), digit.end(), 0))*(quote - quote0) + accumulate(digit.begin() + remainder0, digit.begin() + remainder, 0)) % 10;
	else
		return ((accumulate(digit.begin(), digit.end(), 0))*(quote - quote0 - 1)
			+ accumulate(digit.begin() + remainder0, digit.end(), 0) +
			accumulate(digit.begin(), digit.begin() + remainder, 0)) % 10;

}


int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
