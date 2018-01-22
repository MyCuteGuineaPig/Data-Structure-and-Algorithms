#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

typedef vector<vector<long long> > Matrix;

const long long INF = 1e9;

Matrix read_data() {
	long long vertex_count, edge_count;
	std::cin >> vertex_count >> edge_count;
	Matrix graph(vertex_count, vector<long long>(vertex_count, INF));
	for (long long i = 0; i < edge_count; ++i) {
		long long from, to, weight;
		std::cin >> from >> to >> weight;
		--from, --to;
		graph[from][to] = graph[to][from] = weight;
	}
	return graph;
}

<<<<<<< HEAD
void CombinationUtil(vector<long long>arr, vector<long long>data, long long start, long long index, long long r, vector<vector<long long>>&subset) {
	if (index == r)
	{
		subset.push_back(data);
		return;
	}

	for (long long i = start; i < arr.size() && arr.size() - i >= r - 1 - index; i++)
	{
		data[index] = arr[i];
		CombinationUtil(arr, data, i + 1, index + 1, r, subset);
	}
=======
void CombinationUtil(vector<long long>arr, vector<long long>data, long long start, long long index, long long r, vector<vector<long long>>&subset) {
	if (index == r)
	{
		subset.push_back(data);
		return;
	}

	for (long long i = start; i < arr.size() && arr.size() - i >= r - 1 - index; i++)
	{
		data[index] = arr[i];
		CombinationUtil(arr, data, i + 1, index + 1, r, subset);
	}
>>>>>>> c1f6b22468b5413173b0e8e3fa33c0e3e608d213

}

std::pair<long long, vector<long long> > optimal_path(const Matrix& graph) {
	long long best_ans = INF;
	vector<vector<long long>>C(pow(2, graph.size()), vector<long  long>(graph.size(), INF));
	vector<vector<vector<long long>>>Path(pow(2, graph.size()), vector<vector<long long>>(graph.size(), vector<long  long>()));
	for (long long i = 1, count = 0; count < graph.size(); i <<= 1, count++) {
		C[i][count] = 0;
		//cout << "i  " << i <<" count "<< count<< endl;
		Path[i][count].push_back(count);
	}
	//cout << endl;
<<<<<<< HEAD
	vector<long long>used;
	for (long long i = 0; i < graph.size(); i++) {
		used.push_back(i);
	}
	for (long long s = 2; s <= graph.size(); s++) {

		vector<long long>data(s, 0);
		vector<vector<long long>>subset;
=======
	vector<long long>used;
	for (long long i = 0; i < graph.size(); i++) {
		used.push_back(i);
	}
	for (long long s = 2; s <= graph.size(); s++) {

		vector<long long>data(s, 0);
		vector<vector<long long>>subset;
>>>>>>> c1f6b22468b5413173b0e8e3fa33c0e3e608d213
		CombinationUtil(used, data, 0, 0, s, subset);

		for (long long k = 0; k < subset.size(); k++) {
			long long index = 0;
			//cout << "subset ";
			for (auto i : subset[k]) {
				index += 1 << i;
				//cout << i + 1 << " ";
			}
			//cout << endl;
			C[index][0] = INF;
			for (long long i : subset[k]) {
				if (i != 0) {
					for (long long j : subset[k]) {
						if (j != i && graph[j][i] != INF) {
							long long indexRemoveI = index ^ (1 << i);
							/*cout << "delete i " << i + 1 << " " << " j " << j + 1;
							cout << " indexRemoveI " << indexRemoveI << endl;
							cout << "C[index]["<<i<<"] " << C[index][i];
							cout << " C[RemoveI][<<"<<j<<"] " << C[indexRemoveI][j] << " from j to i " << graph[j][i] << endl;*/
							if (C[index][i] > C[indexRemoveI][j] + graph[j][i]) {
								C[index][i] = C[indexRemoveI][j] + graph[j][i];
								//cout << "final C[{";
								//for (auto i : subset[k]) {
								//	cout << i + 1 << ",";
								//}
								//cout << "}][" << i << "]" << C[index][i] << endl;
								Path[index][i] = Path[indexRemoveI][j];
								Path[index][i].push_back(i);
							}

						}
					}

				}
			}
			//cout << endl;
		}
	}

	vector < long long > best_path;
	long long indexn = pow(2, graph.size()) - 1;
	for (long long i = 1; i < graph.size(); i++) {
		if (C[indexn][i] != INF &&  graph[i][0] != INF && best_ans > C[indexn][i] + graph[i][0]) {
			best_ans = C[indexn][i] + graph[i][0];
			best_path = Path[indexn][i];
		}
	}



	// This solution tries all the possible sequences of stops.
	// It is too slow to pass the problem.
	// Implement a more efficient algorithm here.
	/*size_t n = graph.size();
	vector<int> p(n);
	for (size_t i = 0; i < n; ++i)
	p[i] = i;

	vector<int> best_path;
	int best_ans = INF;

	do {
	int cur_sum = 0;
	bool ok = true;
	for (size_t i = 1; i < n && ok; ++i)
	if (graph[p[i - 1]][p[i]] == INF)
	ok = false;
	else
	cur_sum += graph[p[i - 1]][p[i]];
	if (graph[p.back()][p[0]] == INF)
	ok = false;
	else
	cur_sum += graph[p.back()][p[0]];

	if (!ok)
	continue;
	if (cur_sum < best_ans) {
	best_ans = cur_sum;
	best_path = p;
	}
	} while (std::next_permutation(p.begin(), p.end()));
	*/
	if (best_ans == INF)
		best_ans = -1;
	for (size_t i = 0; i < best_path.size(); ++i)
		++best_path[i];
	return std::make_pair(best_ans, best_path);
}

void print_answer(const std::pair<long long, vector<long long> >& answer) {
	std::cout << answer.first << "\n";
	if (answer.first == -1)
		return;
	const vector<long long>& path = answer.second;
	for (size_t i = 0; i < path.size(); ++i)
		std::cout << path[i] << " ";
	std::cout << "\n";
}

int main() {
	print_answer(optimal_path(read_data()));
	return 0;
}
