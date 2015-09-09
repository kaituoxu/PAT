// PAT-A 1005
// 2015/9/9 15:50 - 16:15
// author: Kaituo Xu


#include <iostream>

using namespace std;

int main()
{
	char *n;
	int value = 0;
	int i = 0;

	n = new char[101];
	cin >> n;

	//sum every digit of n
	while (*n != '\0') {
		value += *n++ - '0';
	}
	//cout << value << endl;

	int stack[101], top = -1;
	//this if statement is aviod the case in which value equal to 0.
	if (value == 0) {
		stack[++top] = value;
	}
	//push every digit of value to a stack
	while (value != 0) {
		stack[++top] = value % 10;
		value /= 10;
	}
	// from highest digit to lowest digit(stack top-down), output correspond English
	while (top != -1) {
		switch (stack[top--]) {
		case 0:
			cout << "zero";
			break;
		case 1:
			cout << "one";
			break;
		case 2:
			cout << "two";
			break;
		case 3:
			cout << "three";
			break;
		case 4:
			cout << "four";
			break;
		case 5:
			cout << "five";
			break;
		case 6:
			cout << "six";
			break;
		case 7:
			cout << "seven";
			break;
		case 8:
			cout << "eight";
			break;
		case 9:
			cout << "nine";
			break;
		}
		// avoid extra space at the end of a line
		if (top == -1) {
			cout << endl;
		} else {
			cout << " ";
		}
	}
}
//test data
//1.
//9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
//2.
//0
//3.
//12345
