#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef long long LL;

#define MAXN 20

LL func(char s[], int n, char x) {
    int i = 0;
    char buf[MAXN];
    int k = 0;
    LL res;

    for (i = 0; i < n; ++i) {
        if (s[i] == x) { buf[k++] = x; }
    }
    buf[k] = 0;
    sscanf(buf, "%lld", &res);
    return res;
}

int main(int argc, char* argv[]) {
    char a[MAXN], b[MAXN];
    char da[2], db[2];
    LL pa, pb, res;

    scanf("%s%s%s%s", a, da, b, db);
    pa = func(a, strlen(a), da[0]);
    pb = func(b, strlen(b), db[0]);
    res = pa + pb;
    printf("%lld\n", res);
    return 0;
}
