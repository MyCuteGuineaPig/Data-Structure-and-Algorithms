
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_set>
using namespace std;

const long long R = 0;
const long long NotR = 1;
const long long G = 2;
const long long NotG = 3;
const long long B = 4;
const long long NotB = 5;

/*
Arguments:
* `n` - the number of vertices.
* `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
* `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
Return value:
* If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
* Otherwise, return value is an empty string.

Red = 1, G = 2,  Blue = 3
*/
class Exam {

public:
	vector<pair<long long, long long>> edges;
	string colors;
	string new_colors;
	long long numVertex;
	long long numClauses;


	vector<vector<long long>>graph;
	vector<long long>disc;
	vector<long long>low;
	vector<long long>result;
	vector<bool>stackMember;

	long long times;
	vector<unordered_set<long long>>scc;
	bool unsatisfiable;
	stack<long long>st;


	Exam(long long numVertex, long long numClauses) {
		this->numVertex = numVertex;
		this->numClauses = numClauses;
		graph.resize(numVertex * 6, vector<long long>());

		low.resize(numVertex * 6, -1);
		disc.resize(numVertex * 6, -1);
		stackMember.resize(numVertex * 6, false);
		result.resize(numVertex * 3, 0);
		times = 0;
		unsatisfiable = false;
	}


	void findscc(long long u) {
		times++;
		low[u] = times;
		disc[u] = times;
		stackMember[u] = true;
		st.push(u);
		for (long long i = 0; i < graph[u].size(); i++) {
			if (disc[graph[u][i]] == -1) {
				findscc(graph[u][i]);
				low[u] = min(low[u], low[graph[u][i]]);
			}
			else if (stackMember[graph[u][i]]) {
				low[u] = min(low[u], disc[graph[u][i]]);
			}
		}
		if (low[u] == disc[u]) {
			unordered_set<long long>sccnow;
			//cout << "scc ";
			while (st.top() != u) {
				stackMember[st.top()] = false;
				//cout << st.top()<<" ";
				sccnow.insert(st.top());
				st.pop();
			}
			stackMember[st.top()] = false;
			//cout << st.top() << " ";
			sccnow.insert(st.top());
			st.pop();
			scc.push_back(sccnow);
			//cout << endl;
			for (auto it : sccnow) {
				long long val = (it);
				if (sccnow.count(val + numVertex)>0 && sccnow.count(val - numVertex)>0)
				{
					unsatisfiable = true;
					break;
				}
			}
		}

	}


	bool assign_new_colors() {


		for (long long i = 0; i < 6 * numVertex; i++) {
			if (disc[i] == -1)
				findscc(i);
			if (unsatisfiable == true)
				return false;
		}


		for (long long j = 0; j < scc.size(); j++) {
			bool isnegative = false;
			//cout << "scc ";
			for (auto i : scc[j]) {
				//cout <<i<<" ";
				long long reminder = i%numVertex;
				long long  divid = i / (numVertex * 2);
				long long  var = divid*numVertex + reminder;
				if (result[var] != 0) {
					//cout << " var " << var  ;
					isnegative = (result[var] == -1) ? true : false;
					//cout << "  isnegative " << isnegative << endl;
					break;
				}
			}
			//cout << endl;
			for (auto i : scc[j]) {
				long long reminder = i%numVertex;
				long long  divid = i / (numVertex * 2);
				long long  var = divid*numVertex + reminder;
				long long orig = i / numVertex;
				if (result[var] == 0 && isnegative) {
					result[var] = orig & 1 ? 1 : -1;
					//cout << "assign var negative " << " result[" << var << "] = " << result[var] << endl;
				}
				else if (result[var] == 0) {
					result[var] = orig & 1 ? -1 : 1;
					//cout << "assign var positive "<< " result[" << var << "] = " << result[var] << endl;
				}

			}
		}

		for (long long i = 0; i < numVertex; i++) {
			//cout << "result i "<<i<<" " << result[i] << " " << result[numVertex + i] << " " << result[2*numVertex + i] << endl;
			if (result[i] == 1 && colors[i] != 'R') {
				new_colors += "R";
			}
			else if (result[numVertex + i] == 1 && colors[i] != 'G') {
				new_colors += "G";
			}
			else if (result[2 * numVertex + i] == 1 && colors[i] != 'B') {
				new_colors += "B";
			}
			else {
				if (colors[i] != 'R')
				{
					new_colors += "R";
				}
				else if (colors[i] != 'G')
				{
					new_colors += "G";
				}
				else
				{
					new_colors += "B";
				}
			}

		}


		return true;
	}

