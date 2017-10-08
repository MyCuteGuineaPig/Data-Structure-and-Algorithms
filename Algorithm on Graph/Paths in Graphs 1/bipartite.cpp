#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int  bipartite(vector<vector<long long > > &adj) {
	vector<int> color(adj.size(), 0);
	// 1 is white, -1 is red
	queue<long long> q;
	q.push(0);
	color[0] = 1;
	while (q.size()) {
		long long node = q.front();
		q.pop();
		for (long long i = 0; i < adj[node].size(); i++) {
			if (color[adj[node][i]] == 0) {
				q.push(adj[node][i]);
				color[adj[node][i]] = -1 * color[node];
			}
			else if (color[adj[node][i]] == color[node])
				return 0;
		}

	}

	//write your code here
	return 1;
}

int main() {
	long long  n, m;
	std::cin >> n >> m;
	vector<vector<long long > > adj(n, vector<long long >());
	for (long long i = 0; i < m; i++) {
		long long  x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << bipartite(adj);
}
