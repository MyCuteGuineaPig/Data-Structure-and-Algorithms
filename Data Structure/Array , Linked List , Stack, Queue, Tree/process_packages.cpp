#include <iostream>
#include <queue>
#include <vector>
#include <deque>

using namespace std;
struct Request {
	Request(long long arrival_time, long long process_time) :
		arrival_time(arrival_time),
		process_time(process_time)
	{}

	long long arrival_time;
	long long process_time;
};

struct Response {
	Response(bool dropped, long long start_time) :
		dropped(dropped),
		start_time(start_time)
	{}

	bool dropped;
	long long start_time;
};

class Buffer {
public:
	Buffer(long long size) :
		size_(size),
		finish_time_()
	{
	}

	Response Process(const Request &request) {
		while (finish_time_.size() > 0 && request.arrival_time >= finish_time_.front()) {
			//size++;
			finish_time_.pop_front();
		}
		if (finish_time_.size() == 0) {
			finish_time_.push_back(request.process_time + request.arrival_time);
			return Response(false, request.arrival_time);
		}
		else if (finish_time_.size() >= size_) {
			return Response(true, request.process_time);
		}
		else {
			long long processt = finish_time_.back();
			finish_time_.push_back(processt + request.process_time);
			return Response(false, processt);
		}


		// write your code here
	}
private:
	long long size_;
	std::deque <long long> finish_time_;
};

std::vector <Request> ReadRequests() {
	std::vector <Request> requests;
	long long count;
	std::cin >> count;
	for (long long i = 0; i < count; ++i) {
		long long arrival_time, process_time;
		std::cin >> arrival_time >> process_time;
		requests.push_back(Request(arrival_time, process_time));
	}
	return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
	std::vector <Response> responses;
	for (long long i = 0; i < requests.size(); ++i)
		responses.push_back(buffer->Process(requests[i]));
	return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
	for (long long i = 0; i < responses.size(); ++i)
		std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
	long long size;
	std::cin >> size;
	std::vector <Request> requests = ReadRequests();

	Buffer buffer(size);
	std::vector <Response> responses = ProcessRequests(requests, &buffer);

	PrintResponses(responses);
	return 0;
}
