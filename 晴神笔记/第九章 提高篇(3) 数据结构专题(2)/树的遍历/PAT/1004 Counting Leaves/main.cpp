#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
���������ÿһ���Ҷ�ڵ�������
����BFS��һ���ڵ����ʱ�������Ҷ�ڵ㣬��ò��Ҷ�ڵ�����һ��
BFS����Ҫ������ȣ����㡣
*/
#define MAXN 105

struct Node {
  int deep;
  vector<int> child;
} node[MAXN];

int level[MAXN]; // ÿ���Ҷ�ڵ�����
int MaxLevel;    // ��������ע����1��ʼ��
const int root = 1;
int N, M; // �ܽڵ㣬��Ҷ�ڵ㡣

int BFS() {
  queue<int> Q;
  Q.push(root);
  node[root].deep = 1;
  int ans = 0;

  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();

    if (node[now].child.empty()) {
      // ����һ��Ҷ�ڵ㡣
      level[node[now].deep]++;
    }
    if (node[now].deep > ans) {
      ans = node[now].deep;
      // ע�⣬���Ҫ��ÿ���ڵ���һ��������
      // �����ڳ�������������Ϊ�������Ӳ����������нڵ�ִ�У�����ִ�У���
    }
    for (int i = 0; i < node[now].child.size(); ++i) {
      int p = node[now].child[i];
      Q.push(p);
      node[p].deep = node[now].deep + 1;
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  if (!N)
    return 0;
  for (int i = 0; i < M; ++i) {
    // �����Ҷ�ڵ��С�
    int id, K;
    scanf("%d%d", &id, &K);
    while (K--) {
      int c;
      scanf("%d", &c);
      node[id].child.push_back(c);
    }
  }
  //	puts("input");

  MaxLevel = BFS();
  // ���ÿ���Ҷ�ڵ�����
  for (int i = 1; i <= MaxLevel; ++i) {
    printf("%d%s", level[i], i == MaxLevel ? "\n" : " ");
  }
  return 0;
}
