#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Sort(int a[], int n) {
    int minpos, minval;
    int i;
    int j;

    for (i = 0; i < n; ++i) {
        minval = a[i];
        minpos = i;
        for (j = i; j < n; ++j) {
            if (a[j] < minval) {
                minval = a[j];
                minpos = j;
            }
        }
        a[minpos] = a[i];
        a[i] = minval;
    }
}

void GenData(int n) {
    int i;
    FILE* f = fopen("./in.txt", "w");
    fprintf(f, "%d\n", n);
    for (i = 0; i < n; ++i) {
        fprintf(f, "%d ", rand());
    }
    fclose(f);
}

#define MAXN 100

int main(int argc, char* argv[]) {
    int a[MAXN];
    int n;
    int i;

    GenData(10);
    freopen("./in.txt", "r", stdin);
    freopen("./out.txt", "w", stdout);

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    Sort(a, n);
    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    return 0;
}
