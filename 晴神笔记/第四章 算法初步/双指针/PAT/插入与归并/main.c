#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*

*/

#define MAXN 105

int a[MAXN];
int half[MAXN];
/*
必须把原数列的副本保留一份，每次恢复到a中，而a则被排序修改。
*/ 
int b[MAXN];

void Read(int a[], int n) {
	int i;
	for (i=0;i<n;++i) {
		scanf("%d", &a[i]);
	}
}

/*
一边排序，一边检测序列是否变成half，如果是，进行多一轮后返回1.
否则返回0.
*/ 
int InsertSort(int n) {
	int flag=0;
	int i;
	
	memcpy(a, b, sizeof(a[0])*n);
	// n-1趟 
	for (i=1; i<n; ++i) {
		int j=i;
		int temp=a[i];
		while (j>0&&a[j-1]>temp) {
			a[j]=a[j-1];
			j--;
		}
		a[j]=temp;
		
//		Print(a, n);
		
		// 一趟结束。
		if (flag == 0 && memcmp(a, half, sizeof(a[0])*n) == 0) {
			flag=1;
			continue;
		}
		if (flag) break;
	}
	return flag;
}

void Merge(int L1, int R1, int L2, int R2) {
	int n=0;
	int i=L1;
	int j=L2;
	int temp[MAXN];
	
	while (i<=R1 && j<=R2) {
		if (a[i] <= a[j]) {
			temp[n++]=a[i++];
		} else {
			temp[n++]=a[j++];
		}
	}
	while (i<=R1) {
		temp[n++]=a[i++];
	}
	while (j<=R2) {
		temp[n++]=a[j++];
	}
	for (i=0;i<n;++i) {
		a[L1+i]=temp[i];
	}
}

#define MIN(a, b) ((a)<(b)?(a):(b))

int MergeSort(int n) {
	int flag=0;
	int step;
	
	memcpy(a, b, sizeof(a[0])*n);
	for (step=2; step/2<=n; step*=2) {
		int i;
		for (i=0;i<n;i+=step) {
			int mid=i+step/2 - 1;
			if (mid+1<n) {
				Merge(i, mid, mid+1, MIN(i+step-1, n-1));
			}
		}
		if (flag == 0 && memcmp(a, half, sizeof(a[0])*n) == 0) {
			flag=1;
			continue;
		}
		if (flag) break;
	}
	return flag;
}

void Print(int a[], int N) {
	int i;
	for (i=0;i<N;++i) {
		printf("%d%s", a[i], i==N-1?"\n":" ");
	}
}

int main(int argc, char *argv[]) {
	int N;
	int i;
	
	scanf("%d", &N);
	Read(b, N);
	Read(half, N);
	
//	InsertSort(N);
//	Print(a, N);
//	return 0;
	
	if (MergeSort(N)) {
		puts("Merge Sort");
	} else if (InsertSort(N)) {
		puts("Insertion Sort");
	}
	Print(a, N);
	
	return 0;
}
