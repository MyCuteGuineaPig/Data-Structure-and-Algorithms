#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long distance(vector<vector<long long> > &adj, long long s, long long t) {
	//write your code here
	long long nil = adj.size() + 1;
	vector<long long>dist(adj.size(), nil);
	queue<long long> q;
	q.push(s);
	dist[s] = 0;
	while (q.size()) {
		long long node = q.front();
		q.pop();
		for (long long i = 0; i < adj[node].size(); i++) {
			if (adj[node][i] == t) return dist[node] + 1;
			if (dist[adj[node][i]] == nil) {
				q.push(adj[node][i]);
				dist[adj[node][i]] = dist[node] + 1;
			}
		}

	}
	return -1;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	for (long long i = 0; i < m; i++) {
		long long x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	long long s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, s, t);
}
