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

int M; // ϵͳ��������
int N; // ��������

struct IO {
	// ��¼һ�����е��������Ҫ��
	int in[MAXM]; // ϵͳ���롣���ȹ̶�ΪM�� 
	int out[MAXN]; // Ҫ�������ԭ����š�
	int len; // out����Ĵ�С�� 
};

// ÿ�����ж���Ҫһ��IO�ṹ�壬����Ҫ������S�����е���Ϣ���ſ��Կ�ʼ���С�
// ������Ϊһ�����е�����������Ϣ����ͬʱ�����������ȸ�����ȫ��������Ϣ��
// �ٸ���ȫ�������Ϣ�� 
vector<IO> runs; // ÿ�������ʼ��һ�Σ�ÿ��ϵͳ����S�Σ�len(runs)==S. 

/*
ע����ȷʵ�ָ����߼��Ų�����
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
			// �ӵ㣺0�İ�λȡ����-1��������! 
			ans = !ans;
			break;
	}
	return ans;
}

// һ����·Ԫ���� 
struct Node {
	int func;
	// ���������������ӵ����ǵ����롣
	// �������Ҫ��������������� 
	vector<int> in1;
	// ϵͳ����������ӵ����ǵ����롣 
	vector<int> in2;
	// ĳ�����е������ 
	int out;
};

Node node[MAXN];

// DFS�ر��� 
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
	// ����Ϊδ���ʡ� 
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
����DAG�ı�����˵���ǲ���Ҫ�Ӹ���ʼ�ģ�Ҳû�и��ĸ��
ֻ��Ҫ��ÿһ���ڵ���з��ʼ��ɡ���һ���ڵ�����꣬out��Ȼ���Ǽ������� 
*/ 
void Compute(int root, int T) {
	assert(inq[root]==0);
	inq[root]=-1; // ��ʼ���ʡ�
	// �ȵݹ����Ϊv�ṩ�����������
	for (int i=0;i<node[root].in1.size();++i) {
		int v=node[root].in1[i];
		assert(inq[v] != -1);
		if (!inq[v]) {
			Compute(v, T);
		}
	}
	
	vector<int> input;
	// ����֪���뿽��input��������㡣
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
	inq[root]=1; // ������ɡ� 
}

// �ַ�ת���֣�
int Parse(char str[]) {
#define TRAN(x) if (!strcmp(#x, str)) return x;
	TRAN(NOT)TRAN(AND)TRAN(OR)
	TRAN(XOR)TRAN(NAND)TRAN(NOR)
#undef TRAN	
	return -1;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
���⿼��㣺
1. ����ͼ�ļ���Ƿ��л�������������ģ�壩 
2. DAG ��������ȱ�������ͼ��DFSģ�壩 
3. �߼������ʵ�֡��ر���NAND,NOR��NOT��

����㣺
1. ��·��⣬inq����������״̬��0����δ������-1�����ڱ�����1��������ɡ�
2. NAND����ȫ��AND ���ó������NOT������������������NAND��
3. ʵ�ֵ���������λ�ķ�ת���������߼��ǣ������������ǰ�λ�ǣ�~����
������Ϊint��ֻ��1λ������������λҲ��仯��ʹ�� !0=-1, !1=-2��
��Ŀд��һ�䡰��Щ�ŵ�·��C���Եİ�λ������һ���ġ������ⲻ��ζ��ʵ����Ҳ��
һ���ġ���Ϊģ���ʱ����һ��int��ʾһλ������ʵ�����ǰ����߼��������&&��||������
�Ĺ�������ġ���int������ʾ��λʱ�����ʺ��ð�λ�������&��|��~���� 
*/ 
 
int main(int argc, char** argv) {
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		// ����һ��ϵͳ������N��������Ȼ������S�Ρ�
		scanf("%d%d", &M, &N);
		for (int i=1;i<=N;++i) {
			// ����һ������������ͼ��
			char str[25]; // func
			int k; // k ����˿����� 
			scanf("%s%d", str, &k);
			int func=Parse(str);
			node[i].func=func;
			node[i].in1.clear();
			node[i].in2.clear();
			node[i].out=-1;
			
			while (k--) {
				scanf("%s", str); // һ����ĸI��O��Ȼ��һ�����֣�������10λ����
				// ע��ϵͳ����ı�Ŵ�1��ʼ�� 
				int id=atoi(str+1);
				if (str[0] == 'I') {
					// ϵͳ���롣
					node[i].in2.push_back(id);
				} else {
					// �����������롣 
					node[i].in1.push_back(id);
				}
			}
		}
		
		int S; // ���д��������ܲ����У����Ǳ���������ݡ�
		scanf("%d", &S);
		// runs�±��0��ʼ��runs[i].out �±��1��ʼ�� 
		runs.resize(S);
		// ���е����롣
		for (int i=0;i<S;++i) {
			// ע�⣬����˿ڵı�ţ���1��ʼ�� 
			for (int j=1;j<=M;++j) {
				int x;
				scanf("%d", &x);
				runs[i].in[j]=x;
			}
		} 
		// ���е������
		for (int i=0;i<S;++i) {
			int s;
			scanf("%d", &s);
			runs[i].len=s;
			for (int j=0;j<s;++j) {
				int id;
				scanf("%d", &id); // Ҫ�������������š�
				runs[i].out[j]=id; 
			}
		}

		// ȫ��������ϡ�
		if (HasLoop()) {
			puts("LOOP");
			continue;
		}
		
		// �ٴ�dfs�� 
		for (int i=0;i<S;++i) {
			// ����ȫ������� 
			fill(inq+1, inq+N+1, 0);
			for (int v=1;v<=N;++v) {
				if (!inq[v]) {
					Compute(v, i);
				}
			}
			
			// �������Ҫ��out���������
			int len=runs[i].len;
			for (int j=0;j<len;++j) {
				int v=runs[i].out[j]; // Ҫ���Ϊv������������� 
				printf("%d%s", node[v].out, j==len-1?"\n":" ");
			} 
		}
			
	}
	return 0;
}
