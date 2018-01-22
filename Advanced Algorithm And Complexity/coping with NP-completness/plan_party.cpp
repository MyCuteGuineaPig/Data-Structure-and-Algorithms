
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sys/time.h> 
#include <sys/resource.h> 
using namespace std;

struct Vertex {
	int weight;
	std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;


class FunParty {

public:
	long long vertices_count;
	Graph tree;
	long long root;
	Sum suml;

	void ReadTree() {

		std::cin >> vertices_count;
		tree.resize(vertices_count);
		suml.resize(vertices_count, -1);

		for (long long i = 0; i < vertices_count; ++i)
			std::cin >> tree[i].weight;

		if (vertices_count <= 1)
			return;

		unordered_set<long long>set;
		for (long long i = 1; i < vertices_count; ++i) {
			long long from, to, weight;
			std::cin >> from >> to;
			tree[from - 1].children.push_back(to - 1);
			tree[to - 1].children.push_back(from - 1);
			if (tree[from - 1].children.size() == 1) {
				set.insert(from - 1);
			}
			else if (tree[from - 1].children.size() > 1 && set.count(from - 1) > 0) {
				set.erase(from - 1);
			}

			if (tree[to - 1].children.size() == 1) {
				set.insert(to - 1);
			}
			else if (tree[to - 1].children.size() > 1 && set.count(to - 1) > 0) {
				set.erase(to - 1);
			}
		}
		root = (*set.begin());
		//cout << " root " << root+1 << endl;
	}



	long long dfs(long long vertex, long long parent) {
		//cout << "vertex " << vertex+1 << " parent " << parent + 1 << " suml[vertex] " << suml[vertex]
		//	<<" children.size() " << tree[vertex].children.size()  << " tree[vertex].weight  "
		//<< tree[vertex].weight<< endl;

		if (suml[vertex] != -1) {
			return suml[vertex];
		}
		else if (tree[vertex].children.size() == 0)
			suml[vertex] = tree[vertex].weight;
		else {
			long long v1 = tree[vertex].weight;
			long long v2 = 0;
			for (long long child : tree[vertex].children) {
				if (child != parent) {
					for (long long grandchild : tree[child].children)
					{
						if (grandchild != child && grandchild != vertex) {
							//cout << " Grandchild go to dfs child " << child + 1 << " grandchild " << grandchild + 1 << endl;
							long long val = dfs(grandchild, child);
							//cout << " child " << child + 1 << "grandchild " << grandchild + 1 << " dfs " << val;
							v1 += dfs(grandchild, vertex);
							//cout << "  v1 " << v1 << endl;
						}
					}

				}
			}
			for (long long child : tree[vertex].children) {
				if (child != parent) {
					//cout << " Child go to dfs " << child + 1 << endl;
					long long val = dfs(child, vertex);
					v2 += val;
					//cout << "  child " << child + 1 << " dfs " << val;
					//cout << "  v2 " << v1 << endl;
				}
			}
			suml[vertex] = max(v1, v2);
			//cout << "final vertex " << vertex+1 << " suml " << suml[vertex] << endl;
		}

		return suml[vertex];
		// This is a template function for processing a tree using depth-first search.
		// Write your code here.
		// You may need to add more parameters to this function for child processing.
	}

	long long MaxWeightIndependentTreeSubset() {
		size_t size = tree.size();
		if (size == 0)
			return 0;
		if (vertices_count == 1) {
			return  tree[0].weight;
		}
		//dfs(tree[parent].children[0], parent);
		// You must decide what to return.
		return dfs(root, -1);
	}





};


int main() {
	// This code is here to increase the stack size to avoid stack overflow
	// in depth-first search.
	const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
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
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}

	// Here begins the solution

	FunParty fun;
	fun.ReadTree();
	std::cout << fun.MaxWeightIndependentTreeSubset() << std::endl;
	return 0;
}
