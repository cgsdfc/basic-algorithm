#include <cstdio>
#include <map> // ���� head����Ա����
#include <string>
#include <iostream>
using namespace std;

map<string, int> Ans;

/*
����ı�Ȩ�������˵�ͨ��ʱ��֮�ͣ�
�������رߣ��ر߿�������ߣ���Ȩ��Ϊ�ر�Ȩ��֮�͡�
Ҳ���� A->B(30), A->B(40), B->A(40) ������AB֮����һ������ߣ�
����ȨΪ 30+40+40=110 ��
��ȨΪһ��������г��ߵı�Ȩ֮�͡�

����Ҫ�ҳ�ÿһ����ͨ�������ܱ�Ȩ����Ȩ���ֵ������Ӧ�Ķ��㣩��
�ڵ�����������һ���ṹ���ʾһ����ͨ������ 
*/

struct Comp {
	int father;
	int total; // �ܱ�Ȩ��
	int max; // ����Ȩ��
	int v; // ��Ӧ�Ķ��㡣
	int num; // �����Ľڵ�����	
};

// �������Ͻ硣 
#define MAXV (2000+5)

Comp comp[MAXV]; // ���鼯�� 
int weight[MAXV]; // ��Ȩ��

int index; // ����id��
map<string, int> mp1;
map<int, string> mp2;

// ���һ��� name-idӳ�䡣 
int Map(string& name) {
	if (mp1.count(name)) {
		return mp1[name];
	}
	mp1[name]=index;
	mp2[index]=name;
	return index++;
}

/*
����N����¼��˵������õ�2*N���ڵ㡣
*/ 
void Init(int N) {
	for (int i=0;i<2*N;++i) {
		comp[i].father=i;
		comp[i].total=0;
		comp[i].num=1;
		comp[i].max=-1;
	}
}

int Find(int x) {
	int a=x;
	while (x != comp[x].father) {
		x=comp[x].father;
	}
	while (a != comp[a].father) {
		int temp=comp[a].father;
		comp[a].father=x;
		a=temp;
	}
	return x;
}

/*
�ò��鼯ʵ�֣�Union ������ñȽϸ��ӡ�
���� DFS�����Ϊ��ࡣ���� DFS �����رߣ�©�ߵ��鷳��
�����鼯�������رߡ����ߵĸ��Ӷ�����ȵġ� 
*/
 
void Union(int a, int b, int w) {
	// ab�ߣ�ȨֵΪw��
	weight[a]+=w;
	weight[b]+=w;
//	printf("Wa %d Wb %d\n", weight[a], weight[b]);
	
	int faA=Find(a);
	int faB=Find(b);
//	printf("a %d b %d w %d\n",a,b,w);

	// �ȸ�������Ȩ��
	if (weight[a] > comp[faA].max) {
		comp[faA].v=a;
		comp[faA].max=weight[a];
	}
	// a ��faAΪ������ͨ������һ����Ա��
	// �����Լ���ͨ����������Ȩ�� 
	if (weight[b] > comp[faB].max) {
		comp[faB].v=b;
		comp[faB].max=weight[b];
	}
	// �ϲ�
	if (faA != faB) {
		comp[faA].father=faB;
		comp[faB].num += comp[faA].num;
		comp[faB].total += comp[faA].total + w;
		if (comp[faA].max > comp[faB].max) {
			// ��ΪA�鲢��B�飬����ABȡ���ֵ�� 
			comp[faB].max=comp[faA].max;
			comp[faB].v=comp[faA].v;
		}
	} else {
		// ͬһ����ͨ�飬����һ���ߡ� 
		comp[faA].total += w;
	}
	 
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N, K; // �ܼ�¼����������ֵ��
	scanf("%d%d", &N, &K);
	Init(N);
	
	while (N--) {
		string a,b;
		int w;
		cin >> a >> b >> w;
		int a1=Map(a);
		int b1=Map(b);
		Union(a1, b1, w);
	}
	// index ���ܽڵ�����
	for (int i=0;i<index;++i) {
		// ע�⣬ֻ����������ͨ�������������м����� 
		if (comp[i].father==i && comp[i].num > 2 && comp[i].total > K) {
			// ����������
			int v=comp[i].v; // ���졣
			string& head=mp2[v];
			Ans[head]=comp[i].num; 
//			printf("max %d head %d\n", comp[i].max, v);
		}
	}
	printf("%d\n", Ans.size());
	map<string,int>::iterator it;
	for (it=Ans.begin();it!=Ans.end();++it) {
		printf("%s %d\n", it->first.c_str(), it->second);
	}
	
	return 0;
}
