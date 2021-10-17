#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 5005

int A[MAXN];
int N;

int Rand(int a, int b) {
    return a;
    // return round(rand()/(double)RAND_MAX * (b-a) + a);
}

int Partition(int a[], int left, int right) {
    int p = Rand(left, right);
    int temp = a[p];
    a[p] = a[left];
    a[left] = temp;

    while (left < right) {
        while (left < right && a[right] >= temp)
            --right;
        a[left] = a[right];
        while (left < right && a[left] < temp)
            ++left;
        a[right] = a[left];
    }
    a[left] = temp;
    return left;
}

void QuickSort(int a[], int left, int right) {
    if (left < right) {
        int mid = Partition(a, left, right);
        QuickSort(a, left, mid - 1);
        QuickSort(a, mid + 1, right);
    }
}

int main(int argc, char* argv[]) {
    //	srand((unsigned)time(NULL));

    while (scanf("%d", &N) != EOF) {
        int i;
        for (i = 0; i < N; ++i) {
            scanf("%d", &A[i]);
        }
        QuickSort(A, 0, N - 1);
        for (i = 0; i < N; ++i) {
            printf("%d\n", A[i]);
        }
    }

    return 0;
}
