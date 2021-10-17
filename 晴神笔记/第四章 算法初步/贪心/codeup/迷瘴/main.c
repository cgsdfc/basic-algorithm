#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 105

int P[MAXN];

/*
假设有N种浓度P[1]..P[n]的溶液，体积都是V，
则混合后，体积为nV，浓度为各自浓度的算术平均值。

贪心策略：
V的最大值为全部溶液混合，即nV，最小值为0，即无解。
按浓度从小到大排序，逐一将下一个溶液混入当前溶液，
直到当前浓度大于W，则得到最大体积和相应的浓度。

合理性：
浓度小于等于W的溶液混合，结果的浓度不会超过W，因此多多益善；
浓度大于W的溶液，可能被低浓度的其他溶液拉低至小于W，因此也可以加入。
但如果浓度大于W的溶液过多，则结果会超过W。
因此考虑溶液时应该按照浓度从小到大的顺序。
*/

int CMP(const void* _a, const void* _b) {
    return *(int*) _a - *(int*) _b;
}

int main(int argc, char* argv[]) {
    int C;

    freopen("./in.txt", "r", stdin);

    scanf("%d", &C);
    while (C--) {
        int n, V, W;
        int i;
        double p;
        int v;

        scanf("%d%d%d", &n, &V, &W);
        for (i = 0; i < n; ++i) {
            scanf("%d", &P[i]);
        }
        qsort(P, n, sizeof(int), CMP);
        /*
        无解：最小的浓度都大于W，则无解。
        否则，一定有解。
        */
        if (P[0] > W) {
            puts("0 0.00");
            continue;
        }

        p = P[0];
        v = 1;
        for (i = 1; i < n; ++i) {
            /*
            注意新浓度如果非法，则不应该更新。
            */
            double newp = (i * p + P[i]) / (double) (i + 1);
            if (newp <= W) {
                p = newp;
                ++v;
            } else {
                break;
            }
        }
        /*
        百分数保留两位小数，则乘100后，即保留整数。
        */
        p = round(p);
        printf("%d %.2f\n", v * V, p / 100);
    }

    return 0;
}
