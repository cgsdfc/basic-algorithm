#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100005

/*
虽然p还有N个整数都是10e9，但是只有mp相乘的时候，才可能越界，
所以其他地方用int即可，相乘时如果越界则大于任何的int。
*/
int a[MAXN];

int CMP(const void* _a, const void* _b) {
    // 从小到大整数排序。
    return *(int*) _a - *(int*) _b;
}

// M<=m*p.
int LessEq(int M, int m, int p) {
    int res = m * p;
    return res < 0 || M <= res;
}

int main(int argc, char* argv[]) {
    int N, p;
    int i;
    int m, M;
    int ans = 0;  // 序列最大长度。

    freopen("./in.txt", "r", stdin);

    scanf("%d%d", &N, &p);
    for (i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    qsort(a, N, sizeof(int), CMP);
    /*
    取定m，则M取满足M小于等于mp的最大元素，使得一个序列的元素最多。
    当m从整个序列的最小值依次增大时，因为mp增大，所以M至少不减少。
    当M增大的位数，即M的位号增大的数量，大于m增大的位数时，就得到了
    更大的序列。但是M到达最后一个元素时，M无法再增大了，此时得出的最大值就是
    答案。

    先排序，logn。然后把m初始为0号元素，M初始为满足条件的最大元素。
    之后不断增大m，更新M，直到M到达最后元素。这个过程O(n)。总的复杂度为nlogn。
    */
    /*
    这是two-pointer的做法，就是用m和M两个指针，不断向后更新。
    本题之所以归在二分法，是因为查找M可以用二分法查找，即查找m和N之间第一个大于mp的数，
    这就是mp的upper-bound。
    */

    m = 0;
    for (i = N - 1; i >= 0; --i) {
        if (LessEq(a[i], a[m], p)) {
            M = i;
            break;
        }
    }
    ans = M - m + 1;

    //	printf("%d\n", ans);

    while (M <= N - 1 && m <= N - 1) {
        int len;

        ++m;
        if (m > M) break;

        for (i = M; i < N && LessEq(a[i], a[m], p); ++i)
            ;
        M = i - 1;
        len = M - m + 1;

        //		printf("m %d M %d len %d\n", m,M,len);

        if (len > ans) { ans = len; }
    }

    printf("%d\n", ans);

    return 0;
}
