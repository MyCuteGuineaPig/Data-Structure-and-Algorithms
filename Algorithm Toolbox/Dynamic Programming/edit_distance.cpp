#include <iostream>
#include <string>
#include <vector>

using namespace std;


long long min(long long a, long long b, long long c)
{
	long long temp_min = a < b ? a : b;
	return temp_min < c ? temp_min : c;
}

long long edit_distance(const string &str1, const string &str2) {
	vector<vector<long long>>table(str1.length() + 1, vector<long long>(str2.length() + 1, 0));
	for (int i = 0; i < table.size(); i++) table[i][0] = i;
	for (int i = 0; i < table[0].size(); i++) table[0][i] = i;

	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			long long deletion = table[i - 1][j] + 1;
			long long insertion = table[i][j - 1] + 1;
			if (str1[i - 1] == str2[j - 1])
				table[i][j] = min(deletion, insertion, table[i - 1][j - 1]);
			else
				table[i][j] = min(deletion, insertion, table[i - 1][j - 1] + 1);
		}
	}
	//write your code here
	//for (auto i : table)
	//{
	//	for (auto j : i) cout << j << " ";
	//	cout << endl;
	//}
	return table[str1.length()][str2.length()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
