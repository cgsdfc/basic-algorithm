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
��codeup�ϵ�һ����񣬿ӵ��������������������ظ��ģ���ô�����
��ͬ�����ֵ�˳���ǲ�ȷ���ģ����ԭ����λ�þͻ������Ϊ��ͬ�����ֵ���ԭ���е�λ���ǲ�ͬ�ģ���

��Ŀû�б�֤�����������ظ�������Ϊ��ȷ�������ȷ���ģ���ͬ���ְ����������������е�˳��
���š�
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
