#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<long long> find_pattern(const string& pattern, const string& text) {
	vector<long long> result;
	vector<long long>kmp_table(pattern.size() + text.size(), 0);
	long long border = 0, p_size = pattern.size();
	for (long long i = 1; i < p_size; i++) {
		if (i == pattern.size() - 1) {
			border = 0;
			kmp_table[i] = 0;
		}
		else {
			while (border > 0 && pattern[i] != pattern[border]) {
				border = kmp_table[border - 1];
			}
			if (pattern[i] == pattern[border])
				border++;
			else
				border = 0;
			kmp_table[i] = border;
		}
	}
	for (long long i = p_size; i < p_size + text.size(); i++) {
		while (border > 0 && text[i - p_size] != pattern[border]) {
			border = kmp_table[border - 1];
		}
		if (text[i - p_size] == pattern[border])
			border++;
		else
			border = 0;
		kmp_table[i] = border;
		if (border == p_size - 1) {
			result.push_back(i - 2 * p_size + 2);
		}

	}
	// Implement this function yourself
	return result;
}

int main() {
	string pattern, text;
	cin >> pattern;
	cin >> text;
	pattern.append("$");
	vector<long long> result = find_pattern(pattern, text);
	for (long long i = 0; i < result.size(); ++i) {
		printf("%d ", result[i]);
	}
	printf("\n");
	return 0;
}
