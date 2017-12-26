#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


/* This class implements a bit unusual scheme for storing edges of the graph,
* in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
	struct Edge {
		int from, to, capacity, flow;
	};

private:
	/* List of all - forward and backward - edges */
	vector<Edge> edges;

	/* These adjacency lists store only indices of edges in the edges list */
	vector<vector<long long> > graph;

public:
	explicit FlowGraph(long long n) : graph(n) {}

	void add_edge(int from, int to, int capacity) {
		/* Note that we first append a forward edge and then a backward edge,
		* so all forward edges are stored at even indices (starting from 0),
		* whereas backward edges are stored at odd indices in the list edges */
		Edge forward_edge = { from, to, capacity, 0 };
		Edge backward_edge = { to, from, 0, 0 };
		graph[from].push_back(edges.size());
		edges.push_back(forward_edge);
		graph[to].push_back(edges.size());
		edges.push_back(backward_edge);
	}

	long long size() const {
		return graph.size();
	}

	const vector<long long>& get_ids(long long from) const {
		return graph[from];
	}

	const Edge& get_edge(long long id) const {
		return edges[id];
	}

	void add_flow(long long id, int flow) {
		/* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
		* due to the described above scheme. On the other hand, when we have to get a "backward"
		* edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
		* should be taken.
		*
		* It turns out that id ^ 1 works for both cases. Think this through! */
		edges[id].capacity -= flow;
		edges[id ^ 1].capacity += flow;
	}
};

FlowGraph read_data() {
	int vertex_count, edge_count;
	std::cin >> vertex_count >> edge_count;
	FlowGraph graph(vertex_count);
	for (int i = 0; i < edge_count; ++i) {
		int u, v, capacity;
		std::cin >> u >> v >> capacity;
		graph.add_edge(u - 1, v - 1, capacity);
	}
	return graph;
}


bool bfs(FlowGraph &graph, int s, int t, unordered_map<long long, long long>& parent) {
	vector<bool>visited(t + 1, false);
	queue<long long>q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;
	while (q.size()) {
		long long u = q.front();
		q.pop();
		for (auto vec : graph.get_ids(u)) {
			//cout << "top " << u + 1 << " " << vec << " vec " << "  from " << u + 1 << "  to " << graph.get_edge(vec).to + 1 << " capacity " << graph.get_edge(vec).capacity << endl;
			if (visited[graph.get_edge(vec).to] == false && graph.get_edge(vec).capacity > 0) {
				//cout << "yes push" << graph.get_edge(vec).to + 1 << endl;
				visited[graph.get_edge(vec).to] = true;
				q.push(graph.get_edge(vec).to);
				parent[graph.get_edge(vec).to] = u;
			}

		}
	}
	return visited[t] == true;
}


int max_flow(FlowGraph& graph, int from, int to) {
	int flow = 0;
	/* your code goes here */
	unordered_map<long long, long long>parent;
	while (bfs(graph, from, to, parent)) {
		long long path_now = 2147483647;
		long long min_vertex = -1;
		for (long long v = to; v != from; v = parent[v]) {
			long long u = parent[v];
			for (auto vec : graph.get_ids(u)) {
				if (graph.get_edge(vec).to == v && graph.get_edge(vec).capacity>0 && path_now > graph.get_edge(vec).capacity) {
					path_now = graph.get_edge(vec).capacity;
					min_vertex = graph.get_edge(vec).to; // because some way have different path, 
														 //in order not to mix path together, add it
					//cout << "u " << u + 1 << "v " << v + 1 << " path " << graph.get_edge(vec).capacity << endl;
					break;
				}

			}
		}
		//cout << "path " << path_now << endl;
		flow += path_now;
		for (long long v = to; v != from; v = parent[v]) {
			long long u = parent[v];
			for (auto vec : graph.get_ids(u)) {
				if ((graph.get_edge(vec).to == min_vertex && graph.get_edge(vec).capacity == path_now) ||
					(graph.get_edge(vec).to != min_vertex && graph.get_edge(vec).to == v && graph.get_edge(vec).capacity>0)) {
					graph.add_flow(vec, path_now);
				}
			}
		}
		parent.clear();
	}
	return flow;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	FlowGraph graph = read_data();

	//cout << "5^1 " << (10 ^ 1) << endl;
	std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
	return 0;
}

