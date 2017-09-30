#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;
class Node;

class Node {
public:
	long long key;
	std::vector<Node *> children;


	void setChild(Node *theChild) {
		children.push_back(theChild);
	}

};


int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	long long n;
	std::cin >> n;

	std::vector<Node> nodes;
	nodes.resize(n);

	long long root_posi = -1;
	for (long long i = 0; i < n; i++) {
		long long parent_index;
		std::cin >> parent_index;
		nodes[i].key = i;
		if (parent_index >= 0)
			nodes[parent_index].setChild(&nodes[i]);
		else root_posi = i;
	}

	long long maxHeight = 0;
	queue<Node*>q;
	q.push(&nodes[root_posi]);
	while (q.size()) {
		maxHeight++;
		long long temp_size = q.size();
		for (long long i = 0; i < temp_size; i++) {
			Node* top = q.front();
			q.pop();
			for (int j = 0; j < (top->children).size(); j++)
				q.push(top->children[j]);
		}

	}

	// Replace this code with a faster implementation
	//int maxHeight = 0;
	//for (long long leaf_index = 0; leaf_index < n; leaf_index++) {
	//	long long height = 0;
	//	for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
	//		height++;
	//	maxHeight = std::max(maxHeight, height);
	//}

	std::cout << maxHeight << std::endl;
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
