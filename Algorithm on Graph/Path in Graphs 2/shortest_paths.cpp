#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cstdint>
#include <stack>
using namespace std;


struct pt {
	long long num;
	bool infinit;
	pt() : num(0), infinit(true) {}
};


void explore(vector<vector<long long> > &adj, vector<long long>&visited, vector<long long> &reachable, long long node)
{
	visited[node] = 1;
	reachable[node] = 1;
	for (long long i = 0; i < adj[node].size(); i++)
		if (visited[adj[node][i]] == 0)
			explore(adj, visited, reachable, adj[node][i]);
}

//void shortest_paths(vector<vector<long long> > &adj, vector<vector<long long> > &cost, 
//	long long s, vector<long long> &distance, vector<long long> &reachable, vector<long long> &shortest) {
//	
//	//stack<long long>order;
//	//DFS(adj, order);
//	//DFS_SSC(adj_rev, order, s, reachable);
//	vector<long long>visited(adj.size(), 0);
//	explore(adj, visited, reachable, s);
//	distance[s] = 0;
//
//	vector<long long>parent(adj.size(), -1);
//	//for (long long i = 0; i < reachable.size(); i++) {
//	//	cout << "reachable "<< reachable[i] << endl;
//	//}
//	for (long long count = 1; count <= 3*adj.size(); count++) {
//		for (long long i = 0; i < adj.size(); i++) {
//			for (long long j = 0; j < adj[i].size(); j++) {
//				long long end = adj[i][j];
//				long long new_dist = distance[i] + cost[i][j];
//				if ( reachable[i] && distance[i] < numeric_limits<long long>::max()
//					&& distance[end] > new_dist)
//				{
//					if ((distance[i] >= 0 && cost[i][j] >= 0 && new_dist >= distance[i] && new_dist >= cost[i][j]) ||
//						(distance[i] <= 0 && cost[i][j] <= 0 && new_dist <= distance[i] && new_dist <= cost[i][j]) ||
//						(distance[i]>0 && cost[i][j] < 0) || (distance[i] < 0 && cost[i][j] > 0))
//					{
//					
//						parent[end] = i;
//						distance[end] = new_dist;
//						if (count >= adj.size()) {
//							//cout << "find loop " << endl;
//							shortest[end] = 0;
//							//long long start = end;
//							//do {
//							//	shortest[end] = 0;
//							//	end = parent[end];
//							//} while (end != start);
//						}
//					}
//
//				}
//			}
//		}
//	}
//	//write your code here
//}

bool check_overflow(long long A, long long B) {
	long long max = std::numeric_limits<long long>::max();
	long long min = std::numeric_limits<long long>::min();

	if (A < 0 && B < 0)
		return B < min - A;
	if (A > 0 && B > 0)
		return B > max - A;

	return false;
}

void shortest_paths(vector<vector<long long> > &adj, vector<vector<long long> > &cost,
	long long s, vector<pt> &distance, vector<long long> &reachable, vector<long long> &shortest) {

	//stack<long long>order;
	//DFS(adj, order);
	//DFS_SSC(adj_rev, order, s, reachable);
	vector<long long>visited(adj.size(), 0);
	explore(adj, visited, reachable, s);
	distance[s].num = 0;
	distance[s].infinit = false;
	vector<long long>parent(adj.size(), -1);
	//for (long long i = 0; i < reachable.size(); i++) {
	//	cout << "reachable "<< reachable[i] << endl;
	//}
	bool update = false;
	for (long long count = 1; count <= 2 * adj.size(); count++, update = false) {
		for (long long i = 0; i < adj.size(); i++) {
			for (long long j = 0; j < adj[i].size(); j++) {
				long long end = adj[i][j];
				long long new_dist = distance[i].num + cost[i][j];
				if (shortest[i] == 0)
					shortest[end] = 0;
				if (reachable[i] && reachable[end] && distance[i].infinit == false && distance[i].num < std::numeric_limits<long long>::max() &&
					cost[i][j]<std::numeric_limits<long long>::max() && cost[i][j]>std::numeric_limits<long long>::min() &&
					distance[i].num > std::numeric_limits<long long>::min() && (distance[end].infinit ||
						distance[end].num > new_dist))
				{

					if (!check_overflow(distance[i].num, cost[i][j]))
					{
						parent[end] = i;
						distance[end].num = new_dist;
						distance[end].infinit = false;
						update = true;
						if (count >= adj.size()) {
							//cout << "find loop " << endl;
							//shortest[end] = 0;
							long long start = end;
							do {
								shortest[end] = 0;
								end = parent[end];
							} while (end != start && shortest[end]!=0);
						}
					}
				}
			}
		}
		if (!update) break;
	}
	//write your code here
}


int main() {
	long long n, m, s;
	std::cin >> n >> m;
	vector<vector<long long> > adj(n, vector<long long>());
	vector<vector<long long> > cost(n, vector<long long>());
	for (long long i = 0; i < m; i++) {
		long long x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cin >> s;
	s--;
	//vector<long long> distance(n, std::numeric_limits<long long>::max());
	vector<pt>distance(n);
	vector<long long> reachable(n, 0);
	vector<long long> shortest(n, 1);
	shortest_paths(adj, cost, s, distance, reachable, shortest);
	for (long long i = 0; i < n; i++) {
		if (!reachable[i]) {
			std::cout << "*\n";
		}
		else if (!shortest[i]) {
			std::cout << "-\n";
		}
		else {
			std::cout << distance[i].num << "\n";
		}
	}
}
