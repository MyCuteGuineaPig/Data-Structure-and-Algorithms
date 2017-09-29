#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct pt {
	long long start;
	char attri; //a start, b points, c end
	long long loc;
};


vector<long long> fast_count_segments(vector<pt>n, long long size) {
	vector<long long> cnt(size, 0);
	//write your code here
	sort(n.begin(), n.end(), [](pt a, pt b) {
		if (a.start != b.start)
			return a.start < b.start;
		else
			return a.attri < b.attri; });

	for (int i = 0, count = 0; i < n.size(); i++) {
		if (n[i].attri == 'a') count++;
		else if (n[i].attri == 'b') cnt[n[i].loc] = count;
		else if (n[i].attri == 'c') count--;
	}
	return cnt;
}

//vector<long long> fast_count_segments(vector<pt>n, vector<pt> points) {
//	vector<long long> cnt(points.size(), 0);
//	//write your code here
//	sort(n.begin(), n.end(), [](pt a, pt b) {
//		if (a.start != b.start)
//			return a.start < b.start;
//		else
//			return a.end < b.end; });
//	sort(points.begin(), points.end(), [](pt a, pt b) {return a.start < b.start; });
//	for (int i = 0, j = 0; i < n.size() && j < points.size(); i++) {
//		while (j < points.size() && points[j].start < n[i].start) j++;
//		int temp = j;
//		while (j < points.size() && points[temp].start >= n[i].start && points[temp].start <= n[i].end) {
//			cnt[points[temp].end]++;
//			temp++;
//		}
//	}
//	return cnt;
//}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  long long nn, m;
  std::cin >> nn >> m;
  vector<pt> n(2*nn+m);
  size_t i = 0;
  for (; i < 2*nn;) {
	  std::cin >> n[i].start;
	  n[i].attri = 'a';
	  n[i].loc = -1;
      i++;
	  cin >> n[i].start;
	  n[i].attri = 'c';
	  n[i].loc = -1;
	  i++;
  }
  //vector<pt> points(m);
  for (int j = 0; i <2 * nn + m; i++, j++) {
    std::cin >> n[i].start;
	n[i].attri = 'b';
	n[i].loc = j;
  }
  //use fast_count_segments
  vector<long long> cnt = fast_count_segments(n, m);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
