#include <cmath>
#include <iostream>
#include <vector>

const double EPS = 1e-6;
const int PRECISION = 20;
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


class Row_Solver {
private:
	Matrix a;
	Column b;
	long long size;
	long long step; //stands for current postion

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


	void ProcessPivotElement() {
		if (a[step][step] != 1) {
			double multipiler = a[step][step];
			for (long long i = step; i < size; i++)
				a[step][i] = a[step][i] / multipiler; //so every pivot is 1
			b[step] = b[step] / multipiler;
		}
		for (long long i = 0; i < size; i++) { // loop throught row
			if (a[i][step] != 0 && i != step) // do row change so only one now 
			{
				double multiplier = -a[i][step] / a[step][step];
				for (long long j = step; j < size; j++) // loop through columns
				{
					a[i][j] += a[step][j] * multiplier;
				}
				b[i] += b[step] * multiplier;
			}
		}
		/*cout << endl << "matrix are " << endl;
		for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		cout << a[i][j] << " ";
		cout << b[i] << endl;
		}*/
		// Write your code here
	}

public:
	void ReadEquation() {
		std::cin >> size;
		a.resize(size, std::vector <double>(size, 0.0));
		b.resize(size, 0.0);
		step = 0;
		for (long long row = 0; row < size; ++row) {
			for (long long column = 0; column < size; ++column)
				std::cin >> a[row][column];
			std::cin >> b[row];
		}
	}


	void SolveEquation() {
		//used_columns.resize(size, false);
		//used_rows.resize(size, false);
		for (step = 0; step < size; ++step) {
			if (SelectPivotElement()) {
				ProcessPivotElement();
			}
		}
		PrintColumn();
	}

};


int main() {
	//Equation equation = ReadEquation();
	//Column solution = SolveEquation(equation);
	//PrintColumn(solution);
	Row_Solver row_solver;
	row_solver.ReadEquation();
	row_solver.SolveEquation();
	return 0;
}

//Equation ReadEquation() {
//	long long  size;
//	std::cin >> size;
//	Matrix a(size, std::vector <double>(size, 0.0));
//	Column b(size, 0.0);
//	for (long long  row = 0; row < size; ++row) {
//		for (long long  column = 0; column < size; ++column)
//			std::cin >> a[row][column];
//		std::cin >> b[row];
//	}
//	return Equation(a, b);
//}
//
//Position SelectPivotElement(
//	const Matrix &a,
//	std::vector <bool> &used_rows,
//	std::vector <bool> &used_columns) {
//	// This algorithm selects the first free element.
//	// You'll need to improve it to pass the problem.
//	Position pivot_element(0, 0);
//	while (used_rows[pivot_element.row])
//		++pivot_element.row;
//	while (used_columns[pivot_element.column])
//		++pivot_element.column;
//	return pivot_element;
//}
//
//void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
//	std::swap(a[pivot_element.column], a[pivot_element.row]);
//	std::swap(b[pivot_element.column], b[pivot_element.row]);
//	std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
//	pivot_element.row = pivot_element.column;
//}
//
//void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
//	// Write your code here
//}
//
//void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
//	used_rows[pivot_element.row] = true;
//	used_columns[pivot_element.column] = true;
//}
//
//Column SolveEquation(Equation equation) {
//	Matrix &a = equation.a;
//	Column &b = equation.b;
//	long long  size = a.size();
//
//	std::vector <bool> used_columns(size, false);
//	std::vector <bool> used_rows(size, false);
//	for (long long  step = 0; step < size; ++step) {
//		Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
//		SwapLines(a, b, used_rows, pivot_element);
//		ProcessPivotElement(a, b, pivot_element);
//		MarkPivotElementUsed(pivot_element, used_rows, used_columns);
//	}
//
//	return b;
//}
//
//void PrintColumn(const Column &column) {
//	long long  size = column.size();
//	std::cout.precision(PRECISION);
//	for (long long row = 0; row < size; ++row)
//		std::cout << column[row] << std::endl;
//}

