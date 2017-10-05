
#include <iostream>
#include <string>
#include <vector>
#include <ostream>

using namespace std;
//typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

class pattern {
public:
	void read_input() {
		std::cin >> data.pattern >> data.text;

		hashtable.resize(data.text.size() - data.pattern.size() + 1);

	}

	void print_occurrences() {
		for (long long i = 0; i < output.size(); ++i)
			std::cout << output[i] << " ";
		std::cout << "\n";
	}

	pattern() {
		multiplier = 13;
		prime = 13523;
	}

	void get_occurrences() {
		read_input();
		precompute_hash();
		if (data.pattern.size() < data.text.size())
			for (long long i = 0; i <= data.text.size() - data.pattern.size(); i++)
				if (hashtable[i] == patternhash && AreEqual(i, i + data.pattern.size() - 1))
					output.push_back(i);
	}

private:
	unsigned long long hash_func(size_t begin, size_t end) {
		unsigned long long hash = 0;
		for (long long i = end; i >= begin; --i) {
			hash = (hash * multiplier + data.text[i]) % prime;
		}

		return hash;
	}

	void hash_fun() {
		patternhash = 0;
		for (long long i = data.pattern.size() - 1; i >= 0; --i) {
			patternhash = (patternhash * multiplier + data.pattern[i]) % prime;
		}

	}


	void precompute_hash() {
		if (data.text.size() < data.pattern.size()) return;
		else if (data.text.size() == data.pattern.size()) {
			if (data.text == data.pattern)
				output.push_back(0);
			return;
		}
		hash_fun();
		long long x_n = 1;
		for (long long i = 0; i < data.pattern.size(); i++)
			x_n = (x_n*multiplier) % prime;

		hashtable[data.text.size() - data.pattern.size()] = hash_func(data.text.size() - data.pattern.size(), data.text.size() - 1);
		for (long long i = data.text.size() - data.pattern.size() - 1; i >= 0; i--) {
			hashtable[i] = ((hashtable[i + 1] * multiplier) % prime + data.text[i] -
				(data.text[i + data.pattern.size()] * x_n) % prime);
			if (hashtable[i] >= 0) hashtable[i] = hashtable[i] % prime;
			else hashtable[i] = prime - (-1 * hashtable[i]) % prime;
		}
	}

	bool AreEqual(size_t begin, size_t end) {
		for (size_t i = begin, j = 0; i <= end; i++, j++)
			if (data.text[i] != data.pattern[j]) return false;
		return true;

	}


	long long patternhash;
	vector<long long>hashtable;
	vector<long long>output;
	Data data;
	long long multiplier, prime;
};


int main() {
	std::ios_base::sync_with_stdio(false);
	pattern p;
	p.get_occurrences();
	p.print_occurrences();
	return 0;
}


