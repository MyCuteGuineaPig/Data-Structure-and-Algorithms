#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct pt {
	long long id;
	long long weight;
	pt(long long id_, long long weight_) :
		id(id_), weight(weight_) {}
	bool operator< (const pt & p1) const {
		return p1.weight < weight;
	}
};


long long distance(vector<vector< long long> > &adj, vector<vector< long long> > &cost, long long s, long long t) {
	priority_queue<pt> pq;
	long long nil = -1;
	vector<long long>dist(adj.size(), -1);
	vector<long long>visited(adj.size(), 0);
	pq.push(pt(s, 0)); dist[s] = 0;
	while (pq.size()) {
		long long id = pq.top().id;
		//dist[id] = pq.top().weight;

		//cout << "id " << id <<"  dist "<<pq.top().weight << endl;
		pq.pop();
		if (id == t) return dist[id];
		if (visited[id] == 0) {
			for (long long i = 0; i < adj[id].size(); i++) {
				long long now = adj[id][i];
				//cout << "  start " << id << "  end " << adj[id][i] << " dist " << dist[now]<<" cost  "<<cost[id][i] << endl;
				if (dist[now] == -1 || dist[now] > dist[id] + cost[id][i]) {
					dist[now] = dist[id] + cost[id][i];
					pq.push(pt(now, dist[now]));
				}
			}
		}
		visited[id] = 1;
	}

	//write your code her
	return -1;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	vector<vector<long long> > cost(n, vector<long long>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	long long s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, cost, s, t);
}
