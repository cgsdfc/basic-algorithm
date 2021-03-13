#include <iostream>
#include <algorithm>
using namespace std;

/*
用lower/upper bound实现二分查找。
*/
template <typename Iter, typename T>
Iter BinarySearch(Iter first, Iter last, const T& value) {
	Iter it=lower_bound(first, last, value);
	if (it != last && *it == value) {
		return it;
	} else {
		return last;
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int a[]={1,2,3,4};
	int* it=BinarySearch(a, a+4, 2);
	printf("%d\n", it-a);
	
	return 0;
}
