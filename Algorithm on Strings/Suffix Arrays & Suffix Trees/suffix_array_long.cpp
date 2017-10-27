#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

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

void computer_order(const string& text, vector < long long> &order) {
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

void computer_class(const string& text, vector < long long> & class1, vector < long long> &order) {
	class1[order[0]] = 0;
	for (long long i = 1; i < text.size(); i++) {
		if (text[order[i]] == text[order[i - 1]])
			class1[order[i]] = class1[order[i - 1]];
		else
			class1[order[i]] = class1[order[i - 1]] + 1;
	}
	//cout << "class " << endl;
	//for (auto i : class1)
	//	cout << i << " ";
	//cout << endl;
}

void computer_order_cyclic(vector < long long> & class1, vector < long long> &order, long long L) {
	vector<long long>count(order.size(), 0);
	vector<long long>new_order(order.size(), 0);
	for (long long i = 0; i < class1.size(); i++) {
		count[class1[i]]++;
	}
	for (long long i = 1; i < class1.size(); i++)
		count[i] += count[i - 1];
	for (long long i = order.size() - 1; i >= 0; i--) {
		//start = i // i + L < class1.size() ? i + L : i + L - class1.size();
		long long start = order[i] - L >= 0 ? order[i] - L : class1.size() - L + order[i];
		count[class1[start]]--;
		new_order[count[class1[start]]] = start;
	}
	order = new_order;
	/*cout << "cyclic order " << endl;
	for (auto i : order)
	cout << i << " ";
	cout << endl;*/
}

void update_class_cylic(vector < long long> & class1, vector < long long> &order, long long L) {
	//class1[order[0]] = 0;
	vector < long long> new_class(order.size(), 0);
	for (long long i = 1; i < class1.size(); i++) {
		long long cur = order[i], prev = order[i - 1];
		long long cur_begin = cur + L < class1.size() ? cur + L : cur + L - class1.size();
		long long prev_begin = prev + L < class1.size() ? prev + L : prev + L - class1.size();
		if (class1[cur] == class1[prev] && class1[cur_begin] == class1[prev_begin]) {
			new_class[cur] = new_class[prev];
		}
		else {
			new_class[cur] = new_class[prev] + 1;
		}

	}
	class1 = new_class;
	//cout << "cyclic class " << endl;
	//for (auto i : class1)
	//	cout << i << " ";
	//cout << endl;
}

//long long cur = i + L < class1.size() ? i + L : i + L - class1.size();
//count[class1[cur]] --;
//new_order[class1[cur]] = i;

vector<long long> BuildSuffixArray(const string& text) {
	vector<long long> result(text.size(), 0);
	vector < long long>order(text.size(), 0);
	vector < long long>class1(text.size(), 0);
	computer_order(text, order);
	computer_class(text, class1, order);
	long long L = 1;
	while (L < text.size()) {
		computer_order_cyclic(class1, order, L);
		update_class_cylic(class1, order, L);
		L *= 2;
	}
	for (long long i = 0; i < class1.size(); i++) {
		result[class1[i]] = i;
	}
	// Implement this function yourself
	return result;
}

int main() {
	cin >> text;
	vector<long long> suffix_array = BuildSuffixArray(text);
	for (long long i = 0; i < suffix_array.size(); ++i) {
		cout << suffix_array[i] << ' ';
	}
	cout << endl;
	return 0;
}
