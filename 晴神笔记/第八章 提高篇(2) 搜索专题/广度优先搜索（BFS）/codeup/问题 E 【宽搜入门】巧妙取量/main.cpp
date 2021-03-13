#include <cstdio>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int A, B, C; // 三个容器的最大体积。 

int* inq; // 散列数组。 
int N; // 散列数组大小。
int K; // 目标体积
 
void Init() {
	N=C*(B+1)*(A+1)+B*(A+1)+A+5;
	if (inq) delete inq;
	inq=new int[N];
	fill(inq, inq+N, 0);
}

/*
BFS的题目，不超时的关键是使用散列实现inq，保证每一个元素只入队一次。
inq数组本身可以编码一些数据，比如step，即到达此状态的最小步数。
实现散列的关键是把状态编码为散列值，使得inq数组尽量小。并且实现从散列值
到状态的来回转换。
*/
 
#define MAXW 3
struct Node {
	// a, b, c
	int data[MAXW];
	Node(int a, int b, int c) {
		data[0]=a;
		data[1]=b;
		data[2]=c;
	}
	Node() {
	}
	// i杯子的上限。 
	int Up(int i) {
		switch (i) {
			case 0: return A;
			case 1: return B;
			case 2: return C;
		}
	}
	bool Full(int i) {
		return data[i] == Up(i);
	}
	bool Empty(int i) {
		return data[i]==0;
	}
	Node Next(int i, int j) {
		// 把i全给j，得到下一个状态。
		Node ans=*this;
		int v=min(data[i], Up(j)-data[j]);
		ans.data[i]-=v;
		ans.data[j]+=v;
		return ans;
	}
	// 关键函数，状态到散列值。 
	int Hash() {
		int a=data[0];
		int b=data[1];
		int c=data[2];
		int ans=c*(B+1)*(A+1)+b*(A+1)+a;
//		printf("ans %d N %d\n", ans, N);
		assert(0<ans&&ans<N);
		return ans;
	}
	// 关键函数，散列值到状态。 
	void Unhash(int h) {
		data[0]=h % (A+1); // a
		data[1]=h/(A+1)%(B+1); // b
		data[2]=h / (A+1) / (B+1); // c
		for (int i=0;i<MAXW;++i) {
			assert(0<=data[i]&&data[i]<=Up(i));
		}
	}
	// 是否到达目标状态。 
	bool OK() {
		for (int i=0;i<MAXW;++i) {
			if (data[i] == K) return true;
		}
		return false;
	}
	void Print() {
		for (int i=0;i<MAXW; ++i) {
			printf("%d ", data[i]);
		}
		printf("\n");
	}
};

int BFS() {
	Node init(A, 0, 0);
	queue<int> q;
	q.push(init.Hash());
	inq[init.Hash()]=1; // inq 数组用来存放step。 
	
	while (!q.empty()) {
		int h=q.front();
		q.pop();
		Node p;
		p.Unhash(h);
//		p.Print();
//		printf("*\n");
		
		if (p.OK()) {
			return inq[h];
		}
		/*
		枚举每一对杯子i，j，先把i全给j，再把j全给i。
		*/
		Node next[10];
		int len=0;
		for (int i=0;i<MAXW;++i) {
			for (int j=i+1;j<MAXW;++j) {
				if (!p.Empty(i) && !p.Full(j)) {
					// i=>j ok
					Node v=p.Next(i, j);
					next[len++]=v;
				}
				if (!p.Empty(j) && !p.Full(i)) {
					Node v=p.Next(j, i);
					next[len++]=v;
				}
			}
		}
		for (int i=0;i<len;++i) {
			int h2=next[i].Hash();
//			next[i].Print();
//			printf("inq %d\n", inq[h2]);
			
			if (!inq[h2]) {
				inq[h2]=inq[h]+1; // step
				q.push(h2);
			}
		}
//		printf("\n");
	}
	return -1; // 无解。 
}

int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
	freopen("./in.txt","r",stdin);
#endif

	
	while (scanf("%d%d%d%d", &A, &B, &C, &K) != EOF) {
		Init();
		int ans=BFS();
		if (ans == -1) {
			puts("no");
		} else {
			puts("yes");
			printf("%d\n", ans-1);
		}
	}
	return 0;
}
