#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
对每个（x，r），求出大于等于x且r==1的个数，以及小于x且r==0的个数，
这两个数值相加，就是以x为参数的正确率。这个数可以预计算，复杂度是NlogN（先排序）。
有了每个数作为参数的正确率后，从大到小遍历取max即可。

这样就把N平方的复杂度降到NlogN。

活用递推

具体实现的时候，注意重复元素的问题。《算法笔记》的算法入门的活用递推里面，
元素是不重复的，所以大于，大于等于，小于，小于等于这些关系，都具有传递性。
但是有重复元素的话，就只有大于等于和小于等于这两个关系有传递性了，而小于
不再具有传递性，所以递推的时候，只能求小于等于当前元素x的值，然后再用一次循环来
修正（在有序序列里面，重复元素可以用不等于相邻元素来检测）；比如说从小于等于的正确率，
也就是小于等于x，并且r==0的元素个数，修正为小于x并且r==0的元素个数。这是可行的。
*/

struct Node {
    int y, r;
};

#define MAXN 100005

Node node[MAXN];
int ge[MAXN];  // 大于等于x并且r==1的个数。
int le[MAXN];  // 小于等于x并且r==0的个数。

int M;

// 要从大到小。因为相同的正确率要取最大的y。
bool cmp(Node a, Node b) {
    return a.y > b.y;
}

void Print(int a[]) {
    for (int i = 0; i < M; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
不知道这道题用常规方法能不能100分。
用N平方超时，仅有70分。
*/
void Solve2() {
    int maxval = -1;
    int ans;

    for (int i = 0; i < M; ++i) {
        // 把每个y作为参数。
        int tot = 0;  // 正确率。
        int the = node[i].y;
        for (int j = 0; j < M; ++j) {
            int pred = node[j].y >= the;  // 预测函数。
            if (pred == node[j].r) { ++tot; }
        }
        //		printf("y %d tot %d\n", the, tot);
        if (tot > maxval || (tot == maxval && the > ans)) {
            maxval = tot;
            ans = the;
        }
    }
    printf("%d\n", ans);
}

int main(int argc, char** argv) {
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &node[i].y, &node[i].r);
    }
    // 常规方法。
    Solve2();
    return 0;

    sort(node, node + M, cmp);

    /*
    对每个x，求大于等于x并且r==1的个数。
    */
    for (int i = 0; i < M; ++i) {
        if (i != 0) {
            // 有前驱，继承。
            ge[i] = ge[i - 1];
        }
        if (node[i].r) { ++ge[i]; }
    }
    //	Print(ge);

    /*
    注意，必须要用小于等于关系才能递推正确。
    即，和gt一样的逻辑，计算小于等于x并且r==0的个数 。
    */
    for (int i = M - 1; i >= 0; --i) {
        if (i != M - 1) { le[i] = le[i + 1]; }
        if (!node[i].r) { ++le[i]; }
    }
    //	Print(le);

    /*
    还需要一个循环计算正确率。
    因为le的数据还不符合要求。
    */
    int x = le[M - 1];
    for (int i = M - 2; i >= 0; --i) {
        if (node[i].y != node[i + 1].y) {
            // 这里的正确率是小于的正确率。
            // yi > yi+1, 且 le[i+1] 表示小于等于yi+1的正确率，
            //  所以小于yi的正确率就是le[i+1].
            // 否则保持正确率不变，因为yi==yi+1，相同元素正确率相同。
            x = le[i + 1];
        }
        ge[i] += x;
    }
    //	Print(ge);

    int maxval = -1;
    int ans;
    for (int i = 0; i < M; ++i) {
        int rate = ge[i];
        if (rate > maxval) {
            maxval = rate;
            ans = node[i].y;
        }
    }

    //	printf("max %d\n", maxval);
    printf("%d\n", ans);

    return 0;
}
