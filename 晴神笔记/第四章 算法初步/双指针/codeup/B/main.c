#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 100005

int A[MAXN];
int Temp[MAXN];

int Min(int a, int b) {
	return a<b?a:b;
}

void Merge(int a[], int L1, int R1, int L2, int R2) {
	int i=L1;
	int j=L2;
	int k=0;
	while (i<=R1&&j<=R2) {
		if (a[i] < a[j]) {
			Temp[k++]=a[i++];
		} else {
			Temp[k++]=a[j++];
		}
	}
	while (i<=R1) {
		Temp[k++]=a[i++];
	}
	while (j<=R2) {
		Temp[k++]=a[j++];
	}
	for (i=0;i<k;++i) {
		a[L1+i]=Temp[i];
	}
}

void MergeSort(int a[], int n) {
	int step;
	for (step=2;step/2<n;step*=2) {
		int i;
		for (i=0;i<n;i+=step) {
			int mid=i+step/2-1;
			if (mid+1<n) {
				Merge(a, i, mid, mid+1, Min(n-1, i+step-1));
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int n;
	
	while (scanf("%d", &n) != EOF) {
		int m;
		int i;
		scanf("%d", &m);
		for (i=0;i<m;++i) {
			scanf("%d", &A[i]);
		}
		MergeSort(A, m);
		for (i=0;i<m;++i) {
			printf("%d\n", A[i]);
		}
	}
	return 0;
}
