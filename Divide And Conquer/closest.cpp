#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>


using namespace std;

struct point {
	long long x, y;
};

long double dist(point a, point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

long double bruteForce(const vector<point>&n, long long left, long long right)
{
	long double min_ = -1;
	for (int i = left; i < right; ++i)
		for (int j = i + 1; j <= right; ++j)
			if (min_ < 0) min_ = dist(n[i], n[j]);
			else min_ = min(min_, dist(n[i], n[j]));
			return min_;
}

long double minimal_twoside(const vector<point>&n, long double temp_min) {
	for (int i = 0; i<n.size(); i++)
		for (int j = i + 1; j <n.size() && abs(n[j].y - n[i].y) < temp_min; j++)
			temp_min = min(temp_min, dist(n[j], n[i]));
	return temp_min;
}

long double minimal_distance(const vector<point>&nx, vector<point>ny, long long left, long long right) {
	if (right - left <= 2) {
		return bruteForce(nx, left, right);
	}
	long long mid = left + (right - left) / 2;
	vector<point>nyl(mid + 1);
	partial_sort_copy(nx.begin(), nx.begin() + mid + 1, nyl.begin(), nyl.end(), [](point a, point b) {if (a.y != b.y) return a.y < b.y; else return a.x < b.x; });
	long double lv = minimal_distance(nx, nyl, left, mid);
	if (lv == 0) return 0;
	vector<point>nyr(right - mid);
	partial_sort_copy(nx.begin() + mid + 1, nx.end(), nyr.begin(), nyr.end(), [](point a, point b) {if (a.y != b.y) return a.y < b.y; else return a.x < b.x; });
	long double rv = minimal_distance(nx, nyr, mid + 1, right);
	if (rv == 0) return 0;
	long double temp_min = min(lv, rv);
	vector<point>strip;
	for (int i = 0; i < ny.size(); i++)
		if (abs(ny[i].x - nx[mid].x) < temp_min)
			strip.push_back(ny[i]);
	long double mid_min = minimal_twoside(strip, temp_min);


	//write your code here
	return mid_min;
}

int main() {
  size_t nn;
  std::cin >> nn;
  //vector<int> x(n);
  //vector<int> y(n);
  vector<point>nx(nn);
  vector<point>ny(nn);
  int i1, i2;

  for (size_t i = 0; i < nn; i++) {
	  cin >> i1 >> i2;
	  nx[i].x = i1;
	  nx[i].y = i2;
	  ny[i].x = i1;
	  ny[i].y = i2;
  }
  sort(nx.begin(), nx.end(), [](point a, point b) {if (a.x != b.x) return a.x < b.x; else return a.y < b.y; });
  sort(ny.begin(), ny.end(), [](point a, point b) {if (a.y != b.y) return a.y < b.y; else return a.x < b.x; });
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(nx, ny,0,nx.size()-1) << "\n";
}
