#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void explore(vector<vector<long long> >&adj, vector<long long> & visited, stack<long long>&order, long long node) {
	visited[node] = 1;
	for (long long i = 0; i < adj[node].size(); i++) {
		if (visited[adj[node][i]] != 1)
			explore(adj, visited, order, adj[node][i]);
	}
	order.push(node);
}

void explore_SSC(vector<vector<long long> >&adj_rev, vector<long long> & visited, long long node) {
	visited[node] = 1;
	for (long long i = 0; i < adj_rev[node].size(); i++) {
		if (visited[adj_rev[node][i]] != 1)
			explore_SSC(adj_rev, visited, adj_rev[node][i]);
	}
}

void DFS(vector<vector<long long> >&adj, stack<long long>&order) {
	vector<long long>visited(adj.size(), 0);
	for (long long i = 0; i < adj.size(); i++) {
		if (visited[i] == 0)
			explore(adj, visited, order, i);
	}
}

long long DFS_REV(vector<vector<long long> >&adj_rev, stack<long long>&order) {
	long long count = 0;
	vector<long long>visited(adj_rev.size(), 0);
	while (order.size()) {
		if (visited[order.top()] == 0) {
			explore_SSC(adj_rev, visited, order.top());
			order.pop();
			count++;
		}
		else if (visited[order.top()] == 1)order.pop();

	}
	return count;
}

//void topsort (vector<vector<long long> >&adj, stack<long long>&order) {
//	DFS()
//}


long long number_of_strongly_connected_components(vector<vector<long long> >&adj, vector<vector<long long> >&adj_rev) {
	stack<long long>order;
	DFS(adj, order);
	return DFS_REV(adj_rev, order);

	//write your code here
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	vector<vector<long long>>adj_rev(n, vector<long long>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj_rev[y - 1].push_back(x - 1);
	}
	std::cout << number_of_strongly_connected_components(adj, adj_rev);
}
