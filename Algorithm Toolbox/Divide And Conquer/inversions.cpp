#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>

using namespace std;


void merge(vector<long long> &a, size_t left, size_t middle, size_t right, long long & count0) {
	vector<long long> temp(a.begin() + left, a.begin() + right + 1);
	size_t i = left, j = middle + 1, k = 0;
	while (i <= middle || j <= right) {
		if (i > middle) temp[k++] = a[j++];
		else if (j > right) temp[k++] = a[i++];
		else if (a[i] > a[j])
		{
			count0 += middle - i + 1;
			temp[k++] = a[j++];
		}
		else temp[k++] = a[i++];
	}
	for (size_t b = left; b <= right; b++)
		a[b] = temp[b - left];
}

void mergesort(vector<long long> &a, size_t left, size_t right, long long & num_inver) {
	if (left >= right) return;
	int middle = left + (right - left) / 2;
	mergesort(a, left, middle, num_inver);
	mergesort(a, middle + 1, right, num_inver);
	merge(a, left, middle, right, num_inver);
}
int main() {
	long long n;
	cin >> n;
	vector<long long> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	long long num_inver = 0;
	mergesort(a, 0, a.size() - 1, num_inver);
	std::cout << num_inver << '\n';
}
