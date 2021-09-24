#include <cassert>
#include <cstdio>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
给出一个无向图，问最少加上几条边能使其成为联通图。
把每个联通分量看作一个点，然后使他们联通的最小边数就是
组织成一棵树，即V-1，V是联通分量的个数。
用并查集统计联通分量个数即可。
*/

#define MAXN 1005

int father[MAXN];
int N;
int M;

int Find(int x) {
  int a = x;
  while (x != father[x]) {
    x = father[x];
  }
  // 路径压缩。
  while (a != father[a]) {
    int temp = father[a];
    father[a] = x;
    a = temp;
  }
  return x;
}

void Union(int a, int b) {
  int faA = Find(a);
  int faB = Find(b);
  if (faA != faB) {
    father[faA] = faB;
  }
}

int main(int argc, char **argv) {
  while (scanf("%d", &N), N) {
    for (int i = 1; i <= N; ++i) {
      // 初始化并查集。
      father[i] = i;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
      int a, b;
      // 输入一条边。
      // 注意一条边，实际上告诉我们两个点ab是联通的，
      // 即同属一个集合，只要按照并查集的Union操作即可，
      // 联通关系可能是多余的，因为按之前的关系可能已经知道
      // ab同属一个集合。
      scanf("%d%d", &a, &b);
      Union(a, b);
    }
    // 统计联通分量个数，就是统计集合数（根节点数）。
    int num = 0;
    for (int i = 1; i <= N; ++i) {
      if (father[i] == i) {
        ++num;
      }
    }
    assert(num >= 1);
    printf("%d\n", num - 1);
  }
  return 0;
}
