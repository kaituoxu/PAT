#include <iostream>

using namespace std;

void format(int a);

int main()
{
	int a, b;
	cin >> a >> b;
	format(a + b);
}

void format(int a) 
{
	if (a < 0) {
		cout << "-";
		a = -a;
	}
	if (a / 1000 > 0) {//a >= 1000, a's bits >= 4
		format(a / 1000);
		printf(",%03d", a % 1000);
	} else {
		cout << a;
	}
}
