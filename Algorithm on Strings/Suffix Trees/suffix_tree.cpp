#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
struct pt {
	long long first;
	long long end;
	long long next;
	pt() { first = 0; end = 0; next = 0; }
	pt(long long _first, long long _end, long long _next) {
		first = _first; end = _end; next = _next;
	}
};


vector<vector<pt>> ComputeSuffixTreeEdges(const string& text) {
	vector<vector<pt>>re;
	if (text.size() == 0) return re;
	long long size = text.size();
	vector<pt> new_pt = { pt(0, size - 1, -1) };
	re.push_back(new_pt);

	for (long long i = 1; i < size; ) {
		long long j = i, next_layer = 0; //j for text
		for (long long k = 0; k < re[next_layer].size(); k++) {//k for count at certain layer
			if (text[re[next_layer][k].first] == text[j]) { //first match continue search
				for (long long n = re[next_layer][k].first; k >= 0 && n <= re[next_layer][k].end; n++, j++) {
					if (text[n] != text[j]) {
						vector<pt> new_pt = { pt(n, re[next_layer][k].end,re[next_layer][k].next),
							pt(j, size - 1, -1) };//two sub-brunch
												  // n 是 sub distance 对于old 的leaves
												  // j 是现在的sub tree 当j 与老的tree 不match了
						re.push_back(new_pt); // modify the old, shrink 
						re[next_layer][k].end = n - 1; // n 是老的
						re[next_layer][k].next = re.size() - 1;// 指向下一层
						goto label; // quit the search loop, done for this string，因为已经产生两个sub leaves
					}
					if (n == re[next_layer][k].end) { // change for another leaves, 这层已经没了。layer 层第k个leaves
						// 所有的leaves 都对应上了
						next_layer = re[next_layer][k].next;
						k = -1;
					}
				}
			}
			else if (k == re[next_layer].size() - 1) { // 没有在第next layer层找到相应的string，
				//就产生新的subtree
				re[next_layer].push_back(pt(j, size - 1, -1));
				break;
			}
		}
	label:
		i++;
	}

	// Implement this function yourself
	return re;
}

int main() {
	string text;
	cin >> text;
	vector<vector<pt>> edges = ComputeSuffixTreeEdges(text);
	for (long long i = 0; i < edges.size(); ++i) {
		// cout << "size" << edges[i].size() << endl;
		for (long long j = 0; j<edges[i].size(); j++)
			cout << text.substr(edges[i][j].first, edges[i][j].end - edges[i][j].first + 1) << endl;
	}
	return 0;
}
