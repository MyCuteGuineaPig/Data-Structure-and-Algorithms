#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int cal_rank(char a) {
	switch (a) {
	case '$': return 0;
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	}
}

struct bwt {
	long long index;
	long long rank;
	bwt(long long _index, long long _rank) : index(_index), rank(_rank) {}
	bwt() {}
};


string InverseBWT(const string& text) {
	string result = "";
	vector<bwt> b;
	for (long long i = 0; i < text.size(); i++) {
		b.push_back(bwt(i, cal_rank(text[i])));
	}
	sort(b.begin(), b.end(), [](bwt x, bwt y) {
		if (x.rank != y.rank) return  x.rank < y.rank;
		else return x.index < y.index;
	});
	unordered_map<long long, long long>m;
	for (long long i = 0; i < b.size(); i++)
		m[b[i].index] = i;


	long long i = 0;
	while (text[i] != '$') {
		//cout << text[i] << endl;
		result += text[i];
		i = m[i];
	}
	reverse(result.begin(), result.end());
	// write your code here
	return result;
}

int main() {
	string text;
	cin >> text;
	cout << InverseBWT(text) + '$' << endl;
	return 0;
}
