#include <cstdio>
#include <algorithm>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // 钥匙数量。
int K; // 老师数量。

#define MAXK 1005
#define MAXN MAXK

int box[MAXN]; // 模拟盒子，-1表示没有钥匙，否则表示钥匙的编号。 

enum {
	BOR, // 借走。 
	RET, // 归还。 
};

struct Op {
	int k; // 钥匙编号。
	int time; // 动作的时间。
	int op;
};

struct {
	Op data[MAXK*2]; // 一个老师产生两个操作。
	int len;
} ops;

bool cmp(Op& a, Op& b) {
	if (a.time != b.time) {
		return a.time < b.time;
	}
	// 同一时间，先还后取。
	if (a.op != b.op) {
		return a.op > b.op;
	}
	if (a.op == RET) {
		// 同时归还，按照钥匙从小到大。
		return a.k < b.k; 
	}
	// 同时借走，钥匙必定不同，顺序随便。
	return a.k < b.k; 
}

// 做一个op。 
void Do(Op& op) {
	if (op.op == BOR) {
		for (int i=0;i<N;++i) {
			if (box[i] == op.k) {
				// 找到钥匙。
				box[i]=-1;
				break; 
			}
		}
	} else {
		// 还钥匙。
		for (int i=0;i<N;++i) {
			if (box[i] == -1) {
				// 第一个空闲位置。
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
		// K个老师的信息。
		int w,s,c; // 钥匙，开始上课时间，上课时长。
		scanf("%d%d%d",&w,&s,&c);
		Op bor={w, s, BOR};
		Op ret={w, s+c, RET};
		ops.data[ops.len++]=bor;
		ops.data[ops.len++]=ret;
	}
	
	// 按照时间递增排序。
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
