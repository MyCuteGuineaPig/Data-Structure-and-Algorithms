#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
	vector<long long> data_;
	vector< pair<long long, long long>> swaps_;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (long long i = 0; i < swaps_.size(); ++i) {
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}

	}

	void ReadData() {
		long long n;
		cin >> n;
		data_.resize(n);
		for (long long i = 0; i < n; ++i)
			cin >> data_[i];
	}

	void GenerateSwaps() {
		swaps_.clear();
		// The following naive implementation just sorts 
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap, 
		// but in the worst case gives a quadratic number of swaps.
		//
		// TODO: replace by a more efficient implementation
		//for (int i = 0; i < data_.size(); ++i)
		//	for (int j = i + 1; j < data_.size(); ++j) {
		//		if (data_[i] > data_[j]) {
		//			swap(data_[i], data_[j]);
		//			swaps_.push_back(make_pair(i, j));
		//		}
		//	}
		for (long long i = data_.size() / 2; i >= 0; i--) {
			siftdown(i);
		}
	}

	void siftdown(long long j) {
		long long index = j;
		if (2 * j + 1 < data_.size() && data_[2 * j + 1] < data_[index])
			index = 2 * j + 1;
		if (2 * j + 2 < data_.size() && data_[2 * j + 2] < data_[index])
			index = 2 * j + 2;
		if (index == j) return;
		else {
			swap(data_[index], data_[j]);
			swaps_.push_back(make_pair(j, index));
			siftdown(index);
		}
	}

public:
	void Solve() {
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
