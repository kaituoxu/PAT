//string version

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
	friend bool operator<(const Node &lhs, const Node &rhs);
	string plate_number;
	string time;
	string state;
};
bool operator<(const Node &lhs, const Node &rhs)
{
	return lhs.time < rhs.time;
}

//in order to compare parking time
struct TimeNode {
	friend bool operator<(const TimeNode &lhs, const TimeNode &rhs);
	string plate_number;
	int ptime;

	TimeNode() {
		plate_number = "";
		ptime = 0;
	}
};
bool operator<(const TimeNode &lhs, const TimeNode &rhs)
{
	return lhs.plate_number < rhs.plate_number;
}
int main()
{
	int N, K;
	Node *record;
	string *query;

	//step 1
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


	//step 2
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


	//step 3
	//query
	for (int i = 0; i != K; ++i) {
		cin >> query[i];
		int cnt = 0;
		for (int j = 0; j != N; ++j) {
			if (record[j].state != "invalid" && record[j].time <= query[i]) {
				if (record[j].state == "in") {
					++cnt;
				} else {//record[j].state == "out"
					--cnt;
				}
			} else if (record[j].time > query[i]) {
				break;
			}
		}
		cout << cnt << endl;
	}

	//debug
	//string a = "05:10:33", b = "04:09:59";
	//int a2s, b2s;//a to second, b to second
	//a2s = ((a[0] - '0') * 10 + a[1] - '0') * 3600 + ((a[3] - '0') * 10 + a[4] - '0') * 60 + ((a[6] - '0') * 10 + a[7] - '0');
	//b2s = ((b[0] - '0') * 10 + b[1] - '0') * 3600 + ((b[3] - '0') * 10 + b[4] - '0') * 60 + ((b[6] - '0') * 10 + b[7] - '0');
	//cout << a2s << " " << b2s << endl;

	//step4
	//count every car's parking time
	TimeNode *parktime = new TimeNode[N];
	int maxTime = 0;
	int k = 0;
	for (int i = 0; i != N; ++i) {
		if (record[i].state == "in") {
			int j;
			for (j = i + 1; j != N; ++j) {
				if (record[i].plate_number == record[j].plate_number &&
					record[j].state == "out") {
					string a = record[i].time, b = record[j].time;
					int a2s, b2s;//string time a to second, string time b to second
					a2s = ((a[0] - '0') * 10 + a[1] - '0') * 3600 + ((a[3] - '0') * 10 + a[4] - '0') * 60 + ((a[6] - '0') * 10 + a[7] - '0');
					b2s = ((b[0] - '0') * 10 + b[1] - '0') * 3600 + ((b[3] - '0') * 10 + b[4] - '0') * 60 + ((b[6] - '0') * 10 + b[7] - '0');
					//cout << a2s << " " << b2s << " " << b2s - a2s << endl;
					int m;
					for (m = 0; m < k; ++m) {
						if (parktime[m].plate_number == record[i].plate_number) {
							parktime[m].ptime += b2s - a2s;
							if (parktime[m].ptime > maxTime) {
								maxTime = parktime[m].ptime;
							}
							break;
						}
					}
					if (m >= k) {
						parktime[k].plate_number = record[i].plate_number;
						parktime[k].ptime = b2s - a2s;
						if (parktime[k].ptime > maxTime) {
							maxTime = parktime[k].ptime;
						}
						++k;
					}
					break;
				}
			}
		}
	}
	sort(parktime, &parktime[k]);

	for (int i = 0; i != k; ++i) {
		if (parktime[i].ptime == maxTime) {
			cout << parktime[i].plate_number << " ";
		}
	}

	int h, m, s;
	h = maxTime / 3600;
	m = maxTime % 3600 / 60;
	s = maxTime % 60;
	printf("%02d:%02d:%02d\n", h, m, s);
}

//char *version

