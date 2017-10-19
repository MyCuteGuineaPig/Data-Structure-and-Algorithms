#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
//1. first compress  O(N)
//2. build suffix array using rank and radix array  O(NlogN)
//3. use suffix array minus one get BWT index	O(N)

using namespace std;



int cal_rank(char a) {
	switch (a) {
	case 'A': return 1;
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	case '$': return 0;
		//default: return 5;
	}
}

string text;

struct cpress {
	long long rank[2]; //rank 1 is the current, rank 2 is adjacent
	long long index;
	cpress(long long _index) : index(_index) {}
	cpress() {}
};

void print(vector<cpress>&arr) {
	cout << "table " << endl;
	for (long long i = 0; i < arr.size(); i++) {
		long long j = arr[i].index;
		do {
			cout << text[j] << " ";
			j++;
			if (j == text.size())
				j = 0;
		} while (j != arr[i].index);
		cout << endl;
	}
	cout << endl;

}

void buildSuffixArray(vector<cpress>&arr) {

	for (long long i = 0; i < arr.size(); i++) {

		arr[i].rank[0] = cal_rank(text[i]);
		arr[i].rank[1] = i + 1 < arr.size() ? cal_rank(text[i + 1]) : 0;

	}
	sort(arr.begin(), arr.end(), [](cpress a, cpress b) {if (a.rank[0] != b.rank[0])
		return a.rank[0] < b.rank[0]; else return a.rank[1] < b.rank[1];
	});
	bool update = false;
	for (long long k = 2; k < arr.size(); k = k * 2, update = false) {
		vector<long long>temp_index(arr.size(), 0);
		arr[0].rank[0] = 0;
		for (long long i = 1, rank = 0, prev_rank = arr[i - 1].rank[0]; i < arr.size(); i++) {
			if (arr[i].rank[0] == prev_rank && arr[i].rank[1] == arr[i - 1].rank[1]) {
				prev_rank = arr[i].rank[0];
				arr[i].rank[0] = rank;
				update = true;
			}
			else {
				prev_rank = arr[i].rank[0];
				arr[i].rank[0] = ++rank;
			}
			temp_index[arr[i].index] = i;
		}
		if (!update) break;
		for (long long i = 0; i < arr.size(); i++) {
			long long rank2 = arr[i].index + k < arr.size() ? arr[i].index + k : 0;
			arr[i].rank[1] = rank2 != 0 ? arr[temp_index[rank2]].rank[0] : 0;
		}
		sort(arr.begin(), arr.end(), [](cpress a, cpress b) {if (a.rank[0] != b.rank[0])
			return a.rank[0] < b.rank[0]; else return a.rank[1] < b.rank[1];
		});
	}
}

string BWT(const string& text) {
	string result = "";
	vector<cpress>arr;
	for (long long i = 0, pre = 0; i < text.size(); i++) {
		arr.push_back(cpress(i));
	}
	buildSuffixArray(arr);

	for (long long i = 0; i < arr.size(); i++) {
		long long before = arr[i].index > 0 ? arr[i].index - 1 : text.size() - 1;
		result += text[before];
	}

	// write your code here

	return result;
}

int main() {
	cin >> text;
	cout << BWT(text) << endl;
	return 0;
}


//
//// A utility function to get maximum value in arr[]
//int getMax(int arr[], int n)
//{
//	int mx = arr[0];
//	for (int i = 1; i < n; i++)
//		if (arr[i] > mx)
//			mx = arr[i];
//	return mx;
//}
//
//// A function to do counting sort of arr[] according to
//// the digit represented by exp.
//void countSort(int arr[], int n, int exp)
//{
//	cout << endl;
//	int output[8]; // output array
//	int i, count[10] = { 0 };
//
//	// Store count of occurrences in count[]
//	for (i = 0; i < n; i++) {
//		count[(arr[i] / exp) % 10]++;
//	}
//		
//
//	// Change count[i] so that count[i] now contains actual
//	//  position of this digit in output[]
//	for (i = 1; i < 10; i++) {
//		count[i] += count[i - 1];
//		cout << "count["<<i<<"] " << count[i] << endl;
//	}
//		
//
//	// Build the output array
//	for (i = n - 1; i >= 0; i--)
//	{
//		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
//		
//		cout << "arr["<<i<<"] "<< arr[i];
//		cout << "  count[(arr[i] / exp) % 10]-1 " << count[(arr[i] / exp) % 10] << "  ";
//		cout << "output[count[(arr[i] / exp) % 10] - 1] " << output[count[(arr[i] / exp) % 10] - 1];
//		count[(arr[i] / exp) % 10]--;
//		cout << "  new count " << count[(arr[i] / exp) % 10] << endl;
//	}
//
//	// Copy the output array to arr[], so that arr[] now
//	// contains sorted numbers according to current digit
//	for (i = 0; i < n; i++) {
//		arr[i] = output[i];
//		cout << "arroutput["<<i<<"] " << arr[i] << endl;
//	}
//		
//}
//
//// The main function to that sorts arr[] of size n using 
//// Radix Sort
//void radixsort(int arr[], int n)
//{
//	// Find the maximum number to know number of digits
//	int m = getMax(arr, n);
//
//	// Do counting sort for every digit. Note that instead
//	// of passing digit number, exp is passed. exp is 10^i
//	// where i is current digit number
//	for (int exp = 1; m / exp > 0; exp *= 10)
//		countSort(arr, n, exp);
//}
//
//// A utility function to print an array
//void print(int arr[], int n)
//{
//	for (int i = 0; i < n; i++)
//		cout << arr[i] << " ";
//}
//
//// Driver program to test above functions
//int main()
//{
//	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
//	int n = sizeof(arr) / sizeof(arr[0]);
//	for (int i = 0; i < n; i++)
//		cout << "arr[" << i << "] " << arr[i] << endl;
//	radixsort(arr, n);
//	print(arr, n);
//	return 0;
//}