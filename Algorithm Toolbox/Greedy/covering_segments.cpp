#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment {
  long long start, end;
};


vector<long long> optimal_points(vector<Segment> &segments) {
	vector<long long> points;
	int lower = -1, upper = -1;
	//write your code here
	for (size_t i = 0; i < segments.size(); ++i) {
		if (lower == -1) {
			lower = segments[i].start;
			upper = segments[i].end;
		}
		else if (segments[i].start <= upper) {
			upper = upper > segments[i].end ? segments[i].end : upper;
		}
		else {
			points.push_back(upper);
			lower = segments[i].start;
			upper = segments[i].end;
		}
		if (i == segments.size() - 1) points.push_back(upper);
	}
	return points;
}

int main() {
	long long n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  sort(segments.begin(), segments.end(), [](Segment a, Segment b) { if(a.start != b.start) return a.start < b.start; 
  else return a.end < b.end; });
  vector<long long> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
