#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>
#include <set>

using namespace std;


double cal_dist(long long x, long long y, long long x1, long long y1) {
	return (double)sqrt((double)pow(x - x1, 2) + (double)pow(y - y1, 2));
}

struct pt {
	long long id;
	double weight;
	pt(long long id_, double weight_) :
		id(id_), weight(weight_) {}
	bool operator< (const pt & p1) const {
		return p1.weight < weight;
	}
};

double clustering(vector<int> x, vector<int> y, int k) {
	if (x.size() == 0) return cal_dist(x[0], y[0], 0, 0);
	vector<double>dist(x.size(), -1);
	dist[0] = 0;
	priority_queue<pt>pq;
	pq.push(pt(0, 0));
	vector<long long> visited(x.size(), 0);
	vector<double>set;
	while (pq.size()) {
		long long id = pq.top().id;
		double weight = pq.top().weight;
		//cout << " id " << id << " weight " << weight << endl;
		pq.pop();
		if (visited[id] == 0) {
			set.push_back(weight);
			for (long long j = 0; j < x.size(); j++) {
				double dist_now = cal_dist(x[id], y[id], x[j], y[j]);
				//cout << "  j " << j << "  dist  " << dist_now << endl;
				if (j != id && (dist[j] == -1 || dist[j] >  dist_now)) {
					dist[j] = dist_now;
					pq.push(pt(j, dist[j]));
					//cout << "push  " << j << "  dist " << dist[j] << endl;
				}

			}

		}
		visited[id] = 1;
	}
	sort(set.begin(), set.end(), [](double a, double b) {return a > b; });
	//write your code here
	return set[k - 2];
}
int main() {
	size_t n;
	int k;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cin >> k;
	std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
