#include <iostream>
#include <stack>

using namespace std;

struct node {
	int x;
	int y;
	int z;
	node(int a, int b, int c) : x(a), y(b), z(c) {}
};

int M, N, L, T;
int ***data;
bool ***visited;

int DFS(int x, int y, int z);

int main()
{
	int sum = 0;

	cin >> M >> N >> L >> T;

	// allocate memory
	// PS M N L
	data = new int**[M];
	visited = new bool**[M];
	for (int i = 0; i != M; ++i) {
		data[i] = new int*[N];
		visited[i] = new bool*[N];
		for (int j = 0; j != N; ++j) {
			data[i][j] = new int[L];
			visited[i][j] = new bool[L];
		}
	}

	// input and initialize
	// PS M N L
	for (int z = 0; z != L; ++z) {
		for (int x = 0; x != M; ++x) {
			for (int y = 0; y != N; ++y) {
				cin >> data[x][y][z];
				visited[x][y][z] = false;
			}
		}
	}

	// DFS
	for (int z = 0; z != L; ++z) {
		for (int x = 0; x != M; ++x) {
			for (int y = 0; y != N; ++y) {
				if (data[x][y][z]) {//key
					int cnt;
					cnt = DFS(x, y, z);
					sum += (cnt >= T ? cnt : 0);
				}
			}
		}
	}

	cout << sum << endl;
}

int DFS(int x, int y, int z)
{
	if (visited[x][y][z]) return 0;
	int neig[6][3];
	int cnt = 0;
	stack<node> s;

	visited[x][y][z] = true;
	s.push(node(x, y, z));
	while (!s.empty()) {
		node top = s.top(); s.pop();
		++cnt;
		neig[0][0] = top.x + 1; neig[0][1] = top.y; neig[0][2] = top.z;
		neig[1][0] = top.x - 1; neig[1][1] = top.y; neig[1][2] = top.z;
		neig[2][0] = top.x; neig[2][1] = top.y + 1; neig[2][2] = top.z;
		neig[3][0] = top.x; neig[3][1] = top.y - 1; neig[3][2] = top.z;
		neig[4][0] = top.x; neig[4][1] = top.y; neig[4][2] = top.z + 1;
		neig[5][0] = top.x; neig[5][1] = top.y; neig[5][2] = top.z - 1;
		for (int i = 0; i < 6; ++i) {
			int a = neig[i][0];
			int b = neig[i][1];
			int c = neig[i][2];
			if (a < 0 || b < 0 || c < 0 || a >= M || b >= N || c >= L) continue;
			if (!visited[a][b][c] && data[a][b][c]) {
				s.push(node(a, b, c));
				visited[a][b][c] = true;
			}
		}

	}

	return cnt;
}
