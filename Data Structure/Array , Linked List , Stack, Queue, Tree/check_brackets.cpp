#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {
	std::string text;
	getline(std::cin, text);

	std::stack <Bracket> opening_brackets_stack;
	for (int position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			Bracket bt = Bracket(next, position + 1);
			opening_brackets_stack.push(bt);
			// Process opening bracket, write your code here
		}

		if (next == ')' || next == ']' || next == '}') {
			if (opening_brackets_stack.size() == 0 || !opening_brackets_stack.top().Matchc(next))
			{
				cout << position + 1 << endl;
				return 0;
			}
			opening_brackets_stack.pop();
			// Process closing bracket, write your code here
		}
	}
	if (opening_brackets_stack.size() > 0) {
		while (opening_brackets_stack.size() > 1) opening_brackets_stack.pop();
		cout << opening_brackets_stack.top().position << endl;
	}
	else cout << "Success" << endl;

	// Printing answer, write your code here

	return 0;
}
