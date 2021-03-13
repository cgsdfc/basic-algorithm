#include <cstdio>
#include <algorithm>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // Կ��������
int K; // ��ʦ������

#define MAXK 1005
#define MAXN MAXK

int box[MAXN]; // ģ����ӣ�-1��ʾû��Կ�ף������ʾԿ�׵ı�š� 

enum {
	BOR, // ���ߡ� 
	RET, // �黹�� 
};

struct Op {
	int k; // Կ�ױ�š�
	int time; // ������ʱ�䡣
	int op;
};

struct {
	Op data[MAXK*2]; // һ����ʦ��������������
	int len;
} ops;

bool cmp(Op& a, Op& b) {
	if (a.time != b.time) {
		return a.time < b.time;
	}
	// ͬһʱ�䣬�Ȼ���ȡ��
	if (a.op != b.op) {
		return a.op > b.op;
	}
	if (a.op == RET) {
		// ͬʱ�黹������Կ�״�С����
		return a.k < b.k; 
	}
	// ͬʱ���ߣ�Կ�ױض���ͬ��˳����㡣
	return a.k < b.k; 
}

// ��һ��op�� 
void Do(Op& op) {
	if (op.op == BOR) {
		for (int i=0;i<N;++i) {
			if (box[i] == op.k) {
				// �ҵ�Կ�ס�
				box[i]=-1;
				break; 
			}
		}
	} else {
		// ��Կ�ס�
		for (int i=0;i<N;++i) {
			if (box[i] == -1) {
				// ��һ������λ�á�
				box[i]=op.k;
				break; 
			}
		} 
	}
}


int main(int argc, char** argv) {
	scanf("%d%d", &N, &K);
	for (int i=0;i<N;++i) {
		box[i]=i+1;
	} 
	
	for (int i=0;i<K;++i) {
		// K����ʦ����Ϣ��
		int w,s,c; // Կ�ף���ʼ�Ͽ�ʱ�䣬�Ͽ�ʱ����
		scanf("%d%d%d",&w,&s,&c);
		Op bor={w, s, BOR};
		Op ret={w, s+c, RET};
		ops.data[ops.len++]=bor;
		ops.data[ops.len++]=ret;
	}
	
	// ����ʱ���������
	sort(ops.data, ops.data+ops.len, cmp);
	
//	for (int i=0;i<ops.len;++i) {
//		Op op=ops.data[i];
//		printf("k %d time %d op %d\n", op.k, op.time, op.op);
//	}
	
	for (int i=0;i<ops.len;++i) {
		Do(ops.data[i]);
	}
	for (int i=0;i<N;++i) {
		printf("%d%s", box[i], i==N-1?"\n":" ");
	}
	
	return 0;
}
