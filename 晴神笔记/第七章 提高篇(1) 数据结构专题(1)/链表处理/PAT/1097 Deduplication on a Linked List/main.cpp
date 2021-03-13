#include <iostream>
#include <algorithm>
using namespace std;

// Key��ɢ�б� 
#define MAXK (10000+5)
bool keys[MAXK];

enum {
	KEEP=2,
	DEL=1,
};

struct Node {
	int addr;
	int data;
	int next;
	int pos; // λ��
	int flag; // 0 ��ʾ�����ڣ�1��ʾɾ����2��ʾ������ 
};

#define MAXN (100000+5)
Node node[MAXN];

bool cmp(const Node& a, const Node& b) {
	if (a.flag != b.flag) {
		return a.flag > b.flag;
	}
	return a.pos < b.pos;
}

/*
�㷨��
ɨ��һ�飬����ɢ�б��ж�һ���ڵ��Ƿ�Ҫ�������������keep��
Ȼ�����򣬱����ڵ�����ߣ�ɾ���ڵ����ұߡ�
�ڲ�����ԭ�������˳�򲻱䡣
*/ 
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	for (int i=0;i<MAXN;++i) {
		node[i].next=-1;
		node[i].flag=0;
	}
	int head;
	int N;
	scanf("%d%d", &head, &N);
	while (N--) {
		int addr;
		int data;
		int next;
		scanf("%d%d%d", &addr, &data, &next);
		node[addr].addr=addr;
		node[addr].data=data;
		node[addr].next=next;
	}
	int p=head;
	int count=0; // �ܵĺϷ��ڵ����� 
	
	while (p != -1) {
		node[p].pos=count++;
		int K=abs(node[p].data);
		
		if (keys[K]) {
			// ɾ�� 
			node[p].flag=DEL;
		} else {
			// ������ 
			keys[K]=true;
			node[p].flag=KEEP;
		}
		p=node[p].next;
	}
	sort(node, node+MAXN, cmp);
	for (int i=0;i<count;++i) {
		if (i==count-1||node[i].flag != node[i+1].flag) {
			// ���һ���ڵ㡣
			printf("%05d %d -1\n", node[i].addr, node[i].data); 
		} else {
			printf("%05d %d %05d\n", node[i].addr, node[i].data, node[i+1].addr);
		}
	}
	
	return 0;
}
