#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

// Data structure to store edges of a suffix tree.
struct Edge {
	// The ending node of this edge.
	long long depth;
	// Starting position of the substring of the text 
	// corresponding to the label of this edge.
	long long start;
	// Position right after the end of the substring of the text 
	// corresponding to the label of this edge.
	long long end;
	map<char, Edge*>children;
	Edge * parent;

	//Edge(long long node_, long long start_, long long end_) : depth(node_), start(start_), end(end_) {}
	//Edge(const Edge& e) : depth(e.node), start(e.start), end(e.end) {}
	Edge() { parent = NULL, depth = 0, start = -1, end = -1; }
	Edge(long long _start, long long _depth, long long _end, Edge * _parent)
	{
		parent = _parent, depth = _depth, start = _start, end = _end;
	}
};

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
void SuffixTreeFromSuffixArray(
	const vector<long long>& suffix_array,
	const vector<long long>& lcp_array,
	const string& text, Edge* tree) {

	Edge *curNode = tree;
	for (long long i = 0, lcpPrev = 0; i < suffix_array.size(); i++) {
		long long suffix = suffix_array[i];
		while (curNode->depth > lcpPrev) {
			curNode = curNode->parent;
		}

		if (curNode->depth == lcpPrev) {
			Edge *leaf = new Edge(suffix + curNode->depth, text.size() - suffix, text.size() - 1, curNode);
			curNode->children[text[leaf->start]] = leaf;
			/*cout << "create new children " << suffix << " " << suffix + curNode->depth;
			cout << " " << text.size() - suffix << " " << text.size() - 1 << endl<<endl;*/
		}
		else {
			long long new_start = suffix_array[i - 1] + curNode->depth;
			long long off_set = lcpPrev - curNode->depth;

			Edge *middle = new Edge(new_start, lcpPrev, off_set + new_start - 1, curNode);
			Edge *children = curNode->children[text[new_start]];
			middle->children[text[off_set + new_start]] = children;
			children->start = children->start + off_set;
			children->parent = middle;
			curNode->children[text[new_start]] = middle;

			/*cout << "repair middle " << suffix << " " << middle->start << " " << middle->depth;
			cout << " " << middle->end << endl;
			cout << "repair old " << suffix << " " << children->start << " " << children->depth;
			cout << " " << children->end << endl;*/

			Edge *leaf = new Edge(suffix + middle->depth, text.size() - suffix, text.size() - 1, middle);
			middle->children[text[leaf->start]] = leaf;
			/*cout << "repair new " << suffix << " " << leaf->start << " " << leaf->depth;
			cout << " " << leaf->end << endl<<endl;*/
			curNode = leaf;
		}
		if (i < lcp_array.size())
			lcpPrev = lcp_array[i];
	}
	// Implement this function yourself
}

void print_result(Edge * edge) {
	if (edge->start != -1)
		cout << edge->start << " " << edge->end + 1 << endl;
	for (auto i : edge->children) {
		print_result(i.second);
	}
}


int main() {
	string text;
	cin >> text;
	vector<long long> suffix_array(text.length());
	for (long long i = 0; i < text.length(); ++i) {
		cin >> suffix_array[i];
	}
	vector<long long> lcp_array(text.length() - 1);
	for (long long i = 0; i + 1 < text.length(); ++i) {
		cin >> lcp_array[i];
	}
	// Build the suffix tree and get a mapping from 
	// suffix tree node ID to the list of outgoing Edges.
	//unordered_map<int, vector<Edge> > tree();

	Edge* tree = new Edge();
	SuffixTreeFromSuffixArray(suffix_array, lcp_array, text, tree);
	cout << text << endl;
	print_result(tree);

	// Output the edges of the suffix tree in the required order.
	// Note that we use here the contract that the root of the tree
	// will have node ID = 0 and that each vector of outgoing edges
	// will be sorted by the first character of the corresponding edge label.
	//
	// The following code avoids recursion to avoid stack overflow issues.
	// It uses a stack to convert recursive function to a while loop.
	// The stack stores pairs (node, edge_index). 
	// This code is an equivalent of 
	//
	//    OutputEdges(tree, 0);
	//
	// for the following _recursive_ function OutputEdges:
	//
	// void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
	//   const vector<Edge>& edges = tree[node_id];
	//   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
	//     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
	//     OutputEdges(tree, edges[edge_index].node);
	//   }
	// }
	//
	//vector<pair<long long, long long> > stack(1, make_pair(0, 0));
	//while (!stack.empty()) {
	//	pair<long long, long long> p = stack.back();
	//	stack.pop_back();
	//	int node = p.first;
	//	int edge_index = p.second;
	//	if (!tree.count(node)) {
	//		continue;
	//	}
	//	const vector<Edge>& edges  = tree[node];
	//	if (edge_index + 1 < edges.size()) {
	//		stack.push_back(make_pair(node, edge_index + 1));
	//	}
	//	printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
	//	stack.push_back(make_pair(edges[edge_index].node, 0));
	//}


	return 0;
}
