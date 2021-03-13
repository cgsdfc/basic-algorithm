#include <cstdio>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int A, B, C; // ������������������ 

int* inq; // ɢ�����顣 
int N; // ɢ�������С��
int K; // Ŀ�����
 
void Init() {
	N=C*(B+1)*(A+1)+B*(A+1)+A+5;
	if (inq) delete inq;
	inq=new int[N];
	fill(inq, inq+N, 0);
}

/*
BFS����Ŀ������ʱ�Ĺؼ���ʹ��ɢ��ʵ��inq����֤ÿһ��Ԫ��ֻ���һ�Ρ�
inq���鱾����Ա���һЩ���ݣ�����step���������״̬����С������
ʵ��ɢ�еĹؼ��ǰ�״̬����Ϊɢ��ֵ��ʹ��inq���龡��С������ʵ�ִ�ɢ��ֵ
��״̬������ת����
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
	// i���ӵ����ޡ� 
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
		// ��iȫ��j���õ���һ��״̬��
		Node ans=*this;
		int v=min(data[i], Up(j)-data[j]);
		ans.data[i]-=v;
		ans.data[j]+=v;
		return ans;
	}
	// �ؼ�������״̬��ɢ��ֵ�� 
	int Hash() {
		int a=data[0];
		int b=data[1];
		int c=data[2];
		int ans=c*(B+1)*(A+1)+b*(A+1)+a;
//		printf("ans %d N %d\n", ans, N);
		assert(0<ans&&ans<N);
		return ans;
	}
	// �ؼ�������ɢ��ֵ��״̬�� 
	void Unhash(int h) {
		data[0]=h % (A+1); // a
		data[1]=h/(A+1)%(B+1); // b
		data[2]=h / (A+1) / (B+1); // c
		for (int i=0;i<MAXW;++i) {
			assert(0<=data[i]&&data[i]<=Up(i));
		}
	}
	// �Ƿ񵽴�Ŀ��״̬�� 
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
	inq[init.Hash()]=1; // inq �����������step�� 
	
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
		ö��ÿһ�Ա���i��j���Ȱ�iȫ��j���ٰ�jȫ��i��
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
	return -1; // �޽⡣ 
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
