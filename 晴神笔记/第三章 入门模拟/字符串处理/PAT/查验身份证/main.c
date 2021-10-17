#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 20

/*
Z£º0 1 2 3 4 5 6 7 8 9 10
M£º1 0 X 9 8 7 6 5 4 3 2
*/

const int W[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
const char Map[11] = "10X98765432";

int Valid(char id[], int n) {
    int sum = 0;
    int i;
    int z, m;

    for (i = 0; i < 17; ++i) {
        if (!isdigit(id[i])) return 0;
        sum += W[i] * (id[i] - '0');
    }
    z = sum % 11;
    m = Map[z];
    return m == id[17];
}

int main(int argc, char* argv[]) {
    char id[MAXN];
    int n;
    int invalid = 0;

    scanf("%d", &n);
    while (n--) {
        scanf("%s", id);
        if (!Valid(id, strlen(id))) {
            puts(id);
            ++invalid;
        }
    }
    if (!invalid) { puts("All passed"); }
    return 0;
}
