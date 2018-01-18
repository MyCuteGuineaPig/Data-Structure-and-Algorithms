
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

struct Edge {
	long long from;
	long long to;
};

struct ConvertHampathToSat {
	long long numVertices;
	long long numEdges;

	vector<vector<long long>>map;

	ConvertHampathToSat(long long n) : //n is number of vertex
		numVertices(n)
	{
		numEdges = 0;
		map.resize(n, vector<long long>(n, 0));
	}

	void printEquisatisfiableSatFormula() {


		vector<string>output;


		for (long long i = 0; i < numVertices; i++) {

			string temp = "";
			for (long long j = 0; j < numVertices; j++) { //each vertex on final path must appear 
														  //n(i,j) V n(i,j+1) V n(i,j+2)
				temp += to_string(i*numVertices + j + 1) + " ";
			}
			output.push_back(temp + "0");

			temp = "";
			for (long long j = 0; j < numVertices; j++) {
				temp += to_string(j*numVertices + i + 1) + " ";
			}
			output.push_back(temp + "0");

			//no node appear in path twice,  j,k is no position 
			// ~n(i, j) V ~ n(i,k)
			for (long long j = 0; j < numVertices - 1; j++) {
				for (long long k = j + 1; k < numVertices; k++) {
					output.push_back(to_string(-(i* numVertices + j + 1)) + " " + to_string(-(i* numVertices + k + 1)) + " 0");
				}
			}


			////no two nodes occupy the same position(k)  node i, j 
			////~n(i,k) V ~n(j,k)
			for (int j = i + 1; j < numVertices; j++) {
				for (int k = 0; k < numVertices; k++) {
					//cout << -(i* numVertices + k + 1) << " " << -(j* numVertices + k + 1) << " " << 0 << endl;
					output.push_back(to_string(-(i* numVertices + k + 1)) + " " + to_string(-(j* numVertices + k + 1)) + " 0");
				}
			}
		}

		//non adjacent codes cannot be adjacent path
		//~n(i,k) V ~n(j,k+1) for i!=j and edge between i adn j 
		//int count = 0;
		//2, 1 ; 3, 2;  2, 2, 3, 3
		//3, 1 ; 2, 2;     
		for (int i = 0; i < numVertices; i++) {
			for (int j = i + 1; j < numVertices; j++) {
				if (!map[i][j]) {
					for (int k = 0; k < numVertices - 1; k++) {
						output.push_back(to_string(-(i* numVertices + k + 1)) + " " + to_string(-(j* numVertices + k + 2)) + " 0");
						output.push_back(to_string(-(j* numVertices + k + 1)) + " " + to_string(-(i* numVertices + k + 2)) + " 0");

					}

				}

			}
		}

		cout << output.size() << " " << numVertices *numVertices << endl;
		for (long long i = 0; i < output.size(); i++)
			cout << output[i] << endl;

	}
};

int main() {
	ios::sync_with_stdio(false);

	long long n, m;
	cin >> n >> m;

	ConvertHampathToSat converter(n);
	long long from, to;
	for (long long i = 0; i < m; ++i) {

		cin >> from >> to;
		from--, to--;
		converter.map[from][to] = 1;
		converter.map[to][from] = 1;
	}

	converter.printEquisatisfiableSatFormula();

	return 0;
}