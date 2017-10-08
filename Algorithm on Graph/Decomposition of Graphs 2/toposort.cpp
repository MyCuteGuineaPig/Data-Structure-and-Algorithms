#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

void explore(vector<vector<long long> > &adj, vector<long long> &used, stack<long long> & order, long long node) {
	used[node] = 1;
	for (long long i = 0; i < adj[node].size(); i++) {
		if (used[adj[node][i]] != 1)
			explore(adj, used, order, adj[node][i]);
	}
	order.push(node);
}

void dfs(vector<vector<long long> > &adj, vector<long long> &used, stack<long long> & order) {
	for (long long i = 0; i < adj.size(); i++) {
		if (used[i] != 1)
			explore(adj, used, order, i);
	}
	//write your code here

}

stack<long long> toposort(vector<vector<long long> > adj) {
	vector<long long> used(adj.size(), 0);
	stack<long long> order;
	dfs(adj, used, order);
	//write your code here
	return order;
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
	stack<long long> order = toposort(adj);
	while (order.size()) {
		std::cout << order.top() + 1 << " ";
		order.pop();
	}
}

//#include <iostream>
//#include <algorithm>
//#include <vector>
//
//using std::vector;
//using std::pair;
//
//void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
//  //write your code here
//}     
//
//vector<int> toposort(vector<vector<int> > adj) {
//  vector<int> used(adj.size(), 0);
//  vector<int> order;
//  //write your code here
//  return order;
//}
//
//int main() {
//  size_t n, m;
//  std::cin >> n >> m;
//  vector<vector<int> > adj(n, vector<int>());
//  for (size_t i = 0; i < m; i++) {
//    int x, y;
//    std::cin >> x >> y;
//    adj[x - 1].push_back(y - 1);
//  }
//  vector<int> order = toposort(adj);
//  for (size_t i = 0; i < order.size(); i++) {
//    std::cout << order[i] + 1 << " ";
//  }
//}
