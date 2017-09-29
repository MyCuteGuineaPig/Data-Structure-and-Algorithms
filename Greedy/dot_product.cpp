#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

long long max_dot_product(vector<long long> a, vector<long long> b) {
  // write your code here
  sort(a.begin(), a.end(), greater<long long>());
  sort(b.begin(), b.end(), greater<long long>());
  long long result = 0;
  for (long long i = 0; i < a.size(); i++)
	  result += (long long)(a[i] * b[i]);
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<long long> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
