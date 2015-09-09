//un-compeletely solved version

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
	string plate_number;
	string time;
	string state;
	string sum;
	
	bool operator<(Node rhs)
	{
		return time < rhs.time;
	}
};

int main()
{
	int N, K;
	Node *record;
	string *query;

	cin >> N >> K;
	record = new Node[N + 1];
	query = new string[K];
	for (int i = 0; i != N; ++i) {
		cin >> record[i].plate_number >> record[i].time >> record[i].state;
	}
	//for (int i = 0; i != K; ++i) {
	//	cin >> query[i];
	//}

	sort(record, &record[N]);

	//find invalid record(ignore)
	for (int i = 0; i != N; ++i) {
		for (int j = i + 1; j != N; ++j) {
			if (record[i].plate_number == record[j].plate_number) {
				if (record[i].state == record[j].state) {
					if (record[i].state == "in") {
						record[i].state = "invalid";
					} else if (record[i].state == "out") {
						record[j].state = "invalid";
					}
				}
				break;
			}
		}
	}

	//query
	for (int i = 0; i != K; ++i) {
		cin >> query[i];
		int cnt = 0;
		for (int j = 0; j != N; ++j) {
			if (record[j].state != "invalid" && record[j].time <= query[i]) {
				if (record[j].state == "in") {
					++cnt;
				} else {//record[i].state == "out"
					--cnt;
				}
			} else if (record[j].time > query[i]) {
				break;
			}
		}
		cout << cnt << endl;
	}

}
