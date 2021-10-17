#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
找到区间a，b范围内的所有素数等差数列，每行输出一个数列。
等差数列要求每个元素是素数，并且元素个数大于等于3.
*/

const int MAXN = 1e6 + 5;
bool p[MAXN];

struct {
    int data[MAXN];
    int len;
} prime;

int a, b;

/*
先把a，b之内的全部素数找出来，然后双指针扫描。
*/
void FindPrime() {
    prime.len = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (!p[i]) {
            // i为素数。
            if (a <= i && i <= b) { prime.data[prime.len++] = i; }
            for (int j = 2 * i; j < MAXN; j += i) {
                p[j] = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    scanf("%d%d", &a, &b);
    FindPrime();
    //	for (int i=0;i<prime.len;++i) {
    //		printf("%d ", prime.data[i]);
    //	}
    //	puts("");

    /*
    每次取当前两个素数，计算公差，然后向后找满足公差的连续素数。
    */
    int i = 0;
    while (i + 2 < prime.len) {
        int A = prime.data[i];
        int B = prime.data[i + 1];
        int d = B - A;  //公差。
        int j = i + 2;  // 从第三个数开始测试。
        // 注意这里j的设置。
        while (j < prime.len && prime.data[j] - prime.data[j - 1] == d) {
            ++j;
        }
        int len = j - i;
        if (len >= 3) {
            //			printf("%d\n",d);
            for (int k = i; k < j; ++k) {
                printf("%d%s", prime.data[k], k == j - 1 ? "\n" : " ");
            }
            // j和前面的数字的公差不一致，j可能成为新的数列头。
            i = j;
        } else {
            // B-A != C-B，现在尝试以B为数列头。
            ++i;
        }
        /*
        注意，如果找到了超过3个的数字，则要跳过这些数字，从后找，否则就会重复；
        如果不足三个，就从B开始找，就是跳过1个数字。
        */
    }

    return 0;
}
