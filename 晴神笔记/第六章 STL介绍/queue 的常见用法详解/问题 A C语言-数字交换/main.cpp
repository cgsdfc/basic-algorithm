#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
注意处理第一个元素是最大的，或者最后一个元素是最小的情况。
当第一个操作，即交换第一个和最小元素完成后，最大元素的下标可能改变，
最后一个元素的值可能改变。 
所以先记录最大最小值的下标，然后依次交换两次的做法是不对的。
必须每次都查找最大值或最小值所在位置，然后交换。
用队列实现的话，可以设置一个临时队列，完成一次两数交换。 
*/

void Print(queue<int> q) {
	while (!q.empty()) {
		printf("%d ", q.front());
		q.pop();
	}
	printf("\n");
}

/*
把x出现的位置换为第一个元素，把第一个元素换为x。
*/ 
void SwapFirst(queue<int>& q, int x) {
	if (q.front() == x) {
		return;
	}
	queue<int> temp;
	temp.push(x); // x作为第一个元素。 
	int first=q.front();
	q.pop();
	while (!q.empty()) {
		if (q.front() == x) {
			// x出现了，换为first。 
			temp.push(first);
		} else {
			temp.push(q.front());
		}
		q.pop();
	}
	q=temp;
}

/*
把x出现的位置换为最后一个元素，把最后一个元素换为x。
*/ 
void SwapLast(queue<int>& q, int x) {
	if (q.back() == x) {
		return;
	}
	queue<int> temp;
	int last=q.back();
	// q的最后一个元素不能放入temp，
	// 而应该把x作为最后一个放入temp。 
	while (q.size() != 1) {
		if (q.front() == x) {
			temp.push(last);
		} else {
			temp.push(q.front());
		}
		q.pop();
	}
	temp.push(x);
	q=temp; 
}

int main(int argc, char** argv) {
	const int N=10;
	int i;
	int Min, Max;
	queue<int> q;
	
	for (int i=0;i<N;++i) {
		int x;
		scanf("%d", &x);
		if (i==0||x>Max) {
			Max=x;
		}
		if (i==0||x<Min) {
			Min=x;
		}
		q.push(x);
	}
	
//	printf("Min %d Max %d\n", Min, Max);
	
	SwapFirst(q, Min);
//	Print(q);
	
	SwapLast(q, Max);
	Print(q);
	
	return 0;
}
