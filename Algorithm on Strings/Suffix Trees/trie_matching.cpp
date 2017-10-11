#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int const Letters = 4;
int const NA = -1;

struct Node
{
	long long next[Letters];

	Node() { fill(next, next + Letters, NA); }

	bool isLeaf() const
	{
		return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex(char letter)
{
	switch (letter)
	{
	case 'A': return 0; break;
	case 'C': return 1; break;
	case 'G': return 2; break;
	case 'T': return 3; break;
	default: assert(false); return -1;
	}
}

typedef unordered_map<char, long long> edges;
typedef vector<edges> tire;


void build_Trie(vector <string>& patterns, tire & t)
{
	for (long long i = 0, node = 0; i < patterns.size(); i++) {
		patterns[i].append("$");
		for (long long j = 0, next_layer = 0; j < patterns[i].size(); j++)
		{
			if (t.size() < next_layer + 1) {
				while (t.size() < next_layer) {
					edges fake_edges;
					t.push_back(fake_edges);
				}
				edges edge;
				edge[patterns[i][j]] = ++node;
				next_layer = node;
				t.push_back(edge);
			}
			else if (t[next_layer].count(patterns[i][j]) == 0) {
				t[next_layer][patterns[i][j]] = ++node;
				next_layer = node;
			}
			else
				next_layer = t[next_layer][patterns[i][j]];
		}
	}

}

bool detect(const string& text, tire& t, long long start) {
	for (long long i = start, next_layer = 0; 1 > 0; i++) {
		if (t[next_layer].count('$') > 0) return true;
		else if (t[next_layer].count(text[i]) == 0)
			return false;
		else
			next_layer = t[next_layer][text[i]];
	}
	return false;
}


vector <long long> solve(const string& text, long long n, vector <string>& patterns)
{
	vector <long long> result;
	//vector <Node>t;
	tire t;
	build_Trie(patterns, t);
	//for (size_t i = 0; i < t.size(); ++i) {
	//	for (const auto & j : t[i]) {
	//		std::cout << i << "->" << j.second << ":" << j.first << "\n";
	//	}
	//}

	for (long long i = 0; i < text.size(); i++) {
		if (detect(text, t, i)) {
			result.push_back(i);
		}
	}
	//// write your code here

	return result;
}

int main(void)
{
	string t;
	cin >> t;

	long long n;
	cin >> n;

	vector <string> patterns(n);
	for (long long i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <long long> ans;
	ans = solve(t, n, patterns);

	for (long long i = 0; i < (long long)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (long long)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
