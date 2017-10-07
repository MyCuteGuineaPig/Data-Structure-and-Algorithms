#include <iostream>
#include <vector>

using namespace std;

void explore(vector<long long> & visited, vector<vector<long long> > &adj, long long node, long long result, int & re) {
	visited[node] = 1;
	for (long long i = 0; i < adj[node].size(); i++) {
		if (adj[node][i] == result) {
			re = 1;
			return;
		}
		if (visited[adj[node][i]] != 1)
			explore(visited, adj, adj[node][i], result, re);
	}
}


//int reach(vector<vector<long long> > &adj , long long a, long long b) {
//	int t = -1;
//	if (adj[b].size() < adj[a].size())
//		swap(a, b);
//	for (long long i = 0; i < adj[a].size(); i++)
//		if (adj[a][i] == b)
//			return 1;
//	return 0;
//}


void print(vector<vector<long long> > &adj) {
	for (long long i = 0; i < adj.size(); i++) {
		cout << " [" << i << "] : ";
		for (long long j = 0; j < adj[i].size(); j++)
			cout << adj[i][j] << " ";
		cout << endl;
	}
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
	long long a, b;
	cin >> a >> b;
	vector<long long>visited(n);
	int re = 0;
	explore(visited, adj, b - 1, a - 1, re);
	std::cout << re;
}
