#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_map>

using namespace std;

class StockCharts {
public:
	void Solve() {
		ReadData();
		long long result = MinCharts();
		WriteResponse(result);
	}

private:
	vector<vector<long long>>stock_data;
	vector<vector<long long>>graph;
	long long num_stocks, num_points;
	unordered_map<long long, long long> matches;

	void ReadData() {
		cin >> num_stocks >> num_points;
		stock_data.resize(num_stocks, vector<long long>(num_points));
		graph.resize(num_stocks, vector<long long>(num_stocks));
		for (long long i = 0; i < num_stocks; ++i) {
			for (long long j = 0; j < num_points; ++j)
				cin >> stock_data[i][j];
			for (long long k = 0; k < i; k++)
				compare(i, k);
		}
	}

	void WriteResponse(long long result) {
		cout << result << "\n";
	}

	bool bfs(long long u, vector<bool>& seen) {
		for (long long i = 0; i < num_stocks; i++) {
			if (graph[u][i] > 0 && !seen[i]) {
				seen[i] = true;
				//cout << "true i "<<i<< "  matches " << matches.count(i) << " size " << matches.size()<< endl;
				if (matches.count(i) == 0 || bfs(matches[i], seen)) {
					matches[i] = u;
					//cout << "true i " << i<< " matches size " <<matches.size() << endl;
					return true;
				}
			}
		}
		return false;
	}

	int MinCharts() {
		// Replace this incorrect greedy algorithm with an
		// algorithm that correctly finds the minimum number
		// of charts on which we can put all the stock data
		// without intersections of graphs on one chart.


		// Vector of charts; each chart is a vector of indices of individual stocks.
		for (long long i = 0; i < num_stocks; i++) {
			vector<bool>seen(num_stocks, false);
			bfs(i, seen);
			//cout << i<< " out now " << matches.size() << endl;
		}


		//vector<vector<int>> charts;
		//for (int i = 0; i < stock_data.size(); ++i) {
		//	bool added = false;
		//	for (auto& chart : charts) {
		//		bool can_add = true;
		//		for (int index : chart)
		//			if (!compare(stock_data[i], stock_data[index]) &&
		//				!compare(stock_data[index], stock_data[i])) {
		//				can_add = false;
		//				break;
		//			}
		//		if (can_add) {
		//			chart.push_back(i);
		//			added = true;
		//			break;
		//		}
		//	}
		//	if (!added) {
		//		charts.emplace_back(vector<int>{i});
		//	}
		//}
		return num_stocks - matches.size();
	}

	void compare(long long s1, long long s2) {
		bool bigger = true;
		if (stock_data[s1][0] < stock_data[s2][0])
			bigger = false;
		if (stock_data[s1][0] == stock_data[s2][0]) return;
		for (long long i = 1; i < num_points; i++)
			if ((bigger && stock_data[s1][i] <= stock_data[s2][i]) ||
				(!bigger && stock_data[s1][i] >= stock_data[s2][i]))
				return;
		if (bigger) graph[s2][s1] = 1;
		else graph[s1][s2] = 1;
		//cout << "s1 " << s1 + 1 << " s2 " << s2 + 1 << " s2s1 " << graph[s2][s1] << " s1s2 " << graph[s1][s2] << endl;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	StockCharts stock_charts;
	stock_charts.Solve();
	return 0;
}
