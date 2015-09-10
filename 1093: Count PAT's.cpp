// PAT-A 1093
// 20:30
// uncompletely correct version

#include <iostream>

using namespace std;

int main()
{
	char in[100001];
	int cnt = 0; 
	int p, a, t;
	int i, j, k;
	i = j = k = 0;

	cin >> in;

	while (in[++i] != '\0') {
		if (in[i] == 'P') {
			p = 0;
			while (in[i] == 'P') { ++p; ++i; }
			--i;
			j = i;
			while (in[++j] != '\0') {
				if (in[j] == 'A') {
					a = 0;
					while (in[j] == 'A') { ++a; ++j; }
					--j;
					k = j;
					while (in[++k] != '\0') {
						if (in[k] == 'T') {
							t = 0;
							while (in[k] == 'T') { ++t; ++k; }
							--k;
							cnt += p * a * t;
							if (cnt >= 1000000007) {
								cnt -= 1000000007;
							}
						}
					}
				}
			}
		}
	}

	cout << cnt << endl;
}
