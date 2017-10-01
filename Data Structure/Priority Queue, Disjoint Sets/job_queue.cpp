#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct thread {
	long long id;
	long long nextFreeTime;
	thread(long long id_, long long time_) : id(id_), nextFreeTime(time_)
	{}
	bool operator<(const thread &t1) const {
		if (nextFreeTime == t1.nextFreeTime)
			return id > t1.id;
		return nextFreeTime > t1.nextFreeTime;
	}

};


class JobQueue {

private:
	long long num_workers_;
	vector<long long> jobs_;
	priority_queue<thread>q1;

	vector<long long> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const {
		for (long long i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		long long m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (long long i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void AssignJobs() {
		// TODO: replace this code with a faster algorithm.
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		for (long long i = 0; i < jobs_.size(); i++) {
			if (q1.size() < num_workers_) {
				assigned_workers_[i] = q1.size();
				q1.push(thread(assigned_workers_[i], jobs_[i]));
			}
			else {
				assigned_workers_[i] = q1.top().id;
				start_times_[i] = q1.top().nextFreeTime;
				q1.pop();
				q1.push(thread(assigned_workers_[i], start_times_[i] + jobs_[i]));
			}

		}



		//vector<long long> next_free_time(num_workers_, 0);
		//for (long long i = 0; i < jobs_.size(); ++i) {
		//	long long duration = jobs_[i];
		//	long long next_worker = 0;
		//	for (long long j = 0; j < num_workers_; ++j) {
		//		if (next_free_time[j] < next_free_time[next_worker])
		//			next_worker = j;
		//	}
		//	assigned_workers_[i] = next_worker;
		//	start_times_[i] = next_free_time[next_worker];
		//	next_free_time[next_worker] += duration;
		//}
	}

public:
	void Solve() {
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};




int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}