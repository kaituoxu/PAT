#include <iostream>
#include <queue>

using namespace std;

struct node {
	int level;
	int parent;
};
typedef node *tree;

int main()
{

	int N, M;
	int pid, K, cid; //parent id, K, child id
	tree T;
	int *gen; // nodes of every generation
	queue<int> Q;
	int f;//front of queue

	cin >> N >> M;

	T = new node[N + 1];
	gen = new int[N + 1];

	//step 1. process input
	for (int i = 0; i != M; ++i) {
		cin >> pid >> K;
		for (int j = 0; j != K; ++j) {
			cin >> cid;
			T[cid].parent = pid;
			T[cid].level = 0; //initialize
		}
	}

	//step 2. calculate every node's level
	T[1].level = 1;//root
	Q.push(1);//root
	while (!Q.empty()) {
		f = Q.front(); Q.pop();
		for (int i = 1; i != N + 1; ++i) {
			if (T[i].parent == f) {
				T[i].level = T[f].level + 1;
				Q.push(i);
			}
		}
	}

	//debug
	//for (int i = 1; i != N + 1; ++i) {
	//	cout << i << " " << T[i].parent << " " << T[i].level << endl;
	//}


	//step 3. calculate the number of nodes of each level

	//initialize gen[]
	for (int i = 1; i != N + 1; ++i) {
		gen[i] = 0;
	}

	int maxLevel = 1;
	for (int i = 1; i != N + 1; ++i) {
		++gen[T[i].level];
		if (T[i].level > maxLevel) {
			maxLevel = T[i].level;
		}
	}

	//debug
	//for (int i = 1; i <= maxLevel; ++i) {
	//	cout << gen[i] << " ";
	//}
	
	//step 4. find the largest population number and the level of the corresponding generation
	int maxNodes = 0;
	int level = 0;
	for (int i = 1; i <= maxLevel; ++i) {
		if (gen[i] > maxNodes) {
			maxNodes = gen[i];
			level = i;
		}
	}

	cout << maxNodes << " " << level << endl;

	delete[]T;
	delete[]gen;
}
