#include <iostream>

#define INF 65535
using namespace std;

const int MAXSIZE = 500;
struct MGraph {
	int **Edge;
	int *teams;// teams[] record the number of rescue teams in the i-th city
	int *dist;// dist[] record the shortest distance from source to i-th vertex(city)
	int *sum;// sum[] record the biggest sum of rescue teams from source to i-th city
	int *count;// record the number of shortest pathes from source to i-th vertex
	int *pre;// record the previous vertex of i-th vertex in the shortest path, its function like path[]
	int N;//  
	int M;//number of edges
	//if no edge between a and b, Edge[a][b] = INF
};

void CreateGraph(MGraph &G, int &source, int &dest)
{
	int a, b, w;

	cin >> G.N >> G.M;
	cin >> source >> dest;

	G.Edge = new int*[G.N];
	G.teams = new int[G.N];
	G.dist = new int[G.N];
	G.sum = new int[G.N];
	G.count = new int[G.N];
	G.pre = new int[G.N];
	//initialize the number of teams of each city
	for (int i = 0; i != G.N; ++i) {
		G.Edge[i] = new int[G.N];

		cin >> G.teams[i];

		for (int j = 0; j != G.N; ++j) {
			G.Edge[i][j] = INF;
		}
	}
	//initialize edge and weight
	for (int i = 0; i != G.M; ++i) {
		cin >> a >> b >> w;
		G.Edge[a][b] = w;
		G.Edge[b][a] = w;
	}
}
//Dijkstra Alg
//path[], dist[], set[]
//return the number of same shortest pathes
void Dijkstra(MGraph G, int s)
{
	int *set = new int[G.N];

	//initialize
	G.count[s] = 1;
	for (int i = 0; i != G.N; ++i) {
		set[i] = 0;
		G.dist[i] = G.Edge[s][i];
		if (G.Edge[s][i] != INF) {
			G.pre[i] = s;
			G.count[i] = G.count[s];
			G.sum[i] = G.teams[s] + G.teams[i];
		} else {
			G.pre[i] = -1;
			//ps this statement: if i == 0, G.count[0] = 0, then G.count[s] = 1 is invalid
			if (i != 0) G.count[i] = 0;
			G.sum[i] = G.teams[i];
		}
	}
	set[s] = 1;
	G.count[s] = 1;
	G.pre[s] = -1;

	//key operation
	for (int i = 0; i != G.N; ++i) {
		//find min and add to set[]
		int min = INF, v = 0;
		for (int j = 0; j != G.N; ++j) {
			if (set[j] == 0 && G.dist[j] < min) {
				min = G.dist[j];
				v = j;
			}
		}
		set[v] = 1;

		//refresh dist[]
		for (int j = 0; j != G.N; ++j) {
			if (G.Edge[v][j] != INF && set[j] == 0) {
				if (G.dist[v] + G.Edge[v][j] < G.dist[j]) {
					G.dist[j] = G.dist[v] + G.Edge[v][j];
					G.sum[j] = G.sum[v] + G.teams[j];

					G.pre[j] = v;
					G.count[j] = G.count[G.pre[j]];					
				} else if (G.dist[v] + G.Edge[v][j] == G.dist[j]) {
					if (G.sum[v] + G.teams[j] > G.sum[j]) {
						G.sum[j] = G.sum[v] + G.teams[j];
					}

					G.pre[j] = v;
					G.count[j] += G.count[G.pre[j]];
				}
			}
		}
	}

	delete[]set;
}

int main()
{
	MGraph G;
	
	int source, dest;

	CreateGraph(G, source, dest);
	
	Dijkstra(G, source);
	cout << G.count[dest] << " " << G.sum[dest] << endl;
	//PrintPath(path, dest);

	//remember to free G's memory
}


//test file
//6 7 0 5
//1 2 1 1 2 1
//0 1 1
//0 2 2
//1 2 1
//2 3 1
//2 4 1
//3 5 1
//4 5 1
