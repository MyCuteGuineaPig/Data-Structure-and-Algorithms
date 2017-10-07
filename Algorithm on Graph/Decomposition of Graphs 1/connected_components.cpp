#include <iostream>
#include <vector>

using namespace std;

void explore(vector<long long> & visited, vector<vector<long long> > &adj, long long node) {
	visited[node] = 1;
	for (long long i = 0; i < adj[node].size(); i++) {
		if (visited[adj[node][i]] != 1)
			explore(visited, adj, adj[node][i]);
	}
}


long long number_of_components(vector<vector<long long> > &adj) {
	vector<long long>visited(adj.size());
	long long cc = 0;
	for (long long i = 0; i < adj.size(); i++) {
		if (visited[i] != 1) {
			explore(visited, adj, i);
			cc++;
		}
	}
	//write your code here
	return cc;
}


int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	for (size_t i = 0; i < m; i++) {
		long long x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << number_of_components(adj);
}