//#include <iostream>
//#include <algorithm>
//#include <cstring>
//#include <cstdio>
////#include <string>
//
//using namespace std;
//
//struct Node {
//	friend bool operator<(const Node &lhs, const Node &rhs);
//	char plate_number[8];
//	char time[9];
//	char state[8];
//	//string plate_number;
//	//string time;
//	//string state;
//};
//bool operator<(const Node &lhs, const Node &rhs)
//{
//	if (strcmp(lhs.time, rhs.time) < 0) {
//		return true;
//	} else {
//		return false;
//	}
//	//return lhs.time < rhs.time;
//}
//
////in order to compare parking time
//struct TimeNode {
//	friend bool operator<(const TimeNode &lhs, const TimeNode &rhs);
//	char plate_number[8];
//	int ptime;
//
//	TimeNode() {
//		plate_number[0] = '\0';
//		ptime = 0;
//	}
//};
//bool operator<(const TimeNode &lhs, const TimeNode &rhs)
//{
//	if (strcmp(lhs.plate_number, rhs.plate_number) < 0) {
//		return true;
//	} else {
//		return false;
//	}
//}
//int main()
//{
//	int N, K;
//	Node *record;
//	char **query;
//
//	//debug
//	//char a[8] = "abcd", b[8] = "abdd", c[8] = "abcc";
//	//cout << strcmp(a, b) << endl;
//	//cout << strcmp(a, c) << endl;
//
//
//
//	cin >> N >> K;
//	record = new Node[N + 1];
//	query = new char*[K];
//	for (int i = 0; i != K; ++i) {
//		query[i] = new char[8];
//	}
//
//	for (int i = 0; i != N; ++i) {
//		cin >> record[i].plate_number >> record[i].time >> record[i].state;
//	}
//
//	sort(record, &record[N]);
//
//	//find invalid record(ignore)
//	for (int i = 0; i != N; ++i) {
//		for (int j = i + 1; j != N; ++j) {
//			if (!strcmp(record[i].plate_number, record[j].plate_number)) {
//				if (!strcmp(record[i].state, record[j].state)) {
//					if (!strcmp(record[i].state, "in")) {
//						strcpy(record[i].state, "invalid");
//					} else if (!strcmp(record[i].state, "out")) {
//						strcpy(record[j].state, "invalid");
//					}
//
//				}
//				break;
//			}
//		}
//	}
//
//	//query
//	for (int i = 0; i != K; ++i) {
//		cin >> query[i];
//		int cnt = 0;
//		for (int j = 0; j != N; ++j) {
//			if (strcmp(record[j].state, "invalid") != 0 && strcmp(record[j].time, query[i]) <= 0) {
//				if (!strcmp(record[j].state, "in")) {
//					++cnt;
//				} else {//record[j].state == "out"
//					--cnt;
//				}
//			} else if (strcmp(record[j].time, query[i]) > 0) {
//				break;
//			}
//		}
//		cout << cnt << endl;
//	}
//
//	//debug
//	//string a = "05:10:33", b = "04:09:59";
//	//int a2s, b2s;//a to second, b to second
//	//a2s = ((a[0] - '0') * 10 + a[1] - '0') * 3600 + ((a[3] - '0') * 10 + a[4] - '0') * 60 + ((a[6] - '0') * 10 + a[7] - '0');
//	//b2s = ((b[0] - '0') * 10 + b[1] - '0') * 3600 + ((b[3] - '0') * 10 + b[4] - '0') * 60 + ((b[6] - '0') * 10 + b[7] - '0');
//	//cout << a2s << " " << b2s << endl;
//
//	//count every car's parking time
//	TimeNode *parktime = new TimeNode[N];
//	int maxTime = 0;
//	int k = 0;
//	for (int i = 0; i != N; ++i) {
//		if (!strcmp(record[i].state, "in")) {
//			int j;
//			for (j = i + 1; j != N; ++j) {
//				if (!strcmp(record[i].plate_number, record[j].plate_number) &&
//					!strcmp(record[j].state, "out")) {
//					char a[9], b[9];
//					strcpy(a, record[i].time);
//					strcpy(b, record[j].time);
//					int a2s, b2s;//string time a to second, string time b to second
//					a2s = ((a[0] - '0') * 10 + a[1] - '0') * 3600 + ((a[3] - '0') * 10 + a[4] - '0') * 60 + ((a[6] - '0') * 10 + a[7] - '0');
//					b2s = ((b[0] - '0') * 10 + b[1] - '0') * 3600 + ((b[3] - '0') * 10 + b[4] - '0') * 60 + ((b[6] - '0') * 10 + b[7] - '0');
//					//cout << a2s << " " << b2s << " " << b2s - a2s << endl;
//					int m;
//					for (m = 0; m < k; ++m) {
//						if (!strcmp(parktime[m].plate_number, record[i].plate_number)) {
//							parktime[m].ptime += b2s - a2s;
//							if (parktime[m].ptime > maxTime) {
//								maxTime = parktime[m].ptime;
//							}
//							break;
//						}
//					}
//					if (m >= k) {
//						strcpy(parktime[k].plate_number, record[i].plate_number);
//						parktime[k].ptime = b2s - a2s;
//						if (parktime[k].ptime > maxTime) {
//							maxTime = parktime[k].ptime;
//						}
//						++k;
//					}
//					break;
//				}
//			}
//		}
//	}
//	sort(parktime, &parktime[k]);
//
//	for (int i = 0; i != k; ++i) {
//		if (parktime[i].ptime == maxTime) {
//			cout << parktime[i].plate_number << " ";
//		}
//	}
//
//	int h, m, s;
//	h = maxTime / 3600;
//	m = maxTime % 3600 / 60;
//	s = maxTime % 60;
//	printf("%02d:%02d:%02d\n", h, m, s);
//}
