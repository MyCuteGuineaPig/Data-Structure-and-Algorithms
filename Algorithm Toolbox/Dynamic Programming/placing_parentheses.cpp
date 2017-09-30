#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a *b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}

tuple<long long, long long > maxandmin(long long a, long long b, long long c, long long d) //1st is min 2nd is max
{
	long long temp_min = a < b ? a : b;
	long long temp_max = a > b ? a : b;
	long long temp_min2 = temp_min < c ? temp_min : c;
	long long temp_max2 = temp_max > c ? temp_max : c;
	long long temp_min3 = temp_min2 < d ? temp_min2 : d;
	long long temp_max3 = temp_max2 > d ? temp_max2 : d;

	return make_tuple(temp_min3, temp_max3);
}

long long get_maximum_value(const string &exp) {
	long long len = (exp.length() + 1) / 2;
	vector<vector<long long>>Mt(len, vector<long long>(len, 0));
	vector<vector<long long>>mt(len, vector<long long>(len, 0));
	for (long long i = 0; i < len; i++) {
		Mt[i][i] = (long long)(exp[2 * i] - '0' + 0); 
		mt[i][i] = (long long)(exp[2 * i] - '0' + 0);
	}
	for (long long diff = 1; diff < len; diff++) {
		for (long long i = 0; i < len - diff; i++) {
			long long j = i + diff;
			long long tempmax = -922337203698547758;
			long long tempmin = 922337203698547758;
			for (long long k = i; k < j; k++) {

				long long minmin = eval(mt[i][k], mt[k + 1][j], exp[2 * k + 1]);
				long long maxmax = eval(Mt[i][k], Mt[k + 1][j], exp[2 * k + 1]);
				long long maxmin = eval(Mt[i][k], mt[k + 1][j], exp[2 * k + 1]);
				long long minmax = eval(mt[i][k], Mt[k + 1][j], exp[2 * k + 1]);

				long long maxnow, minnow;
				tie(minnow, maxnow) = maxandmin(minmin, maxmax, maxmin, minmax);
				tempmax = tempmax > maxnow ? tempmax : maxnow;
				tempmin = tempmin < minnow ? tempmin : minnow;
			}

			mt[i][j] = (long long)tempmin;
			Mt[i][j] = (long long)tempmax;
		}
	}
	return Mt[0][len - 1];
}


int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}                                                        
