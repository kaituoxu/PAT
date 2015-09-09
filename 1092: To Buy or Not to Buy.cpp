// PAT-A 
// 40min

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char a[1001], b[1001];
	int i = 0, j, cnt = 0;
	int fa[1001];//flag of a

	for (j = 0; j != 1001; ++j) {
		fa[j] = 0;
	}

	cin >> a >> b;

	i = 0;
	j = 0;
	while (b[i] != '\0') {
		j = 0;
		while (a[j] != '\0') {
			if (fa[j] == 0 && a[j] == b[i]) {
				fa[j] = 1;
				++cnt;
				break;
			}
			++j;
		}
		++i;
	}

	if (cnt == strlen(b)) {
		cout << "Yes" << " " << strlen(a) - cnt << endl;
	} else {
		cout << "No" << " " << strlen(b) - cnt << endl;
	}
}
