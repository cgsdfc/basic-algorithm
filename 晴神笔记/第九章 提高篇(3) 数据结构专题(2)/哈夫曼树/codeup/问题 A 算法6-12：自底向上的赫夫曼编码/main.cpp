#include <cassert>
#include <climits>
#include <cstdio>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ��Ҷ�ӽڵ�����
#define MAXN 105
// �����������ܽڵ���������Ҷ�ӽڵ���ȷ����
#define MAXV (2 * MAXN - 1)

struct Node {
  int parent;
  // ��Ϊ���Ե����Ͻ��������Բ���Ҫchild��
  // ��¼��ǰ�ڵ������ӻ����Һ��Ӽ��ɡ�
  bool isRight; // ���Һ��ӣ��Ը��ڵ������塣
                //	bool isLeaf; // ��Ҷ�ӽڵ㡣
  int weight;   // Ȩ�ء�
  /*
  ��Ŀ�����㷨��û���öѣ����Ե�������ͬ��Ȩ��ʱ��
  ������ѡ�������������濼ǰ��Ԫ�أ�Ҳ����������ɨ����
  ����Сֵ���������ö�ģ�⣬���뻹ԭ�������ȼ�������
  �õ�һ���Ĵ𰸡�
  */
  int id;
} node[MAXV];

int index = 0;

int NewNode() { return index++; }

struct cmp {
  // ע�⣺��ͬ��Ȩ�أ�idС���ȳ��֣���ΪҪģ������ɨ������ԡ�
  bool operator()(int a, int b) {
    // weight С���ȳ��ӡ�
    if (node[a].weight != node[b].weight) {
      return node[a].weight > node[b].weight;
    }
    // idС���ȳ��ӡ�
    return node[a].id > node[b].id;
  }
};

// �����������������ظ��ڵ㡣
int Build(int N) {
  // ע�����������ر�С���ѣ���greater��
  priority_queue<int, vector<int>, cmp> Q;
  // ����N��Ȩ�أ�������Ҷ�ӽڵ㡣
  int id = 0;
  while (N--) {
    int w;
    scanf("%d", &w);
    int p = NewNode();
    //		node[p].isLeaf=true;
    node[p].weight = w;
    node[p].parent = -1; // һ��ʼ���Ǹ��ڵ㣬Ҳ��Ҷ�ڵ㡣
    node[p].id = id++;
    Q.push(p);
  }
  // �����ɵĽڵ㣬��idҪ������š�
  while (Q.size() > 1) {
    int a = Q.top();
    Q.pop();
    int b = Q.top();
    Q.pop();
    /*
    ע�⣬������СԪ����id��˳����֡�
    */
    if (node[a].id > node[b].id) {
      swap(a, b);
    }

    //		printf("%d %d\n", node[a].weight, node[b].weight);

    // ����̶����ȳ��ӵ������ӡ�
    node[a].isRight = false;
    node[b].isRight = true;
    // �ϲ�Ϊ����
    int root = NewNode();
    node[root].weight = node[a].weight + node[b].weight;
    node[root].parent = -1; // ��֪����
    //		node[root].isLeaf=false; // ���к��ӣ�����Ҷ�ӡ�
    node[root].id = id++;
    node[a].parent = node[b].parent = root;
    Q.push(root);
  }
  return Q.top();
}

// ��Ҷ���Ҹ������ɱ��롣
void FindCode(int v, int root) {
  //	assert(node[v].isLeaf);
  vector<int> code;
  while (v != root) {
    //		printf("%d ", node[v].weight);
    code.push_back((int)node[v].isRight);
    v = node[v].parent;
  }
  for (int i = code.size() - 1; i >= 0; --i) {
    printf("%d", code[i]);
  }
  printf("\n");
}

/*
���ɹ��������롣
ע�⣺
1. �������Ľڵ�Ȩ�ش󣬿���Ҷ�ӵĽڵ�Ȩ��С����ˣ�
Ҫ��С���ѣ�ÿ��ѡ��Ȩ����С�������ڵ���кϲ���
*/
int main(int argc, char **argv) {
  int N;
  while (scanf("%d", &N) != EOF) {
    index = 0;
    int root = Build(N);
    // ע�⣬0--N-1��Ҷ�ӡ�
    for (int i = 0; i < N; ++i) {
      FindCode(i, root);
    }
  }
  return 0;
}
