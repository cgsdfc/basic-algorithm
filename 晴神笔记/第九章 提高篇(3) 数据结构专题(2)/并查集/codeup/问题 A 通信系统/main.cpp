#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
只要通信系统是一个树，包括了所有端点，就满足条件。
因为题目的两个条件，就是联通和无环。如果一个图满足这两个关系，
那它必定是树。

如何用并查集判断这两个条件是否成立：
1. 联通， 所有元素的根都相同。
2. 无环，联通并且 E=V-1。
*/

int N, M; // N个节点，M段线路。

#define MAXN 1005

/*
BUG点：
1. 第一次，答案错误0，输入循环有问题，NM同时为0才结束。
2. 第二层，超时0，Find要路径压缩，因为每次查找最坏是N，M次就是MN，
其中M=N^2，所以是N^3的复杂度。N是1000，N的三次方就是10e9，稳稳超时。
优化后复杂度是M，就是N平方，才10e6。
*/

int father[MAXN];

int Find(int x) {
  int a = x;
  while (x != father[x]) {
    x = father[x];
  }
  // 超时了，必须压缩。
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
  // 注意，NM都为0时输入结束，即只要其中一个不为零就要处理。
  while (scanf("%d%d", &N, &M), (N || M)) {
    bool flag = M == N - 1;
    for (int i = 1; i <= N; ++i) {
      father[i] = i;
    }
    /*
    利用并查集判断联通性，
    并查集会忽略掉成环的边，而得出森林。
    最后检查是否只有一个集合即可。
    */
    while (M--) {
      int a, b;
      // 无重边，无自环。
      scanf("%d%d", &a, &b);
      Union(a, b);
    }
    int num = 0; // 多少个集合。
    for (int i = 1; i <= N; ++i) {
      if (father[i] == i) {
        ++num; // 一个根节点代表一个集合。
      }
    }
    puts(flag && num == 1 ? "Yes" : "No");
  }

  return 0;
}
