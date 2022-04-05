#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXK (1001)  // 爱好最大下标。
#define MAXN (1001)  // 人数 。

struct Hobby {
    // 遍历所有爱好。
    int data[MAXK];
    int len;
    // 查询某个爱好是否存在。
    bool hash[MAXK];
};

// N个人的爱好信息。
Hobby hb[MAXN];

bool Has(int a, int b) {
    // 两个人是否有公共爱好。
    if (hb[a].len > hb[b].len) { swap(a, b); }
    // 遍历较短的爱好列表。
    for (int i = 0; i < hb[a].len; ++i) {
        int x = hb[a].data[i];
        if (hb[b].hash[x]) { return true; }
    }
    return false;
}

/*
任意两个人，只要他们有公共爱好，它们就有一条边，
这种关系不具有传递性，也就是说，A和B有公共爱好，B和C有公共爱好，
但是A和C可以没有公共爱好。

枚举所有边，即枚举所有的节点对，如果它们有公共爱好，就进行合并。
O(N*N*K)，由于N平方已经10e6了，判断有边的逻辑最好快些。
对每个人的爱好列表排序，然后用归并法判断是否有公共元素，
预处理的复杂度是NKlogK，每次查询的复杂度是K。

方法1：
开一个MAXK数组bool型对应每个人的爱好列表，查询时遍历二者的数组。
预处理是O(K)，每次查询是O(MAXK),

方法2：
排序，然后归并找公共元素。预处理是O(KlogK), 每次查询是O(K)

方法3:
对每一个人，既记录bool数组，也记录int数组，然后查询时遍历一个人的int数组，
看另一个人的bool数组。预处理是O(K)，每次查询是O(K).
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;  // 总人数。

int father[MAXN];
int num[MAXN];

int Find(int x) {
    int a = x;
    while (x != father[x]) {
        x = father[x];
    }
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
        num[faB] += num[faA];
        num[faA] = 0;
    }
}

bool cmp(int a, int b) {
    return a > b;
}

/*
数据的特点，每个人的K值比较小，不接近MAXK，即爱好比较稀疏，
所以O(K)的比较算法不会超时。
*/

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int k;
        scanf("%d:", &k);
        hb[i].len = k;
        for (int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            hb[i].data[j] = x;
            hb[i].hash[x] = true;
        }
    }
    // 并查集初始化。
    for (int i = 1; i <= N; ++i) {
        father[i] = i;
        num[i] = 1;
    }
    // 枚举每一对人。
    for (int i = 1; i <= N - 1; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (Has(i, j)) { Union(i, j); }
        }
    }
    // num记录了每个分量的大小。
    sort(num + 1, num + N + 1, cmp);
    // 统计非零分量，即cluster数量。
    int len = 0;
    for (int i = 1; i <= N; ++i) {
        if (num[i]) {
            ++len;
        } else { // 因为是有序的，后面都是0，不用看了。
            break;
        }
    }
    printf("%d\n", len); // 输出所有分量的大小。
    for (int i = 1; i <= len; ++i) {
        printf("%d%s", num[i], i == len ? "\n" : " ");
    }

    return 0;
}
