#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100010

// 从节点1到节点1，。。。，N的顺时针距离。
//有了这个数组，就可以得出任意两点之间的顺时针距离。
//注意，不需要2x2矩阵。MAXN本身很大，所以必须节省时间空间。
//本解法空间O(n)，建表时间为O(n)，一个查询的时间O(1)。
//而任意两点之间的距离的最小值，就是顺时针距离和逆时针距离的最小者。
//二者相加即总距离和，故计算顺时针距离即可。
int dis[MAXN];

int main(int argc, char *argv[]) {
  int n;
  int sum = 0;
  int i;
  int m; // 查询数目。

  scanf("%d", &n); // 节点数。
  for (i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    dis[i] = sum;
    sum += x;
  }

  scanf("%d", &m);
  for (i = 0; i < m; ++i) {
    int u, v;
    int d1, d2;
    int res;

    scanf("%d%d", &u, &v);
    if (u > v) {
      // 保证u小于v。
      int tmp = u;
      u = v;
      v = tmp;
    }
    assert(u <= v);
    u--;
    v--;
    d1 = dis[v] - dis[u];
    d2 = sum - d1;
    res = d1 < d2 ? d1 : d2;
    printf("%d\n", res);
  }

  return 0;
}
