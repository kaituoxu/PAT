#include <iostream>

using namespace std;

struct ListNode {
	int e;//exponent
	double c;//coefficient
	ListNode *Next;

	ListNode() {
		e = 0;
		c = 0;
		Next = nullptr;
	}
};
typedef ListNode *List;

int main()
{
	List L1, L2, r1, r2;
	int K1, K2;

	L1 = new ListNode;
	L2 = new ListNode;
	r1 = L1;
	r2 = L2;

	//input
	//Create List 1 and List 2
	cin >> K1;
	for (int i = 0; i != K1; ++i) {
		List tmp = new ListNode;
		cin >> tmp->e >> tmp->c;
		r1->Next = tmp;
		r1 = r1->Next;
	}
	cin >> K2;
	for (int i = 0; i != K2; ++i) {
		List tmp = new ListNode;
		cin >> tmp->e >> tmp->c;
		r2->Next = tmp;
		r2 = r2->Next;
	}

	//Merge L1 and L2 to L1
	List L = new ListNode, r;
	int cnt = 0;

	r = L;
	r1 = L1->Next;
	r2 = L2->Next;
	while (r1 != nullptr && r2 != nullptr) {
		List tmp = new ListNode;
		++cnt;
		if (r1->e == r2->e) {
			tmp->e = r1->e;
			tmp->c = r1->c + r2->c;
			if (tmp->c != 0) {
				r->Next = tmp;
				r = r->Next;
			} else {
				--cnt;
			}

			r1 = r1->Next;
			r2 = r2->Next;
			--K1;
			--K2;
		} else if (r1->e > r2->e) {
			tmp->e = r1->e;
			tmp->c = r1->c;
			r->Next = tmp;
			r = r->Next;

			r1 = r1->Next;
			--K1;
		} else {//r1->e < r2->e
			tmp->e = r2->e;
			tmp->c = r2->c;
			r->Next = tmp;
			r = r->Next;

			r2 = r2->Next;
			--K2;
		}
	}

	if (r1 != nullptr) {
		r->Next = r1;
		cnt += K1;
	}
	if (r2 != nullptr) {
		r->Next = r2;
		cnt += K2;
	}


	//output
	if (cnt > 0) {
		cout << cnt << " ";
	} else {
		cout << 0 << endl;
	}
	r = L->Next;
	while (r != nullptr) {
		if (r->Next == nullptr) {
			printf("%d %.1f\n", r->e, r->c);
			break;
		}
		printf("%d %.1f ", r->e, r->c);
		r = r->Next;
	}

	//free memory
	delete L;
	delete L1;
	delete L2;
}
