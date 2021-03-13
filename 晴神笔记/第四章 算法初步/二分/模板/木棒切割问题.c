#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
木棒切割问题
给出N条木棒，长度均已知，切割它们来得到至少K段长度相等的木棒，
长度必须是整数，问这些长度相等的木棒最长能有多长？
注意切割时，可以抛弃一些长度不足的木棒。

设相等的长度为L，切割后的木棒为K段。注意到，L越大，K必定越小。
于是本题就是求满足k大等于K的最大的L，若将L从小到大排序，则求
满足k大于等于K的最后一个L，转化为k小于K的第一个L，就是一个二分问题了。
给定L，可以计算出k，L的最小值为1，最大值为所有木棒长度的最大值。 
*/

#define MAXN 100

int a[MAXN]; // 木棒原始长度。

// 给定L，求K。 
int GetK(int n, int L) {
	int ans=0;
	int i;
	for (i=0;i<n;++i) {
		ans += a[i] / L;
	}
	return ans;
}

// 找出第一个使得k小于K的L。 
int BSearch(int left, int right, int N, int K) {
	int mid;
	while (left < right) {
		mid=(left+right)/2;
		int k=GetK(N, mid);
		if (k < K) {
			// 满足了条件，但是要使L减少（因为是第一个L）所以去左边区间。 
			right=mid;
		} else {
			// 还不满足条件，要使得L增大，去右边区间。 
			left=mid+1;
		}
	}
}

void CutRodMain(void) {
	int N;
	int K;
	int i;
	int max=0;
	int ans;
//	int left,right;
	
	scanf("%d%d", &N, &K);
	for (i=0;i<N;++i) {
		scanf("%d",&a[i]);
		if (a[i] > max) {
			max=a[i];
		}
	}
	ans=BSearch(1, max, N, K);
	printf("%d\n", ans-1);
}

