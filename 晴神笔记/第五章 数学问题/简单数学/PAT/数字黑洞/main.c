#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int INC(const void* a, const void* b) {
    return *(char*) a - *(char*) b;
}

int DEC(const void* a, const void* b) {
    return *(char*) b - *(char*) a;
}

int main(int argc, char* argv[]) {
    int N;
    char buf[10];

    scanf("%d", &N);
    while (1) {
        int min, max;
        int len;

        sprintf(buf, "%04d", N);
        len = strlen(buf);
        // ∑«µ›‘ˆ≈≈–Ú°£
        qsort(buf, len, sizeof(char), DEC);
        sscanf(buf, "%d", &max);
        // ∑«µ›ºı≈≈–Ú°£
        qsort(buf, len, sizeof(char), INC);
        sscanf(buf, "%d", &min);
        N = max - min;
        printf("%04d - %04d = %04d\n", max, min, N);
        if (N == 0 || N == 6174) break;
    }

    return 0;
}
