#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

enum {
	NOT,
	AND,
	OR,
	XOR,
	NAND,
	NOR,
};

#define MAXM (2500+5)
#define MAXN 505

int M; // 系统输入数。
int N; // 器件数。

struct IO {
	// 记录一次运行的输入输出要求。
	int in[MAXM]; // 系统输入。长度固定为M。 
	int out[MAXN]; // 要求输出的原件编号。
	int len; // out数组的大小。 
};

// 每次运行都需要一个IO结构体，并且要输入完S次运行的信息，才可以开始运行。
// 这是因为一次运行的输入和输出信息不是同时给出，而是先给出了全部输入信息，
// 再给出全部输出信息。 
vector<IO> runs; // 每个问题初始化一次，每个系统运行S次，len(runs)==S. 

/*
注意正确实现各种逻辑门操作。
*/ 
int Func(vector<int>& in, int op) {
	int ans=in.front();
	assert(ans != -1);
	for (int i=1;i<in.size();++i) {
		int x=in[i];
		assert(x != -1);
		switch (op) {
			case AND:
			case NAND:
				ans &= x;
				break;
			case OR:
			case NOR:
				ans |= x;
				break;
			case XOR:
				ans ^= x;
				break;
		}
	}
	switch (op) {
		case NOT:
		case NAND:
		case NOR:
			// 坑点：0的按位取反是-1，必须用! 
			ans = !ans;
			break;
	}
	return ans;
}

// 一个电路元件。 
struct Node {
	int func;
	// 别的器件的输出连接到我们的输入。
	// 器件编号要随机访问器件本身。 
	vector<int> in1;
	// 系统的输入端连接到我们的输入。 
	vector<int> in2;
	// 某次运行的输出。 
	int out;
};

Node node[MAXN];

// DFS必备。 
int inq[MAXN];

bool hasloop;
 
void DFS(int v) {
//	printf("v %d\n", v);
	inq[v]=-1;
	for (int i=0;i<node[v].in1.size();i++) {
		int u=node[v].in1[i];
		if (inq[u] == -1) {
			hasloop=true;
		} else if (!inq[u]) {
			DFS(u);
		}
	}
	inq[v]=1;
}

bool HasLoop() {
	// 设置为未访问。 
	fill(inq+1, inq+N+1, 0);
	hasloop=false;
	for (int i=1;i<=N;++i) {
		if (!inq[i]) {
			DFS(i);
		}
	}
	return hasloop;
}

/*
对于DAG的遍历来说，是不需要从根开始的，也没有根的概念，
只需要对每一个节点进行访问即可。当一个节点访问完，out自然就是计算结果。 
*/ 
void Compute(int root, int T) {
	assert(inq[root]==0);
	inq[root]=-1; // 开始访问。
	// 先递归计算为v提供输入的器件。
	for (int i=0;i<node[root].in1.size();++i) {
		int v=node[root].in1[i];
		assert(inq[v] != -1);
		if (!inq[v]) {
			Compute(v, T);
		}
	}
	
	vector<int> input;
	// 把已知输入拷入input，方便计算。
	for (int i=0;i<node[root].in1.size();++i) {
		int v=node[root].in1[i];
		input.push_back(node[v].out);
	}
	for (int i=0;i<node[root].in2.size();++i) {
		int v=node[root].in2[i];
		input.push_back(runs[T].in[v]);
	}
	int ans=Func(input, node[root].func);	
	node[root].out=ans;
	inq[root]=1; // 访问完成。 
}

// 字符转数字：
int Parse(char str[]) {
#define TRAN(x) if (!strcmp(#x, str)) return x;
	TRAN(NOT)TRAN(AND)TRAN(OR)
	TRAN(XOR)TRAN(NAND)TRAN(NOR)
#undef TRAN	
	return -1;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
本题考察点：
1. 有向图的检测是否有环。（拓扑排序模板） 
2. DAG 的深度优先遍历。（图的DFS模板） 
3. 逻辑运算的实现。特别是NAND,NOR和NOT。

出错点：
1. 环路检测，inq必须有三个状态：0：尚未遍历，-1：正在遍历，1：遍历完成。
2. NAND是先全部AND ，得出结果再NOT，而不是两个两个的NAND。
3. 实现单个二进制位的反转，必须用逻辑非（！），而不是按位非（~）。
这是因为int不只有1位，所以其他的位也会变化，使得 !0=-1, !1=-2。
题目写了一句“这些门电路和C语言的按位运算是一样的”，但这不意味着实现上也是
一样的。因为模拟的时候，用一个int表示一位，所以实际上是按照逻辑运算符（&&，||，！）
的规则运算的。当int用来表示多位时，才适合用按位运算符（&，|，~）。 
*/ 
 
int main(int argc, char** argv) {
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		// 输入一个系统，包括N个器件，然后运行S次。
		scanf("%d%d", &M, &N);
		for (int i=1;i<=N;++i) {
			// 输入一个器件，构建图。
			char str[25]; // func
			int k; // k 输入端口数量 
			scanf("%s%d", str, &k);
			int func=Parse(str);
			node[i].func=func;
			node[i].in1.clear();
			node[i].in2.clear();
			node[i].out=-1;
			
			while (k--) {
				scanf("%s", str); // 一个字母I或O，然后一个数字，不超过10位数。
				// 注意系统输入的编号从1开始。 
				int id=atoi(str+1);
				if (str[0] == 'I') {
					// 系统输入。
					node[i].in2.push_back(id);
				} else {
					// 其他器件输入。 
					node[i].in1.push_back(id);
				}
			}
		}
		
		int S; // 运行次数，可能不运行，但是必须读入数据。
		scanf("%d", &S);
		// runs下标从0开始，runs[i].out 下标从1开始。 
		runs.resize(S);
		// 所有的输入。
		for (int i=0;i<S;++i) {
			// 注意，输入端口的编号，从1开始。 
			for (int j=1;j<=M;++j) {
				int x;
				scanf("%d", &x);
				runs[i].in[j]=x;
			}
		} 
		// 所有的输出。
		for (int i=0;i<S;++i) {
			int s;
			scanf("%d", &s);
			runs[i].len=s;
			for (int j=0;j<s;++j) {
				int id;
				scanf("%d", &id); // 要求输出的器件编号。
				runs[i].out[j]=id; 
			}
		}

		// 全部输入完毕。
		if (HasLoop()) {
			puts("LOOP");
			continue;
		}
		
		// 再次dfs。 
		for (int i=0;i<S;++i) {
			// 计算全部结果。 
			fill(inq+1, inq+N+1, 0);
			for (int v=1;v<=N;++v) {
				if (!inq[v]) {
					Compute(v, i);
				}
			}
			
			// 按照输出要求out进行输出。
			int len=runs[i].len;
			for (int j=0;j<len;++j) {
				int v=runs[i].out[j]; // 要编号为v的器件的输出。 
				printf("%d%s", node[v].out, j==len-1?"\n":" ");
			} 
		}
			
	}
	return 0;
}
