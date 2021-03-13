#include <cstdio>
#include <map> // 保存 head和组员数。
#include <string>
#include <iostream>
using namespace std;

map<string, int> Ans;

/*
本题的边权是两个端点通话时间之和，
可以有重边，重边看作无向边，但权重为重边权重之和。
也就是 A->B(30), A->B(40), B->A(40) 都看作AB之间有一条无向边，
但边权为 30+40+40=110 。
点权为一个点的所有出边的边权之和。

本题要找出每一个联通分量的总边权，点权最大值（和相应的顶点），
节点总数，故用一个结构体表示一个联通分量。 
*/

struct Comp {
	int father;
	int total; // 总边权。
	int max; // 最大点权。
	int v; // 对应的顶点。
	int num; // 分量的节点数。	
};

// 顶点数上界。 
#define MAXV (2000+5)

Comp comp[MAXV]; // 并查集。 
int weight[MAXV]; // 点权。

int index; // 分配id。
map<string, int> mp1;
map<int, string> mp2;

// 查找或建立 name-id映射。 
int Map(string& name) {
	if (mp1.count(name)) {
		return mp1[name];
	}
	mp1[name]=index;
	mp2[index]=name;
	return index++;
}

/*
对于N条记录来说，最多用到2*N个节点。
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
用并查集实现，Union 函数变得比较复杂。
若用 DFS，则较为简洁。但是 DFS 有算重边，漏边的麻烦，
而并查集不会算重边。二者的复杂度是相等的。 
*/
 
void Union(int a, int b, int w) {
	// ab边，权值为w。
	weight[a]+=w;
	weight[b]+=w;
//	printf("Wa %d Wb %d\n", weight[a], weight[b]);
	
	int faA=Find(a);
	int faB=Find(b);
//	printf("a %d b %d w %d\n",a,b,w);

	// 先更新最大点权。
	if (weight[a] > comp[faA].max) {
		comp[faA].v=a;
		comp[faA].max=weight[a];
	}
	// a 是faA为根的联通分量的一个成员，
	// 更新自己联通分量的最大点权。 
	if (weight[b] > comp[faB].max) {
		comp[faB].v=b;
		comp[faB].max=weight[b];
	}
	// 合并
	if (faA != faB) {
		comp[faA].father=faB;
		comp[faB].num += comp[faA].num;
		comp[faB].total += comp[faA].total + w;
		if (comp[faA].max > comp[faB].max) {
			// 因为A块并入B块，所以AB取最大值。 
			comp[faB].max=comp[faA].max;
			comp[faB].v=comp[faA].v;
		}
	} else {
		// 同一个联通块，多了一条边。 
		comp[faA].total += w;
	}
	 
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N, K; // 总记录数，犯罪阈值。
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
	// index 是总节点数。
	for (int i=0;i<index;++i) {
		// 注意，只考虑最后的联通分量，不考虑中间结果。 
		if (comp[i].father==i && comp[i].num > 2 && comp[i].total > K) {
			// 符合条件。
			int v=comp[i].v; // 首领。
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
