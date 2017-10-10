#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

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

double minimum_distance(vector<long long> x, vector<long long> y) {
	if (x.size() == 0) return cal_dist(x[0], y[0], 0, 0);
	double result = 0.;
	vector<double>dist(x.size(), -1);
	dist[0] = 0;
	priority_queue<pt>pq;
	pq.push(pt(0, 0));
	vector<long long> visited(x.size(), 0);
	while (pq.size()) {
		long long id = pq.top().id;
		double weight = pq.top().weight;
		//cout << " id " << id << " weight " << weight << endl;
		pq.pop();
		if (visited[id] == 0) {
			result += weight;
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

	//write your code here
	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<long long> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}