#include <stdio.h>
#include <stdlib.h>

/*
在快速排序的核心子程序 RandPartition 的基础上得来的 RandSelect 函数，
作用是求出第K大的元素X，并且把序列原地分为两部分：左边小于等于X，右边大于X。
效率较高，平均O(n)。

注：
第K大的元素X，表示连同X和X前面的元素，一共有K个元素。
也是排序好的序列中，第K个元素（1-base）。 

核心思想：
先随机选择主元p，用 RandPartition 把序列划分。
根据主元在划分后的序列是第几大，记为M：
1. 如果M=K，则划分完毕，p就是所求元素。
2. 如果M<K，则X在右边序列，并且变成第M-K大，递归进行。
3. 如果M>K，则X在左边序列，并且是第K大，递归进行。
4. 如果序列只有一个元素，则这个唯一的元素就是X，不管K是多少。 
*/

int RandPartition(int A[], int left, int right) {
	int p;
	int temp;
	
	/*
	注意主元是在区间中随机选择的一个数，用来比较其他数，并划分区间。
	最后返回的并不是主元的随机选取的下标，而是完成划分后主元所在的位置。
	*/ 
	p=round(rand()*1.0/RAND_MAX*(right-left)+left);
	temp=A[p];
	A[p]=A[left];
	A[left]=temp;
	
	while (left < right) {
		while (left < right && A[right] > temp) --right;
		A[left]=A[right];
		while (left < right && A[left] <= temp) ++left;
		A[right]=A[left];
	}
	A[left]=temp;
	return left;
}

/*
求出a中第K大的数，K应该取1--N，如果K<1，则返回最小数，如果 K>N，则返回最大数。
*/ 
int RandSelect(int A[], int left, int right, int K) {
	int p;
	int M;
	
	if (left == right) {
		return A[left];
	}
	p=RandPartition(A, left, right);
	M=p-left+1;
	if (K == M) {
		return A[p];
	}
	if (K < M) {
		return RandSelect(A, left, p-1, K);
	} else {
		return RandSelect(A, p+1, right, K-M);
	}
}

void TestRandSelect(void) {
	const int A[]={5,12,7,2,9,3};
	const int len=sizeof(A)/sizeof(A[0]);
	int i;
	int ans;
	
	for (i=0;i<len;++i) {
		int K=i+1;
		ans=RandSelect(A, 0, len-1, K);
		printf("K %d ans %d\n", K, ans);
	}
	
	ans=RandSelect(A, 0, len-1, 0);
	printf("ans %d\n", ans);
	ans=RandSelect(A, 0, len-1, len+1);
	printf("ans %d\n", ans);
	
}

