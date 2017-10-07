#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
	long long  key;
	long long  left;
	long long  right;

	Node() : key(0), left(-1), right(-1) {}
	Node(long long  key_, long long  left_, long long  right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree, long long t, long long minnum, long long maxnum) {
	if (t == -1) return true;
	else if (tree[t].key < minnum || tree[t].key >= maxnum) {
		return false;
	}
	return IsBinarySearchTree(tree, tree[t].left, minnum, tree[t].key) && IsBinarySearchTree(tree, tree[t].right, tree[t].key, maxnum);
}

int main() {
	long long nodes;
	cin >> nodes;
	vector<Node> tree;
	for (long long i = 0; i < nodes; ++i) {
		long long  key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (nodes == 0) {
		cout << "CORRECT" << endl;
	}
	else if (IsBinarySearchTree(tree, 0, -1 * 922337203685477580, 9223372036854775807)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	return 0;
}