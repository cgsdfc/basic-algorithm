#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int Max(int a, int b) {
	return a > b ? a : b;
}

int CrossSum(int a[], int low, int mid, int hi) {
	int sum, lowmax, himax;
	int i;
	
	sum=0;
	lowmax=0;
	for (i=mid;i>=low;--i) {
		sum+=a[i];
		if (sum>lowmax) {
			lowmax=sum;
		}
	}
	sum=0;
	himax=0;
	for (i=mid+1;i<=hi;++i) {
		sum+=a[i];
		if (sum>himax) {
			himax=sum;
		}
	}
	return lowmax+himax;
}

int MaxSum(int a[], int low, int hi) {
	int mid, lowmax, himax;
	int cross;
	int i;
	int res;
	
//	printf("low=%d, hi=%d, ", low, hi);
//	for (i=low;i<=hi;++i) {
//		printf("%d ", a[i]);
//	}
	
	if (low == hi) {
		res = Max(a[low], 0);
//		printf("res=%d\n", res);
		return res;
	}
	
	assert(low < hi);
	mid=(low+hi)/2;
	lowmax=MaxSum(a, low, mid);
	himax=MaxSum(a, mid+1, hi);
	cross=CrossSum(a, low, mid, hi);
	res= Max(cross, Max(lowmax, himax));
	
//	printf("lowmax=%d, himax=%d, cross=%d, res=%d", lowmax, himax, cross, res);
//	printf("\n");
		
	return res;
}

#define MAXN 100

int main(int argc, char *argv[]) {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	
	int n;
	int A[MAXN];
	int i;
	int res;
	
	scanf("%d", &n);
	for (i=0;i<n;++i) {
		scanf("%d", &A[i]);
	}
	res=MaxSum(A, 0, n-1);
	printf("%d", res);
	
	return 0;
}

