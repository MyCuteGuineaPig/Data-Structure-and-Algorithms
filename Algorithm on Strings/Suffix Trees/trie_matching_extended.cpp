#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, long long> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
	trie t;
	for (long long i = 0, new_node = 1; i < patterns.size(); i++) {
		for (long long j = 0, find_layer = 0; j < patterns[i].size(); j++) {
			if (t.size() < find_layer + 1) {// less than currect root level push back
				while (t.size() < find_layer)
				{
					edges fake_edge;
					t.push_back(fake_edge);
				}
				edges new_edges;
				find_layer = new_node;
				new_edges[patterns[i][j]] = new_node++;
				t.push_back(new_edges);
			}
			else if (t[find_layer].count(patterns[i][j]) == 0) { // cannot find char at current level, push back
				t[find_layer][patterns[i][j]] = new_node++;
				find_layer = new_node - 1;
			}
			else
				find_layer = t[find_layer][patterns[i][j]]; // find keep down
		}
	}

	// write your code here
	return t;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<string> patterns;
	for (size_t i = 0; i < n; i++) {
		string s;
		std::cin >> s;
		patterns.push_back(s);
	}
	trie t = build_trie(patterns);
	for (size_t i = 0; i < t.size(); ++i) {
		for (const auto & j : t[i]) {
			std::cout << i << "->" << j.second << ":" << j.first << "\n";
		}
	}

	return 0;
}