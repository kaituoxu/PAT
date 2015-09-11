// 1 hour

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int *pre, *in, *post;

void solve(int preL, int inL, int postL, int n);

int main()
{
	int N, x, preIdx, inIdx, postIdx;
	string op;
	stack<int> s;

	cin >> N;
	pre = new int[N];
	in = new int[N];
	post = new int[N];
	preIdx = inIdx = postIdx = 0;

	for (int i = 0; i != 2 * N; ++i) {
		cin >> op;
		if (op == "Push") {
			cin >> x;
			s.push(x);
			pre[preIdx++] = x;
		} else {
			in[inIdx++] = s.top();
			s.pop();
		}
	}

	solve(0, 0, 0, N);

	for (int i = 0; i != N - 1; ++i) {
		cout << post[i] << " ";
	}
	cout << post[N - 1] << endl;

}

void solve(int preL, int inL, int postL, int n)
{
	if (n <= 0) return;
	int len, R, root = pre[preL];

	post[postL + n - 1] = root;
	if (n == 1) return;
	for (int i = inL; i < inL + n; ++i) {
		if (in[i] == pre[preL]) {
			R = i;
			break;
		}
	}

	len = R - inL;

	solve(preL + 1, inL, postL, len);
	solve(preL + len + 1, inL + len + 1, postL + len, n - len - 1);
}
