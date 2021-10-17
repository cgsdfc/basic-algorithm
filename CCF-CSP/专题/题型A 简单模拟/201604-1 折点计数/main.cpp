#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
#define MAXN 1005

int a[MAXN];
int N;
int ans;

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < N - 1; ++i) {
        if (a[i - 1] < a[i] && a[i] > a[i + 1]) {
            ++ans;
        } else if (a[i - 1] > a[i] && a[i] < a[i + 1]) {
            ++ans;
        }
    }
    printf("%d\n", ans);

    return 0;
}
