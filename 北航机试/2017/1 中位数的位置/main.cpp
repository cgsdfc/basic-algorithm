#include <cstdio>
#include <algorithm>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MAXN=1000000+5;

struct Node {
	int data;
	int index;
	friend bool operator<(Node a, Node b) {
		if (a.data != b.data) return a.data<b.data;
		return a.index<b.index;
	}
} node[MAXN];

/*
和codeup上的一题很像，坑点在于输入的数字如果有重复的，那么排序后
相同的数字的顺序是不确定的，输出原序列位置就会出错（因为相同的数字但是原序列的位置是不同的）。

题目没有保证输入数字无重复，所以为了确保结果是确定的，相同数字按照它们在输入序列的顺序
来排。
*/

void Print(int i) {
		printf("%d %d\n", node[i].data, node[i].index);
}

int main(int argc, char** argv) {
	int N;
	scanf("%d",&N);
	for (int i=0;i<N;++i) {
		scanf("%d", &node[i].data);
		node[i].index=i+1;
	}
	sort(node,node+N);
	if (N & 1) {
		// odd:
		Print(N/2);
	} else {
		// even:
		Print(N/2-1);
		Print(N/2);
	}
	return 0;
}
