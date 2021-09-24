#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100005

int *A;
int *Temp;

void Merge(int a[], int L1, int R1, int L2, int R2) {
  int i, j, k;
  i = L1;
  j = L2;
  k = 0;
  while (i <= R1 && j <= R2) {
    if (a[i] < a[j]) {
      Temp[k++] = a[i++];
    } else {
      Temp[k++] = a[j++];
    }
  }
  while (i <= R1) {
    Temp[k++] = a[i++];
  }
  while (j <= R2) {
    Temp[k++] = a[j++];
  }
  for (i = 0; i < k; ++i) {
    a[L1 + i] = Temp[i];
  }
}

void MergeSort(int a[], int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, mid + 1, right);
  }
}

int Min(int a, int b) { return a < b ? a : b; }

void MergeSort2(int a[], int n) {
  int step;
  for (step = 2; step / 2 < n; step *= 2) {
    int i;
    for (i = 0; i < n; i += step) {
      int mid = i + step / 2 - 1;
      if (mid + 1 < n) {
        Merge(a, i, mid, mid + 1, Min(i + step - 1, n - 1));
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int i;
  int n;

  while (scanf("%d", &n) != EOF) {
    A = malloc(sizeof(int) * (n + 5));
    Temp = malloc(sizeof(int) * (n + 5));

    for (i = 0; i < n; ++i) {
      scanf("%d", &A[i]);
    }
    MergeSort2(A, n);
    for (i = 0; i < n; ++i) {
      printf("%d\n", A[i]);
    }
    free(A);
    free(Temp);
  }

  return 0;
}
