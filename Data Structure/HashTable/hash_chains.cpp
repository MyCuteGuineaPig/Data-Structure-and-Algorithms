#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
	string type, s;
	size_t ind;
};

class QueryProcessor {
	long long bucket_count;
	// store all strings in one vector
	//vector<string> elems;
	vector<vector<string>>hashtable;

	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(long long bucket_count) : bucket_count(bucket_count) {
		hashtable.resize(bucket_count);
	}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		if (query.type == "check") {
			// use reverse order, because we append strings to the end
			for (long long i = static_cast<long long>(hashtable[query.ind].size()) - 1; i >= 0; --i)
				std::cout << hashtable[query.ind][i] << " ";
			std::cout << "\n";
		}
		else {
			long long loc = hash_func(query.s);
			vector<string>::iterator it = std::find(hashtable[loc].begin(), hashtable[loc].end(), query.s);
			if (query.type == "find")
				writeSearchResult(it != hashtable[loc].end());
			else if (query.type == "add") {
				if (it == hashtable[loc].end())
					hashtable[loc].push_back(query.s);
			}
			else if (query.type == "del") {
				if (it != hashtable[loc].end())
					hashtable[loc].erase(it);
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	long long bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