	void read() {
		for (long long i = 0; i < numVertex; i++) {
			if (colors[i] == 'R') { //G&B  (~G -> B) v (~B -> G )     !G&!B  (G -> ~B) v (B -> ~G )    
				graph[NotG * numVertex + i].push_back(B * numVertex + i);
				graph[NotB * numVertex + i].push_back(G * numVertex + i);

				graph[G * numVertex + i].push_back(NotB * numVertex + i);
				graph[B * numVertex + i].push_back(NotG * numVertex + i);


				result[i] = -1;
				//cout << "graph from " << NotG * numVertex + i <<" "<< B * numVertex + i << endl;
				//cout << "graph from " << NotB * numVertex + i << " " << G * numVertex + i << endl;
				//cout << "graph from " << G * numVertex + i << " " << NotB * numVertex + i << endl;
				//cout << "graph from " << B * numVertex + i << " " << NotG * numVertex + i << endl;
				//
				//cout << "result[" << i << "] = -1" << endl;
			}

			else if (colors[i] == 'G') {//R&B  (~R -> B) v (~B -> R )     !R&!B  (R -> ~B) v (B -> ~R )    
				graph[NotR * numVertex + i].push_back(B * numVertex + i);
				graph[NotB * numVertex + i].push_back(R * numVertex + i);

				graph[R * numVertex + i].push_back(NotB * numVertex + i);
				graph[B * numVertex + i].push_back(NotR * numVertex + i);


				result[numVertex + i] = -1;

				//cout << "graph from " << NotR * numVertex + i << " " << B * numVertex + i << endl;
				//cout << "graph from " << NotB * numVertex + i << " " << R * numVertex + i << endl;
				//cout << "graph from " << R * numVertex + i << " " << NotB * numVertex + i << endl;
				//cout << "graph from " << B * numVertex + i << " " << NotR * numVertex + i << endl;
				//cout << "result[" << numVertex + i << "] = -1" << endl;
			}

			else if (colors[i] == 'B') {//R&R   (~R -> G ) v (~G -> R)     !R&!G   (R -> ~G )v(G -> ~R) 
				graph[NotR * numVertex + i].push_back(G * numVertex + i);
				graph[NotG * numVertex + i].push_back(R * numVertex + i);

				graph[R * numVertex + i].push_back(NotG * numVertex + i);
				graph[G * numVertex + i].push_back(NotR * numVertex + i);
				result[2 * numVertex + i] = -1;

				//cout << "graph from " << NotR * numVertex + i << " " << G * numVertex + i << endl;
				//cout << "graph from " << NotG * numVertex + i << " " << R * numVertex + i << endl;
				//cout << "graph from " << R * numVertex + i << " " << NotG * numVertex + i << endl;
				//cout << "graph from " << G * numVertex + i << " " << NotR * numVertex + i << endl;
				//cout << "result[" << 2 * numVertex + i << "] = -1" << endl;
			}
		}


		for (int i = 0; i < numClauses; i++) {

			int u, v;
			cin >> u >> v;
			u--, v--;
			edges.push_back(make_pair(u, v));
			//(x!= R v y!=R) v (x!= G v y!=G) v (x!= B v y!=B)
			//(x= R -> y!=R ) v (y= R -> x=!R ) v (x= G -> y!=G ) v (y= G -> x=!G ) v (x= B -> y!=B ) v (y= B -> x=!B )
			if (u != v) {
				graph[R * numVertex + u].push_back(NotR * numVertex + v);
				graph[R * numVertex + v].push_back(NotR * numVertex + u);

				graph[G * numVertex + u].push_back(NotG * numVertex + v);
				graph[G * numVertex + v].push_back(NotG * numVertex + u);

				graph[B * numVertex + u].push_back(NotB * numVertex + v);
				graph[B * numVertex + v].push_back(NotB * numVertex + u);
			}
			else {
				unsatisfiable = true;
			}
			//cout << "edgegraph from " << R * numVertex + u << " " << NotR * numVertex + v << endl;
			//cout << "edgegraph from " << R * numVertex + v << " " << NotR * numVertex + u << endl;
			//cout << "edgegraph from " << G * numVertex + u << " " << NotG * numVertex + v << endl;
			//cout << "edgegraph from " << G * numVertex + v << " " << NotG * numVertex + u << endl;

			//cout << "edgegraph from " << B * numVertex + u << " " << NotB * numVertex + v << endl;
			//cout << "edgegraph from " << B * numVertex + v << " " << NotB * numVertex + u << endl;
		}
	}

};


int main() {

	long long n, m;
	cin >> n >> m;
	Exam exam(n, m);
	cin >> exam.colors;
	exam.read();


	if (!exam.assign_new_colors()) {
		cout << "Impossible";
	}
	else {
		cout << exam.new_colors << endl;
	}
}
