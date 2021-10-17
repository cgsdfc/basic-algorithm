#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXK 100

int main(int argc, char* argv[]) {
    int n;

    //	freopen("./in.txt","r",stdin);

    while (scanf("%d", &n) != EOF) {
        // n个数组
        while (n--) {
            int k;
            int a[MAXK];
            int ans[MAXK];
            int num = 0;
            int i;

            scanf("%d", &k);
            assert(0 <= k && k <= 100);
            if (k == 0) break;

            for (i = 0; i < k; ++i) {
                scanf("%d", &a[i]);
            }
            for (i = 0; i < k; ++i) {
                if (i == 0) {
                    if (a[0] != a[1]) { ans[num++] = i; }
                } else if (i == k - 1) {
                    if (a[k - 1] != a[k - 2]) { ans[num++] = i; }
                } else {
                    int prev = a[i - 1];
                    int next = a[i + 1];
                    int x = a[i];
                    int cond1 = (x - prev) * (x - next) > 0;
                    int cond2 = (x > prev && x > next || x < prev && x < next);
                    assert(cond1 == cond2);

                    /*
                    注意，这两个条件并不等价：
                    1. (x-n)(x-p)>0
                    2. x>p&&x>n || x<p&&x<n

                    但是从数学上是等价的，不知道为什么。。
                    */
                    //					if ((x-next) * (x-prev) > 0) {
                    if (((x - prev) * (x - next)) > 0 || x - prev < 0 && x - next < 0)
                    /*(x>prev&&x>next || x<prev&&x<next)*/
                    /*(a[i]>a[i-1]&&a[i]>a[i+1] || a[i]<a[i-1]&&a[i]<a[i+1])*/ {
                        ans[num++] = i;
                    }
                }
            }
            if (num) {
                for (i = 0; i < num; ++i) {
                    printf("%d%s", ans[i], i == num - 1 ? "\n" : " ");
                }
            }
        }
    }

    return 0;
}
