#include <iostream>
#include <algorithm>
using namespace std;

// Key的散列表 
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
	int pos; // 位序。
	int flag; // 0 表示不存在，1表示删除，2表示保留。 
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
算法：
扫描一遍，根据散列表判定一个节点是否要保留，即做标记keep。
然后排序，保留节点在左边，删除节点在右边。
内部按照原来链表的顺序不变。
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
	int count=0; // 总的合法节点数。 
	
	while (p != -1) {
		node[p].pos=count++;
		int K=abs(node[p].data);
		
		if (keys[K]) {
			// 删除 
			node[p].flag=DEL;
		} else {
			// 保留。 
			keys[K]=true;
			node[p].flag=KEEP;
		}
		p=node[p].next;
	}
	sort(node, node+MAXN, cmp);
	for (int i=0;i<count;++i) {
		if (i==count-1||node[i].flag != node[i+1].flag) {
			// 最后一个节点。
			printf("%05d %d -1\n", node[i].addr, node[i].data); 
		} else {
			printf("%05d %d %05d\n", node[i].addr, node[i].data, node[i+1].addr);
		}
	}
	
	return 0;
}
