#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXM 1005

/*
记录面值为i的数量，
面值集合本质上是多重集。
一个面值不超过500.
*/
int hashtable[510];

// int Min(int a, int b) {
//	return a<b?a:b;
//}

int main(int argc, char* argv[]) {
    int N, M;
    int i;
    int minV1 = MAXM;

    scanf("%d%d", &N, &M);
    for (i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        hashtable[x]++;
    }
    /*
    注意核心逻辑
    区分等分M和不等分M的情况。
    若等分M，则要求同样面值的硬币至少2个。
    若不等分，则要求两个面值的硬币各自至少1个。
    */
    for (i = 1; i <= 500; ++i) {
        int x = i;
        int y = M - x;
        if (y > 500) {
            // 超过面值范围，不可能分割。
            continue;
        }
        if (!hashtable[x] || !hashtable[y]) {
            // 该面值不存在。
            continue;
        }
        if ((x == y && hashtable[x] >= 2) || (x != y && hashtable[x] >= 1 && hashtable[y] >= 1)) {
            // 找到一组解。
            /*
            注意，不需要运用最小值的算法，因为对V1的枚举就是从小到大的，
            只要在第一个可行解处输出V1即可。
            */
            //			int V1=Min(x, y);
            //			if (V1 < minV1) {
            //				minV1=V1;
            //			}
            printf("%d %d\n", x, y);
            return 0;
        }
    }
    puts("No Solution");
    //	if (minV1 == MAXM) {
    //		puts("No Solution");
    //	} else {
    //		printf("%d %d\n", minV1, M-minV1);
    //	}

    return 0;
}
