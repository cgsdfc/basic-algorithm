#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����ͼ�ò��鼯����ͨ����������
*/
int N, M; // ������������ 

#define MAXN 1005
int father[MAXN];

int T;

int Find(int x) {
	int a=x;
	while (x != father[x]) {
		x=father[x];
	}
	// ·��ѹ�����Կ����ǲ��鼯���ڲ�ά��������
	// ��AVL�ĵ����������ѵĲ����ȵȡ� 
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
		// ab������ͬһ��ͨ��������ϲ�֮�� 
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
			// a��ʶb��������ab�ߡ�
			Union(a, b); // �ϲ���ͨ������
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
