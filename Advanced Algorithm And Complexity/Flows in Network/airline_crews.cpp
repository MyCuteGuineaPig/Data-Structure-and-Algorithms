
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class MaxMatching {
public:
	void Solve() {
		vector<vector<bool>> adj_matrix = ReadData();
		vector<long long> matching = FindMatching(adj_matrix);
		WriteResponse(matching);
	}

private:
	vector<vector<bool>> ReadData() {
		long long num_left, num_right;
		cin >> num_left >> num_right;
		vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
		for (long long i = 0; i < num_left; ++i)
			for (long long j = 0; j < num_right; ++j) {
				long long bit;
				cin >> bit;
				adj_matrix[i][j] = (bit == 1);
			}
		return adj_matrix;
	}

	void WriteResponse(const vector<long long>& matching) {
		for (long long i = 0; i < matching.size(); ++i) {
			if (i > 0)
				cout << " ";
			if (matching[i] == -1)
				cout << "-1";
			else
				cout << (matching[i] + 1);
		}
		cout << "\n";
	}

	bool dfs(const vector<vector<bool>> & adj_matrix, long long u, vector<bool>&seen, vector<long long>& matching) {
		for (long long j = 0; j< adj_matrix.size(); j++) {
			if (adj_matrix[j][u] && !seen[j]) {
				seen[j] = true;
				if (matching[j] < 0 || dfs(adj_matrix, matching[j], seen, matching)) {
					matching[j] = u;
					return true;
				}
			}

		}
		return false;
	}


	vector<long long> FindMatching(const vector<vector<bool>>& adj_matrix) {
		// Replace this code with an algorithm that finds the maximum
		// matching correctly in all cases.
		long long num_left = adj_matrix.size();
		long long num_right = adj_matrix[0].size();
		vector<long long> matching(num_left, -1);
		for (long long i = 0; i < num_right; i++) {
			vector<bool> seen(num_left, false);
			dfs(adj_matrix, i, seen, matching);
		}
		/*vector<bool> busy_right(num_right, false);
		for (int i = 0; i < num_left; ++i)
		for (int j = 0; j < num_right; ++j)
		if (matching[i] == -1 && !busy_right[j] && adj_matrix[i][j]) {
		matching[i] = j;
		busy_right[j] = true;
		}*/
		return matching;
	}
};

int main() {
	//std::ios_base::sync_with_stdio(false);
	MaxMatching max_matching;
	max_matching.Solve();
	return 0;
}


