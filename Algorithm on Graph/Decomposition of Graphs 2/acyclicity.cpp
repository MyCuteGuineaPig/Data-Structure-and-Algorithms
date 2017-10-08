#include <iostream>
#include <vector>

using namespace std;


void explore(vector<vector<long long> > &adj, vector<long long>&visited, long long t, long long result, bool & get) {
	visited[t] = 1;
	for (long long i = 0; i < adj[t].size(); i++) {
		if (adj[t][i] == result) {
			get = true;
			return;
		}
		if (adj[adj[t][i]].size() > 0 && visited[adj[t][i]] != 1) explore(adj, visited, adj[t][i], result, get);
	}
}


int DFS(vector<vector<long long> > &adj) {
	vector<long long>visited(adj.size(), 0);
	for (long long i = 0; i < adj.size(); i++) {
		if (adj[i].size() > 0 && visited[i] != 1) {
			bool get = false;
			explore(adj, visited, i, i, get);
			if (get == true) return 1;
		}
	}
	return 0;
}

long long acyclic(vector<vector<long long> > &adj) {
	//write your code here

	return 0;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	for (size_t i = 0; i < m; i++) {
		long long x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	std::cout << DFS(adj);
}
