#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100010

int main(int argc, char* argv[]) {
    int n, i, id, val;
    int vals[MAXN];

    memset(vals, 0, sizeof(vals));
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d%d", &id, &val);
        vals[id] += val;
    }

    val = -1;
    id = 1;
    for (i = 1; i <= n; ++i) {
        if (vals[i] > val) {
            val = vals[i];
            id = i;
        }
    }

    assert(id > 0);
    printf("%d %d\n", id, val);
    return 0;
}
