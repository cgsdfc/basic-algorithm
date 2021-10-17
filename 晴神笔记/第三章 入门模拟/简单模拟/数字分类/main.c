#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int n;
    int i;
    int a[5] = {};
    int cnt[5] = {};
    int ans = 1;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        switch (x % 5) {
            case 0:
                if (x % 2 == 0) {
                    cnt[0]++;
                    a[0] += x;
                }
                break;
            case 1:
                cnt[1]++;
                a[1] += ans * x;
                ans *= -1;
                break;
            case 2:
                ++cnt[2];
                ++a[2];
                break;
            case 3:
                ++cnt[3];
                a[3] += x;
                break;
            case 4:
                ++cnt[4];
                if (cnt[4] == 1) {
                    a[4] = x;
                } else if (x > a[4]) {
                    a[4] = x;
                }
                break;
        }
    }

    for (i = 0; i < 5; ++i) {
        if (!cnt[i]) {
            printf("N");
        } else if (i == 3) {
            printf("%.1f", a[i] / (double) cnt[i]);
        } else {
            printf("%d", a[i]);
        }
        if (i != 4) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    return 0;
}
