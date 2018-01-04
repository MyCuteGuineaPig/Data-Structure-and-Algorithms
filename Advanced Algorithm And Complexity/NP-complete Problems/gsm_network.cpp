#include <ios>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Edge {
	long long  from;
	long long  to;
};

struct ConvertGSMNetworkProblemToSat {
	long long  numVertices;
	vector<Edge> edges;
	long long totalconstraint;
	unordered_set<long long>visited;
	vector<string>output;

	ConvertGSMNetworkProblemToSat(long long  n, long long m) : //n is #of vertices
		numVertices(n),
		edges(m)
	{
	}

	void printEquisatisfiableSatFormula() {
		// This solution prints a simple satisfiable formula
		// and passes about half of the tests.
		// Change this function to solve the problem.


		cout << 4 * numVertices + 3 * edges.size() << " " << 3 * numVertices << endl;
		for (long long to = 0; to < numVertices; to++) {
			cout << 3 * to + 1 << " " << 3 * to + 2 << " " << 3 * to + 3 << " " << 0 << endl;
			cout << -(3 * to + 1) << " " << -(3 * to + 2) << " " << 0 << endl;
			cout << -(3 * to + 1) << " " << -(3 * to + 3) << " " << 0 << endl;
			cout << -(3 * to + 2) << " " << -(3 * to + 3) << " " << 0 << endl;
		}

		for (long long i = 0; i<edges.size(); i++) {
			long long from = edges[i].from - 1;
			long long to = edges[i].to - 1;
			//if (visited.count(from) == 0) {
			//	visited.insert(from);
			//	//cout << 3 * from + 1 << " " << 3 * from + 2 << " " << 3 * from + 3 << " " << 0 << endl;
			//	//cout << -(3 * from + 1) << " " << -(3 * from + 2) << " " << 0 << endl;
			//	//cout << -(3 * from + 1) << " " << -(3 * from + 3) << " " << 0 << endl;
			//	//cout << -(3 * from + 2) << " " << -(3 * from + 3) << " " << 0 << endl;
			//}
			//if (visited.count(to) == 0) {
			//	visited.insert(to);
			//	cout << 3 * to + 1 << " " << 3 * to + 2 << " " << 3 * to + 3 << " " << 0 << endl;
			//	cout << -(3 * to + 1) << " " << -(3 * to + 2) << " " << 0 << endl;
			//	cout << -(3 * to + 1) << " " << -(3 * to + 3) << " " << 0 << endl;
			//	cout << -(3 * to + 2) << " " << -(3 * to + 3) << " " << 0 << endl;
			//}

			cout << -(3 * from + 3) << " " << -(3 * to + 3) << " " << 0 << endl;
			cout << -(3 * from + 2) << " " << -(3 * to + 2) << " " << 0 << endl;
			cout << -(3 * from + 1) << " " << -(3 * to + 1) << " " << 0 << endl;
		}


		//cout << "3 2" << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);

	long long n, m;
	cin >> n >> m;
	ConvertGSMNetworkProblemToSat converter(n, m);
	for (long long i = 0; i < m; ++i) {
		cin >> converter.edges[i].from >> converter.edges[i].to;
	}

	converter.printEquisatisfiableSatFormula();

	return 0;
}
