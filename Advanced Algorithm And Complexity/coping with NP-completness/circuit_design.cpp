
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <bits/stdc++.h>
#include <sys/time.h> 
#include <sys/resource.h> 
using namespace std;

struct Clause {
	long long firstVar;
	long long secondVar;
};

struct TwoSatisfiability {
	long long numVars;
	vector<Clause> clauses;
	vector<vector<long long>>graph;
	vector<long long>low;
	vector<long long>disc;
	vector<bool>stackMember;
	vector<long long>result;

	long long times;

	stack<long long >st;
	vector<unordered_set<long long>>topo;
	bool unsatisfiable;

	vector<unordered_set<long long>> scc;

	TwoSatisfiability(long long n, long long m) :
		numVars(n),
		clauses(m)
	{
		graph.resize(numVars * 2, vector<long long>());// 0.....numVars - 1 means positive, numVars to 2*numVars-1 means falsify
		low.resize(numVars * 2, -1);
		disc.resize(numVars * 2, -1);
		stackMember.resize(numVars * 2, false);
		result.resize(numVars, 0);
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
			while (st.top() != u) {
				stackMember[st.top()] = false;
				sccnow.insert(st.top());
				st.pop();
			}
			stackMember[st.top()] = false;
			sccnow.insert(st.top());
			st.pop();
			scc.push_back(sccnow);

			for (auto it : sccnow) {
				long long val = (it);
				if (val < numVars && sccnow.count(val + numVars)>0)
				{
					unsatisfiable = true;
					break;
				}
			}
		}

	}


	bool isSatisfiable() {


		for (long long i = 0; i < 2 * numVars; i++) {
			if (disc[i] == -1)
				findscc(i);
			if (unsatisfiable == true)
				return false;
		}


		for (long long j = 0; j < scc.size(); j++) {
			bool isnegative = false;
			for (auto i : scc[j]) {
				long long var = i >= numVars ? i - numVars : i;
				if (result[var] != 0) {
					isnegative = result[var]> 0 ? true : false;
					break;
				}
			}

			for (auto i : scc[j]) {
				long long var = i >= numVars ? i - numVars : i;
				if (result[var] == 0 && isnegative) {
					result[var] = i >= numVars ? var + 1 : -(var + 1);
				}
				else if (result[var] == 0) {
					result[var] = i >= numVars ? -(var + 1) : var + 1;
				}

			}
		}

		return true;
		// This solution tries all possible 2^n variable assignments.
		// It is too slow to pass the problem.
		// Implement a more efficient algorithm here.

		/*for (int mask = 0; mask < (1 << numVars); ++mask) {
		for (int i = 0; i < numVars; ++i) {
		result[i] = (mask >> i) & 1;
		}

		bool formulaIsSatisfied = true;

		for (const Clause& clause : clauses) {
		bool clauseIsSatisfied = false;
		if (result[abs(clause.firstVar) - 1] == (clause.firstVar < 0)) {
		clauseIsSatisfied = true;
		}
		if (result[abs(clause.secondVar) - 1] == (clause.secondVar < 0)) {
		clauseIsSatisfied = true;
		}
		if (!clauseIsSatisfied) {
		formulaIsSatisfied = false;
		break;
		}
		}

		if (formulaIsSatisfied) {
		return true;
		}
		}
		return false;*/
	}
};

int main() {
	//ios::sync_with_stdio(false);
	const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}


	long long n, m;
	cin >> n >> m;
	TwoSatisfiability twoSat(n, m);
	for (long long i = 0; i < m; ++i) {
		long long a, b;
		cin >> a >> b;
		twoSat.clauses[i].firstVar = a;
		twoSat.clauses[i].secondVar = b;
		if (a >= 0 && b >= 0) {
			twoSat.graph[a + n - 1].push_back(b - 1);
			twoSat.graph[b + n - 1].push_back(a - 1);

		}

		else if (a < 0 && b >= 0) {
			twoSat.graph[-a - 1].push_back(b - 1);
			twoSat.graph[b + n - 1].push_back(n - a - 1);
		}
		else if (a >= 0 && b < 0) {
			twoSat.graph[a + n - 1].push_back(n - b - 1);
			twoSat.graph[-b - 1].push_back(a - 1);

		}
		else if (a < 0 && b < 0) {
			twoSat.graph[-a - 1].push_back(n - b - 1);
			twoSat.graph[-b - 1].push_back(n - a - 1);
		}

	}
	twoSat.result.resize(n, 0);

	if (twoSat.isSatisfiable()) {
		cout << "SATISFIABLE" << endl;
		for (int i = 1; i <= n; ++i) {
			cout << twoSat.result[i - 1];

			if (i < n) {
				cout << " ";
			}
			else {
				cout << endl;
			}
		}
	}
	else {
		cout << "UNSATISFIABLE" << endl;
	}

	return 0;
}
