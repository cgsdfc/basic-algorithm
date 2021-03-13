#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
无向图用并查集求联通分量个数。
*/
int N, M; // 点数，边数。 

#define MAXN 1005
int father[MAXN];

int T;

int Find(int x) {
	int a=x;
	while (x != father[x]) {
		x=father[x];
	}
	// 路径压缩可以看作是并查集的内部维护操作，
	// 像AVL的调整操作，堆的操作等等。 
	while (a != father[a]) {
		int temp=father[a];
		father[a]=x;
		a=temp;
	}
	return x;
}

void Union(int a, int b) {
	int faA=Find(a);
	int faB=Find(b);
	if (faA != faB) {
		// ab不属于同一联通分量，则合并之。 
		father[faA]=faB;
	}
}

int main(int argc, char** argv) {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		for (int i=1;i<=N;++i) {
			father[i]=i;
		}
		while (M--) {
			int a, b;
			scanf("%d%d",&a,&b);
			// a认识b，即存在ab边。
			Union(a, b); // 合并联通分量。
		}
		int num=0;
		for (int i=1;i<=N;++i) {
			if (father[i] == i) {
				++num;
			}
		}
		printf("%d\n", num);
	}
	return 0;
}
