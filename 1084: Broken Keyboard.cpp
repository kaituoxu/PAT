// 25minutes

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	bool visited[81];
	char ori[81], typ[81];
	char set[81];

	cin >> ori >> typ;
	for (int i = 0; ori[i] != '\0'; ++i) {
		ori[i] = toupper(ori[i]);
		visited[i] = false;
	}
	for (int i = 0; typ[i] != '\0'; ++i) {
		typ[i] = toupper(typ[i]);
	}
	//cout << ori << endl;
	//cout << typ << endl;
	//cout << strlen(typ) << endl;

	for (int i = 0; i < strlen(typ); ++i) {
		for (int j = 0; j < strlen(ori); ++j) {
			if (ori[j] == typ[i]) {
				visited[j] = true;
			}
		}
	}

	int n = 0;
	for (int i = 0; i < strlen(ori); ++i) {
		if (visited[i] == false) {
			//cout << ori[i];
			//s.insert(ori[i]);
			int j;
			for (j = 0; j < n; ++j) {
				if (ori[i] == set[j]) break;
			}
			if (j == n) {
				set[n] = ori[i];
				++n;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		cout << set[i];
	}

	cout << endl;

}
