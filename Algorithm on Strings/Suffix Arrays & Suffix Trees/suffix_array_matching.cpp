#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>
using namespace std;

string text;
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

int cal_rank(char a) {
	switch (a) {
	case '$': return 0;
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	}
}

void computer_order(vector < long long> &order) {
	long long count[5] = { 0 };
	for (long long i = 0; i < text.size(); i++) {
		count[cal_rank(text[i])]++;
	}
	for (int i = 1; i < 5; i++)
		count[i] += count[i - 1];
	for (long long i = text.size() - 1; i >= 0; i--) {
		count[cal_rank(text[i])]--;
		order[count[cal_rank(text[i])]] = i;
	}
}

void computer_class(vector < long long> & class1, vector < long long> &order) {
	class1[order[0]] = 0;
	for (long long i = 1; i < text.size(); i++) {
		if (text[order[i]] == text[order[i - 1]])
			class1[order[i]] = class1[order[i - 1]];
		else
			class1[order[i]] = class1[order[i - 1]] + 1;
	}
}

void computer_order_cyclic(vector < long long> & class1, vector < long long> &order, vector < long long> &order2, long long L) {
	vector<long long>count(order.size(), 0);
	for (long long i = 0; i < class1.size(); i++) {
		count[class1[i]]++;
	}
	for (long long i = 1; i < class1.size(); i++)
		count[i] += count[i - 1];
	for (long long i = order.size() - 1; i >= 0; i--) {
		long long start = order[i] - L >= 0 ? order[i] - L : class1.size() - L + order[i];
		count[class1[start]]--;
		order2[count[class1[start]]] = start;
	}
	//order = new_order;
}

void update_class_cylic(vector < long long> & class1, vector < long long> & class2, vector < long long> &order, long long L) {
	//class1[order[0]] = 0;
	class2[order[0]] = 0;
	for (long long i = 1; i < class1.size(); i++) {
		long long cur = order[i], prev = order[i - 1];
		long long cur_begin = cur + L < class1.size() ? cur + L : cur + L - class1.size();
		long long prev_begin = prev + L < class1.size() ? prev + L : prev + L - class1.size();
		if (class1[cur] == class1[prev] && class1[cur_begin] == class1[prev_begin]) {
			class2[cur] = class2[prev];
		}
		else {
			class2[cur] = class2[prev] + 1;
		}

	}
	//cout << "cyclic class " << endl;
	//for (auto i : class1)
	//	cout << i << " ";
	//cout << endl;
}

//1 order1, 2 order 2, 4 order1

void BuildSuffixArray(vector<long long> & result) {


	vector < long long>order(text.size(), 0);
	vector<long long>order2(text.size(), 0);

	vector < long long> class1(text.size(), 0);
	vector < long long>class2(text.size(), 0);

	computer_order(order);
	computer_class(class1, order);
	long long L = 1, count = 0;
	while (L < text.size()) {
		if (count % 2 == 0) {
			computer_order_cyclic(class1, order, order2, L);
			update_class_cylic(class1, class2, order2, L);
		}
		else {
			computer_order_cyclic(class2, order2, order, L);
			update_class_cylic(class2, class1, order, L);
		}
		L *= 2;
		count++;
	}
	if ((count - 1) % 2 == 0)
		for (long long i = 0; i < class1.size(); i++) {
			result[class2[i]] = i;
		}

	else
		for (long long i = 0; i < class1.size(); i++)
			result[class1[i]] = i;
	// Implement this function yourself
	return;
}

void bwt(vector<long long> & result, unordered_map<char, long long> &firstOccurence, unordered_map<char, vector<long long>> & countsymbol) {
	for (long long i = 0, j = 0; i < result.size() && j < 5; i++)
		if (firstOccurence[text[result[i]]] == 0)
			firstOccurence[text[result[i]]] = i, j++;
	for (auto m : firstOccurence) {
		countsymbol[m.first] = vector<long long>(text.size() + 1, 0);
	}

	for (long long i = 0; i < text.size(); i++) {
		for (auto ii : firstOccurence)
			countsymbol[ii.first][i + 1] += countsymbol[ii.first][i];
		long long before = result[i] - 1 >= 0 ? result[i] - 1 : result.size() - 1;
		++countsymbol[text[before]][i + 1];
	}
}


void FindOccurrences(string & pattern, vector<long long> & suffix_array, unordered_map<char, long long> & firstOccurence, unordered_map<char, vector<long long>> &countsymbol, vector<long long> & occurrences, unordered_set<long long>&set) {
	long long top = 0, bottom = text.size() - 1, j = pattern.size() - 1;
	while (top <= bottom) {

		if (j >= 0) {
			if (firstOccurence.count(pattern[j]) == 0) return;
			top = firstOccurence[pattern[j]] + countsymbol[pattern[j]][top];
			bottom = firstOccurence[pattern[j]] + countsymbol[pattern[j]][bottom + 1] - 1;
			j--;
		}
		else {
			for (long long i = top; i <= bottom; i++) {
				if (set.count(suffix_array[i]) == 0) {
					occurrences.push_back(suffix_array[i]);
					set.insert(suffix_array[i]);
				}

			}
			break;
		}
	}

}

int main() {
	cin >> text;

	text += '$';
	vector<long long> suffix_array(text.size(), 0);

	BuildSuffixArray(suffix_array);
	unordered_map<char, long long> firstOccurence;
	unordered_map<char, vector<long long>> countsymbol;

	vector<long long> occurrences;
	unordered_set<long long>set;

	bwt(suffix_array, firstOccurence, countsymbol);

	long long pattern_count;
	cin >> pattern_count;
	vector<bool> occurs(text.length(), false);
	for (long long pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
		string pattern;
		cin >> pattern;
		FindOccurrences(pattern, suffix_array, firstOccurence, countsymbol, occurrences, set);
	}
	for (int i = 0; i < occurrences.size(); ++i) {
		cout << occurrences[i] << " ";
	}
	printf("\n");
	return 0;
}
