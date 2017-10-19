#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct pt {
	long long first;
	long long end;
	long long next;
	pt() : first(0), end(0), next(0) {}
	bool r;
	pt(long long _first, long long _end, long long _next, bool _r = false) {
		first = _first; end = _end; next = _next; r = _r;
	}
};

//struct suffix {
//	long long first; 
//	long long end;
//	
//
//
//};


void DFS(vector<vector<pt>> re, long long next_layer, vector<vector<long long>> & finallist, vector<vector<long long>> templist
	, long long & maxn, long long temp_size, long long & p_size) {
	bool have = false;
	for (long long i = 0; i<re[next_layer].size(); i++) {
		//cout << "first " << re[next_layer][i].first << "  end " << re[next_layer][i].end << " true " << re[next_layer][i].r << endl;
		if (re[next_layer][i].r == false && re[next_layer][i].first != p_size) {
			if (next_layer == 0) {
				//cout << "  re[next_layer][i].first " << re[next_layer][i].first << endl;
				have = true;
				maxn = 1;
				finallist = { { re[next_layer][i].first , re[next_layer][i].first } };
			}
			else if (1 + temp_size < maxn) {
				//cout << "  1re[next_layer][i].first " << re[next_layer][i].first << endl;
				have = true;
				maxn = temp_size + 1;
				templist.push_back({ re[next_layer][i].first , re[next_layer][i].first });
				finallist = templist;
			}
		}
	}
	if (!have) {
		for (long long i = 0; i<re[next_layer].size(); i++) {
			if (next_layer == 0 && re[next_layer][i].next != -1) {
				//cout << "next_layer " << next_layer << "  new [next_layer][i].first " << re[next_layer][i].first;
				//cout << "   new [next_layer][i].end  " << re[next_layer][i].end << " next "<< re[next_layer][i].next << " true " << re[next_layer][i].r << endl;
				vector<vector<long long>> templist = { { re[next_layer][i].first, re[next_layer][i].end } };
				DFS(re, re[next_layer][i].next, finallist, templist, maxn,
					re[next_layer][i].end - re[next_layer][i].first + 1, p_size);
			}

			else if (re[next_layer][i].next != -1) {
				//cout << "next_layer " << next_layer << "  new [next_layer][i].first " << re[next_layer][i].first;
				//cout << "   new [next_layer][i].end  " << re[next_layer][i].end << " next " << re[next_layer][i].next << endl;;
				vector<vector<long long>> newtemp = templist;
				newtemp.push_back({ re[next_layer][i].first, re[next_layer][i].end });
				temp_size += re[next_layer][i].end - re[next_layer][i].first + 1;
				//cout << "temp "<<endl;
				/*for (auto i : templist) {
				cout << " i " << i[0] <<" endl " << i[1] << endl;
				}*/
				DFS(re, re[next_layer][i].next, finallist, newtemp, maxn, temp_size + re[next_layer][i].end - re[next_layer][i].first + 1, p_size);
			}
		}

	}

}






string solve(string p, string q)
{
	long long p_size = p.size();
	p.append("#");
	q.append("$");
	string pq = p + q;
	vector<vector<pt>>re;
	long long size = pq.size();
	re.push_back({ pt(0, size - 1, -1) });
	for (long long i = 1; i < pq.size(); i++) {
		//cout <<endl<< "current " << pq.substr(0, i-0+1) << endl;
		long long j = i, next_layer = 0, start_point = i;
		for (long long k = 0; k < re[next_layer].size(); k++) {
			if (pq[re[next_layer][k].first] == pq[j]) {
				//cout << "equal  n " << pq.substr(0, re[next_layer][k].first+1);
				//cout << "equal j  " << pq.substr(0, j+1) << endl;
				for (long long n = re[next_layer][k].first; k >= 0 && n <= re[next_layer][k].end; n++, j++) {
					if (pq[n] != pq[j]) {
						if (start_point >= p_size) {
							re.push_back({ pt(n,re[next_layer][k].end, re[next_layer][k].next,re[next_layer][k].r), pt(j,size - 1,-1, true)
							});
							//cout << "push to layer " << re.size() - 1 << endl;
							//cout << "r separate j " << pq.substr(j, size - j) << endl;
							//cout << "r separate old " << pq.substr(n, re[next_layer][k].end - n + 1) << endl;
						}
						else {
							re.push_back({ pt(n,re[next_layer][k].end, re[next_layer][k].next,false), pt(j,size - 1,-1,false)
							});
							//cout << "push to layer " << re.size() - 1 << endl;
							//cout << "l separate old " << pq.substr(n, re[next_layer][k].end - n + 1) << endl;
							//cout << "l separate j  " << pq.substr(j, size - j) << endl;
						}
						re[next_layer][k].end = n - 1;
						re[next_layer][k].next = re.size() - 1;
						//cout << "separate old " << pq.substr(re[next_layer][k].first, n - re[next_layer][k].first) << endl;
						if (start_point >= p_size) {
							re[next_layer][k].r = true;
							//cout << "rgeng xin lao de " << pq.substr(re[next_layer][k].first, re[next_layer][k].end - re[next_layer][k].first + 1) << endl;
						}
						goto label;
					}
					if (n == re[next_layer][k].end) {
						if (start_point >= p_size) {
							re[next_layer][k].r = true;
							//cout << "r huan ceng " << pq.substr(re[next_layer][k].first, re[next_layer][k].end - re[next_layer][k].first + 1) << endl;

						}
						//cout << "l  huan ceng  " << re[next_layer][k].next << endl;

						next_layer = re[next_layer][k].next;
						k = -1;
					}
				}

			}
			else if (k == re[next_layer].size() - 1) {
				if (start_point >= p_size) {
					re[next_layer].push_back(pt(j, size - 1, -1, true));
					//cout << "r insert " << pq.substr(j,size-j) << endl;
				}

				else {
					re[next_layer].push_back(pt(j, size - 1, -1, false));
					//cout << "l insert " << pq.substr(j, size - j) << endl;
				}
				break;
			}
		}
	label:;
	}

	//long long maxn = re.size();
	//long long start = 0, end = pq.size(), next_layer = -1;
	//for (long long i = 0; i < re[0].size(); i++) {
	//	if()
	//	start = re[0][i].first, end = re[0][i].end;
	//	next_layer = re[0][i].next;
	//	for (long long j = 0; ; j<re[next_layer].next; j++) {
	//	}


	//for (long long j = 0; j < re[i].size(); j++) {
	//	if (re[i][j].r == false && re[i][j].end - re[i][j].first < end - start)
	//	{
	//		end = re[i][j].end;
	//		start = re[i][j].first;
	//	}
	//	//cout << pq.substr(re[i][j].first, re[i][j].end - re[i][j].first + 1) << endl;
	//}
	long long start = 0, end = re.size(), maxn = 90000000;
	vector<vector<long long>> templist, finallist;
	DFS(re, 0, finallist, templist, maxn, 0, p_size);

	string result = "";
	for (auto i : finallist)
		result += pq.substr(i[0], i[1] - i[0] + 1);
	return result;
}

int main(void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve(p, q);

	cout << ans << endl;

	return 0;
}

