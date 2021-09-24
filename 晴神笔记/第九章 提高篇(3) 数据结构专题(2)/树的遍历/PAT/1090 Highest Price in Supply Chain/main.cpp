#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/*
�������Ҷ�ӵ�����·�����ȣ��Լ����ֵ��
Ȼ������·����Ӧ�ļ�Ǯ��Ȼ������ж������·���Ľڵ㡣
*/

#define MAXN (100000 + 5)

// int father[MAXN];
// bool leaf[MAXN];
int N;
double P, r;
int root;

struct Node {
  int deep; // ��ȡ�
  vector<int> child;
};

Node node[MAXN];
// ����Ҷ�ڵ����ȡ�
vector<int> leaf;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��Ҷ�ӵ������ᵼ��ĳЩ�����·�����ظ������ܶ�Σ����Ը��ӶȲ���N��
���ǽӽ�Nƽ����
���Ӹ���ʼ����ÿһ���ڵ����ȣ���Ȼ���Ƽ����˷�Ҷ�ڵ����ȣ���ֻ��ҪҶ�ڵ��
��ȣ������Ǹ��Ӷ�ȴ��N�������BFS����BFS�����У������Լ���������ȡ�
*/

int BFS() {
  queue<int> Q;
  Q.push(root);
  node[root].deep = 0;
  int ans = 0; // ��ʼ��Ϊ������ȡ�

  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    if (node[now].child.empty()) {
      // ����Ҷ�ڵ㡣
      leaf.push_back(node[now].deep);
    }

    for (int i = 0; i < node[now].child.size(); ++i) {
      int p = node[now].child[i];
      Q.push(p);
      node[p].deep = node[now].deep + 1;
      if (node[p].deep > ans) {
        ans = node[p].deep;
      }
      // ����д���ԣ���Ϊ���п�����Ҷ�ڵ㣬������ֻ�����˷Ǹ���Ҷ�ڵ㡣
      /*
      ����д����ҪĿ�����Կռ任ʱ�䣬
      ��ΪҶ�ڵ�������ȫ���ڵ������١�
      �����Ż��Ĳ��Է�������ɴ���
      */
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  scanf("%d%lf%lf", &N, &P, &r);

  for (int i = 0; i < N; ++i) {
    node[i].child.clear();
  }

  for (int i = 0; i < N; ++i) {
    // ���븸�׽ڵ㡣
    int p;
    scanf("%d", &p);
    if (p == -1) {
      // ��¼���ڵ㡣
      root = i;
    } else {
      node[p].child.push_back(i);
    }
  }

  int ans = BFS();
  double price = P * pow(1 + r / 100, ans);
  int num = 0;
  //	for (int i=0;i<N;++i) {
  //		if (node[i].deep==ans) {
  //			++num;
  //		}
  //	}
  for (vector<int>::iterator it = leaf.begin(); it != leaf.end(); ++it) {
    if (ans == *it) {
      ++num;
    }
  }
  //	printf("root %d ans %d\n", root, ans);

  printf("%.2f %d\n", price, num);

  return 0;
}
