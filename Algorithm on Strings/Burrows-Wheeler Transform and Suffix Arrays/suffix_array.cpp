#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

long long cal_rank(char a) {
	switch (a) {
	case '$': return 0;
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	}
}

struct suffix {
	long long rank[2];
	long long index;
	suffix(long long _index, long _r1, long _r2) : index(_index) {
		rank[0] = _r1;
		rank[1] = _r2;
	}
};


void BuildSuffixArray(const string& text, vector<suffix>& sf) {
	vector<long long> result;
	for (long long i = 0; i < text.size(); i++) {
		if (i < text.size() - 1)
			sf.push_back(suffix(i, cal_rank(text[i]), cal_rank(text[i + 1])));
		else
			sf.push_back(suffix(i, cal_rank(text[i]), 0));
		//cout << sf[i].index <<" i " <<i<< "  rank[0]  "<< sf[i].rank[0] << "  rank[1]  "<< sf[i].rank[1]<<endl;
	} // build the first rank 1, rank 2;

	sort(sf.begin(), sf.end(), [](suffix a, suffix b) {
		if (a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
		else  return a.rank[1] < b.rank[1];
	});

	bool update = false;
	for (long long k = 2; k < text.size(); k *= 2, update = false) { // build the next k
		vector<long long> temp_index(sf.size(), 0);
		long long prev_rank = sf[0].rank[0];
		sf[0].rank[0] = 0;
		for (long long i = 1, rank = 0; i < sf.size(); i++) {
			if (sf[i].rank[0] == prev_rank && sf[i].rank[1] == sf[i - 1].rank[1]) {
				prev_rank = sf[i].rank[0];
				sf[i].rank[0] = rank;
				update = true;
			}
			else {
				prev_rank = sf[i].rank[0];
				sf[i].rank[0] = ++rank;
			}
			temp_index[sf[i].index] = i;
		}
		if (!update) break;
		for (long long i = 0; i < sf.size(); i++) {
			long long rank2 = sf[i].index + k < sf.size() ? sf[i].index + k : 0;
			sf[i].rank[1] = rank2 == 0 ? 0 : sf[temp_index[rank2]].rank[0];
		}
		sort(sf.begin(), sf.end(), [](suffix a, suffix b) {
			if (a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
			else return a.rank[1] < b.rank[1];
		});
	}

	// Implement this function yourself
	return;
}

int main() {
	string text;
	cin >> text;
	//vector<long long> suffix_array = BuildSuffixArray(text);
	vector<suffix> sf;
	BuildSuffixArray(text, sf);
	for (long long i = 0; i < sf.size(); ++i) {
		cout << sf[i].index << ' ';
	}
	cout << endl;
	return 0;
}
