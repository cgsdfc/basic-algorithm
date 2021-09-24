#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
using namespace std;
/*
�á���ȫ�������������˼·��
�Ƚ�����Ȼ�����������Ĵ�С��
Ȼ��Լ�ֵ��������ó�����
Ȼ���������������������
���Ӷ�Ϊnlogn������n��С�����Բ��ᳬʱ��

˼·����
1. ������Ȼ����������ó���ŵ�����
2. �Լ�ֵ�������򣬵ó�����������
3. ���ڱ�źͼ�ֵһһ��Ӧ������֪��ĳ��ֵ��Ӧ�ı�ţ�
�������롣
4. ���������
*/

#define MAXN 105
struct Node {
  int data;
  int lchild, rchild;
} node[MAXN];

int N;
int data[MAXN]; // ��ֵ��

// ��ŵ��������С�
struct {
  int data[MAXN];
  int len;
} in;

void Inorder(int root) {
  if (root != -1) {
    Inorder(node[root].lchild);
    in.data[in.len++] = root;
    Inorder(node[root].rchild);
  }
}

const int Root = 0;

void BFS(int &i) {
  queue<int> Q;
  Q.push(Root);
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    printf("%d%s", node[now].data, i == N - 1 ? "\n" : " ");
    i++;
    if (node[now].lchild != -1) {
      Q.push(node[now].lchild);
    }
    if (node[now].rchild != -1) {
      Q.push(node[now].rchild);
    }
  }
}

void Fill() {
  assert(N == in.len);
  // ��data����node
  for (int i = 0; i < N; ++i) {
    node[in.data[i]].data = data[i];
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    // ����ĸ�ʽ�ͱ�ʾ�ĸ�ʽ��ȫ��ͬ��
    scanf("%d%d", &node[i].lchild, &node[i].rchild);
  }
  // ����ؼ��֡�
  for (int i = 0; i < N; ++i) {
    scanf("%d", &data[i]);
  }
  // ���������
  sort(data, data + N);
  // �±������
  Inorder(Root);
  Fill();
  int i = 0;
  BFS(i);

  return 0;
}
