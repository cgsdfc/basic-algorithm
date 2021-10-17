#include <cassert>
#include <cstdio>
#include <cstring>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
并查集求最大联通分量的节点数。

房子里的人必须互相为朋友，说明是一个联通图，
题目要求人数尽量多，说明这个是最大的联通分量。
*/

//点数。
#define MAXN (10000000)

int father[MAXN + 5];
int num[MAXN + 5];  // 统计以i为根的分量的大小，如果i不是根则为0.

int N;        // 边数。
int ans = 1;  // 最小值是1.

int Find(int x) {
    int a = x;
    while (father[x] != x) {
        x = father[x];
    }
    while (father[a] != a) {
        int temp = father[a];
        father[a] = x;
        a = temp;
    }
    return x;
}

/*
不超时的关键优化：
在Union中计算每个联通分量的大小，同时计算其中最大值。
这样就不用多次遍历大数组father，也就没有了O(V)的耗时。
复杂度就是O(E)。
*/

void Union(int a, int b) {
    int faA = Find(a);
    int faB = Find(b);
    if (faA != faB) {
        father[faA] = faB;
        num[faB] += num[faA];
        num[faA] = 0;
        if (num[faB] > ans) {
            // 最大的联通分量一定在合并中产生。
            ans = num[faB];
        }
    }
}

/*
注意这个图的点数远远大于边数，
可见大部分点是孤立点。所以要尽量使算法的复杂度依赖E，
不要依赖V。
*/

int main(int argc, char** argv) {
    while (scanf("%d", &N) != EOF) {
        ans = 1;  // 初始化！！
        for (int i = 1; i <= MAXN; ++i) {
            father[i] = i;
            num[i] = 1;
        }
        while (N--) {
            int A, B;
            scanf("%d%d", &A, &B);
            Union(A, B);
        }
        assert(ans > 0);
        printf("%d\n", ans);
    }
    return 0;
}
