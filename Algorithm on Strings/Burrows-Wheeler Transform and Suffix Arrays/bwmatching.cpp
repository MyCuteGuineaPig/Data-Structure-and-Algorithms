#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

long long cal_rank(char a) {
	switch (a) {
	case '$': return 0;
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	}
}

struct LF {
	long long rank;
	long long index;
	LF(long long _index, long long _rank) : index(_index), rank(_rank) {}
	LF() {}
};



// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
	unordered_map<char, long long>& starts,
	unordered_map<char, vector<long long>>& occ_count_before) {
	// Implement this function yourself
	vector<LF>sf;
	for (long long i = 0; i < bwt.size(); i++) {
		sf.push_back(LF(i, cal_rank(bwt[i])));
	}
	//unordered_map<long long, long long>m;
	sort(sf.begin(), sf.end(), [](LF a, LF b) { if (a.rank == b.rank) return a.index < b.index;
	else return a.rank < b.rank; });
	for (long long i = 0; i < sf.size() && starts.size() < 5; i++) {
		if (starts.count(bwt[sf[i].index]) == 0) {
			starts[bwt[sf[i].index]] = i;
		}
	}

	for (auto m : starts) {
		occ_count_before[m.first] = vector<long long>(bwt.size() + 1, 0);
	}


	for (long long i = 0; i < bwt.size(); i++) {
		for (auto m : starts)
			occ_count_before[m.first][i + 1] = occ_count_before[m.first][i];
		++occ_count_before[bwt[i]][i + 1];
		//m[sf[i].index] = i;
	}

	//long long i = 0;
	//string result;
	//while (bwt[i] != '$') {
	//	result += bwt[i];
	//	i = m[i];
	//}
	//reverse(result.begin(), result.end());
	//cout << result << endl;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
	const string& bwt,
	unordered_map<char, long long>& starts,
	unordered_map<char, vector<long long> >& occ_count_before) {

	long long top = 0, bottom = bwt.size() - 1;
	long long j = pattern.size() - 1;
	while (top <= bottom) {

		if (j >= 0) {
			if (starts.count(pattern[j]) == 0) return 0;
			if (occ_count_before[pattern[j]][bottom+1]>0) {
				//cout << "pattern[j] " << pattern[j] << "  start " << starts[pattern[j]];
				//cout << "  occ_count_before[pattern[j]][top] " << occ_count_before[pattern[j]][top];
				//cout << "  occ_count_before[pattern[j]][bottom+1]-1 " << occ_count_before[pattern[j]][bottom+1] - 1 << endl;
				top = starts[pattern[j]] + occ_count_before[pattern[j]][top];
				bottom = starts[pattern[j]] + occ_count_before[pattern[j]][bottom + 1] - 1;
				//cout << "top " << top << "  bottom " << bottom << endl;
				j--;
			}
			else return 0;
		}
		else return bottom - top + 1;
	}

	// Implement this function yourself
	return 0;
}


int main() {
	string bwt;
	cin >> bwt;
	int pattern_count;
	cin >> pattern_count;
	// Start of each character in the sorted list of characters of bwt,
	// see the description in the comment about function PreprocessBWT
	//map<char, int> starts;

	unordered_map<char, long long>starts;

	// Occurrence counts for each character and each position in bwt,
	// see the description in the comment about function PreprocessBWT

	unordered_map<char, vector<long long>>occ_count_before;

	//map<char, vector<int> > occ_count_before;
	// Preprocess the BWT once to get starts and occ_count_before.
	// For each pattern, we will then use these precomputed values and
	// spend only O(|pattern|) to find all occurrences of the pattern
	// in the text instead of O(|pattern| + |text|).
	PreprocessBWT(bwt, starts, occ_count_before);
	for (int pi = 0; pi < pattern_count; ++pi) {
		string pattern;
		cin >> pattern;
		int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
		printf("%d ", occ_count);
	}
	printf("\n");
	return 0;
}
