// un-completely correct version

#include <iostream>
#include <string>
#include <map>

#define INF 65535

using namespace std;

struct Graph {
	int **Edge;//distance from a to b
	string *city;//name of every vertex
	int *hpy;//happiness of every vertex
	int *maxhpy;//the max sum of happiness from source to i-th vertex
	int *dist;//shortest distance from source to i-th vertex
	int *nodes;//in the shortest path, the number of vertex from source to i-th vertex
	int *pre;//in the shortest path, the previous vertex of i-th vertex
	int num_path;
	int N;//the number of vertex
	int E;//the number of edge
};

void Create(Graph &G, string &source, map<string, int> &s2i);
void Dijkstra(Graph &G, string source, map<string, int> s2i);
void PrintPath(Graph G, map<string, int> s2i);

int main()
{
	Graph G;
	string source;
	map<string, int> s2i;

	Create(G, source, s2i);

	Dijkstra(G, source, s2i);

	PrintPath(G, s2i);

	// remember to free G's memory
}

void Create(Graph &G, string &source, map<string, int> &s2i)
{
	// allocate memory
	cin >> G.N >> G.E >> source;
	G.Edge = new int*[G.N];
	for (int i = 0; i != G.N; ++i) {
		G.Edge[i] = new int[G.N];
	}
	G.city = new string[G.N];
	G.hpy = new int[G.N];

	// initialize
	for (int i = 0; i != G.N; ++i) {
		for (int j = 0; j != G.N; ++j) {
			G.Edge[i][j] = INF;
		}
	}

	// input vertex
	G.city[0] = source;
	G.hpy[0] = 0;
	s2i.insert({ G.city[0], 0 });
	for (int i = 1; i != G.N; ++i) {
		cin >> G.city[i] >> G.hpy[i];
		s2i.insert({ G.city[i], i });
	}

	// input edge
	for (int i = 0; i != G.E; ++i) {
		string c1, c2;
		int dist;
		cin >> c1 >> c2 >> dist;
		G.Edge[s2i[c1]][s2i[c2]] = dist;
		G.Edge[s2i[c2]][s2i[c1]] = dist;
	}
}

void Dijkstra(Graph &G, string source, map<string, int> s2i)
{
	int *set;
	int s = s2i[source];
	// allocate memory
	set = new int[G.N];
	G.maxhpy = new int[G.N]; 
	G.dist = new int[G.N];
	G.nodes = new int[G.N];
	G.pre = new int[G.N];

	// initialize
	G.num_path = 0;
	for (int i = 0; i != G.N; ++i) {
		set[i] = 0;
		G.dist[i] = G.Edge[s][i];
		if (G.Edge[s][i] != INF) {
			G.maxhpy[i] = G.hpy[i];
			G.pre[i] = s;
			G.nodes[i] = 1;
		} else {
			G.maxhpy[i] = 0;
			G.pre[i] = -1;
			G.nodes[i] = 0;
		}
	}
	set[s] = 1;
	G.pre[s] = -1;

	for (int i = 0; i != G.N; ++i) {
		// find min
		int u = 0, min = INF;
		for (int j = 0; j != G.N; ++j) {
			if (set[j] == 0 && G.dist[j] < min) {
				u = j;
				min = G.dist[j];
			}
		}
		set[u] = 1;

		for (int j = 0; j != G.N; ++j) {
			if (G.Edge[u][j] != INF && set[j] == 0) {
				if (G.dist[u] + G.Edge[u][j] < G.dist[j]) {
					G.dist[j] = G.dist[u] + G.Edge[u][j];
					G.maxhpy[j] = G.maxhpy[u] + G.hpy[j];
					G.nodes[j] = G.nodes[u] + 1;
					G.pre[j] = u;
					G.num_path = 1;
				} else if (G.dist[u] + G.Edge[u][j] == G.dist[j]) {
					++G.num_path;
					if (G.maxhpy[u] + G.hpy[j] > G.maxhpy[j]) {
						G.maxhpy[j] = G.maxhpy[u] + G.hpy[j];
						G.nodes[j] = G.nodes[u] + 1;
						G.pre[j] = u;
					} else if (G.maxhpy[u] + G.hpy[j] == G.maxhpy[j]) {
						double avgHpy_j, avgHpy_u;
						avgHpy_j = (double)G.maxhpy[j] / G.nodes[j];
						avgHpy_u = (double)(G.maxhpy[u] + G.hpy[j]) / (G.nodes[u] + 1);
						if (avgHpy_u > avgHpy_j) {
							G.nodes[j] = G.nodes[u] + 1;
							G.pre[j] = u;
						}
					}
				}
			}
		}
	}


	delete[]set;
}

void PrintPath(Graph G, map<string, int> s2i)
{
	int d = s2i["ROM"];
	int *stack, top = -1;
	
	cout << G.num_path << " " << G.dist[d] << " " << G.maxhpy[d] << " " << G.maxhpy[d] / G.nodes[d] << endl;

	stack = new int[G.N];
	while (d != -1) {
		stack[++top] = d;
		d = G.pre[d];
	}

	while (top - 1 != -1) {
		int n = stack[top--];
		for (const auto & c : s2i) {
			if (c.second == n) {
				cout << c.first << "->";
			}
		}
	}
	int n = stack[0];
	for (const auto & c : s2i) {
		if (c.second == n) {
			cout << c.first << endl;
		}
	}

	delete[]stack;
}
