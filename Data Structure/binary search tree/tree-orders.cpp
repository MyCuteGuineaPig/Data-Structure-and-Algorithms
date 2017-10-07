#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using namespace std;

class TreeOrders {
	long long  n;
	vector <long long > key;
	vector <long long > left;
	vector <long long > right;

public:
	void read() {
		cin >> n;
		key.resize(n);
		left.resize(n);
		right.resize(n);
		for (long long i = 0; i < n; i++) {
			cin >> key[i] >> left[i] >> right[i];
		}
	}


	vector <long long > in_order() {
		vector<long long > result;
		inorder(0, result);
		return result;
	}

	void inorder(long long t, vector<long long >& result) {
		if (left[t] != -1) {
			inorder(left[t], result);
		}
		result.push_back(key[t]);
		if (right[t] != -1)
			inorder(right[t], result);
	}

	vector <long long> pre_order() {
		vector<long long > result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		preorder(0, result);
		return result;
	}

	void preorder(long long t, vector<long long >& result) {
		result.push_back(key[t]);
		if (left[t] != -1) {
			preorder(left[t], result);
		}
		if (right[t] != -1)
			preorder(right[t], result);
	}


	vector <long long > post_order() {
		vector<long long > result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		postorder(0, result);
		return result;
	}

	void postorder(long long t, vector<long long >& result) {
		if (left[t] != -1) {
			postorder(left[t], result);
		}
		if (right[t] != -1)
			postorder(right[t], result);
		result.push_back(key[t]);
	}

};

void print(vector <long long> a) {
	for (size_t i = 0; i < a.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

