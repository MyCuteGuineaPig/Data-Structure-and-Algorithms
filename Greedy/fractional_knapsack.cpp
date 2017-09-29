#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

struct loot {
	double values;
	int weights;
};


double get_optimal_value(int capacity, vector <loot> loots) {
	double value = 0.0;
	for (int i = 0; i < loots.size(); i++)
		loots[i].values = (double)(loots[i].values / loots[i].weights);
	sort(loots.begin(), loots.end(), [](loot const &a, loot const & b) {
		return a.values > b.values;
	});
	int i = 0;
	while (capacity > 0) {
		if (capacity <= loots[i].weights) {
			value += capacity * loots[i].values;
			capacity = 0;
		}
		else {
			value += loots[i].values * loots[i].weights;
			capacity -= loots[i].weights;
		}
		i++;
	}
	// write your code here

	return value;
}
int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<loot>loots(n);
  for (int i = 0; i < n; i++) {
    std::cin >> loots[i].values >> loots[i].weights;
  }

  double optimal_value = get_optimal_value(capacity, loots);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
