#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <unordered_set>
#include <set>
using namespace std;


const double EPS = 1e-6;
const int PRECISION = 20;
const double infinity = 1000000000;
const double DIFF_EPS = 1e-9;
using namespace std;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
	Equation(const Matrix &a, const Column &b) :
		a(a),
		b(b)
	{}

	Matrix a;
	Column b;
};

struct Position {
	Position(long long column, long long  row) :
		column(column),
		row(row)
	{}

	long long  column;
	long long  row;
};


class Row_Solver { //-1 no solution, 0 solution, 1 infinity
private:
	Matrix a;
	Column b;
	long long size;
	long long step; //stands for current postion

	Matrix cst; //constraint matrix
	Column bcst; //constraint value

	bool SelectPivotElement() { // if have pivot return true; not return false
								// This algorithm selects the first free element.
								// You'll need to improve it to pass the problem.
		if (a[step][step] != 0) return true;
		for (long long i = step + 1; i < size; i++) {
			if (a[i][step] != 0) {
				std::swap(a[i], a[step]);
				std::swap(b[i], b[step]);
				return true;
			}
		}
		return false;
	}

	void PrintColumn() {
		std::cout.precision(PRECISION);
		for (long long row = 0; row < size; ++row)
			std::cout << b[row] << std::endl;
	}


	int ProcessPivotElement() {
		if (a[step][step] != 1) { //unify
			double multipiler = a[step][step];
			for (long long i = step; i < size; i++)
				a[step][i] = a[step][i] / multipiler; //so every pivot is 1
			b[step] = b[step] / multipiler;
		}
		for (long long i = 0; i < size; i++) { // loop throught row
			if (a[i][step] != 0 && i != step) // do row change so only this row step column not zero and not itself
			{
				double multiplier = -a[i][step] / a[step][step];
				for (long long j = step; j < size; j++) // loop through columns
				{
					a[i][j] += a[step][j] * multiplier;
				}
				b[i] += b[step] * multiplier;
			}
			if (b[i] != 0 && i>step) { // check if no solution no need to above line
				for (long long j = step; j < size; j++) {
					double diff = a[i][j] <0 ? -a[i][j] : a[i][j];
					if (diff>DIFF_EPS)
						break;
					else if (j == size - 1) {
						/*cout << " return no solution i "<<i<<" j " <<j<<" a[i][j] "<<a[i][j]<< " step "<<step<<"size "<< size <<" diff "<<diff<< endl;
						for (int y = 0; y < size; y++) {
						for (int z = 0; z < size; z++) {
						cout << a[y][z] << " ";
						}
						cout << b[y] << endl;
						}*/
						return -1; // 0 return no solution
					}
				}
			}
		}

		return 0;
	}

	int checkconstraint() {
		for (int i = 0; i < cst.size(); i++) {
			double tempsum = 0;
			for (int j = 0; j < cst[0].size(); j++)
				tempsum += cst[i][j] * b[j];
			double diff = tempsum - bcst[i];
			if (diff > DIFF_EPS) {
				/*cout << "check constraint failed " << endl;
				for (int y = 0; y < size; y++) {
				for (int z = 0; z < size; z++) {
				cout << a[y][z] << " ";
				}
				cout << b[y] << endl;
				}
				cout << " constraint " << endl;
				for (int y = 0; y < size; y++)
				cout << cst[i][y] << "  ";
				cout<<" "<<bcst[i]<< " tempsum " << tempsum << endl;*/
				return -1;
			}
		}
		return 0;
	}

public:

	Row_Solver(Matrix a, Column b, vector<int>subset, int m, int n) {
		size = m;
		unordered_set<int>set(subset.begin(), subset.end());
		//cout << " subset ";
		for (int i = 0; i < m + n + 1; i++) {
			if (set.count(i) > 0) {
				this->a.push_back(a[i]), this->b.push_back(b[i]);
				//cout << i<<" ";
			}
			else this->cst.push_back(a[i]), this->bcst.push_back(b[i]);
		}
		//cout << endl;
	}

	int SolveEquation() {
		for (step = 0; step < size; ++step) {
			if (SelectPivotElement()) {
				if (ProcessPivotElement() == -1) return -1;
			}
			else if (b[step] != 0) return -1; // because we don't find pivot but we have no pivot so return no solution
		}
		if (checkconstraint() == -1) return -1;
		//cout << " matrix get " << endl;
		//for (int y = 0; y < size; y++) {
		//	for (int z = 0; z < size; z++) {
		//		cout << a[y][z] << " ";
		//	}
		//	cout << b[y] << endl;
		//}
		return 0;
	}

	const Column GetB() const {
		return b;
	}

};

void CombinationUtil(vector<int>arr, vector<int>data, int start, int index
	, int r, vector<vector<int>>&subset) {
	if (index == r)
	{
		subset.push_back(data);
		return;
	}

	for (int i = start; i < arr.size() && arr.size() - i >= r - 1 - index; i++)
	{
		data[index] = arr[i];
		CombinationUtil(arr, data, i + 1, index + 1, r, subset);
	}
}



pair<int, vector<double>> solve_diet_problem(
	int n, // constraint
	int m, // restriction
	Matrix A,
	vector<double> b,
	vector<double> c) {

	vector<int>used;
	for (int i = 0; i < n + m + 1; i++) {
		used.push_back(i);
	}

	vector<int>data(m, 0);
	vector<vector<int>>subset;
	CombinationUtil(used, data, 0, 0, m, subset);
	double optimal_value = -infinity;
	int result = -1; // -1 means no solution 1 means infinity, 0 means has soltuion
	vector<double>optimal_point(m, 0);

	for (auto sub : subset) { //loop through subset;
		Row_Solver row_solver(A, b, sub, m, n);
		if (row_solver.SolveEquation() != -1) {
			Column solution = row_solver.GetB();
			result = 0;
			double temp = 0;
			//cout << "have temp solution " << solution[0] << "  " << solution[1] << "  temp  ";
			for (int i = 0; i < solution.size(); i++)
				temp += solution[i] * c[i];
			//cout << temp << endl;
			if (temp > optimal_value) {
				optimal_point = solution;
				optimal_value = temp;
			}

			if (temp >= infinity - 100000)
			{
				//cout << "infinity "<< solution[0] << "  " << solution[1] << "  temp  " << temp << endl;
				return { 1, optimal_point };
			}
		}
		//else {
		//	cout << "no solution constranit " << sub[0] << " " << sub[1] << endl << endl;
		//}
	}


	// Write your code here

	return { result, optimal_point };
}



int main() {
	int n, m;
	cin >> n >> m;
	Matrix A(n + m + 1, vector<double>(m, 0));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> A[i][j];

	for (int i = n; i < n + m; i++)
		A[i][i - n] = -1;

	for (int i = 0; i < m; i++)
		A[n + m][i] = 1;

	vector<double> b(n + m + 1, 0);
	for (int i = 0; i < n; i++)
		cin >> b[i];

	for (int i = n; i < n + m; i++)
		b[i] = 0;

	b[n + m] = infinity;

	vector<double> c(m);
	for (int i = 0; i < m; i++)
		cin >> c[i];


	pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

	switch (ans.first) {
	case -1:
		printf("No solution\n");
		break;
	case 0:
		printf("Bounded solution\n");
		for (int i = 0; i < m; i++) {
			printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
		}
		break;
	case 1:
		printf("Infinity\n");
		break;
	}
	return 0;
}
