#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
加速任意子序列[i,j]之间累加和的方法：
以O(n)时间，计算sum数组，其中：
sum[0]=0
sum[1]=a[1]
sum[i]=sum[i-1]+a[i], i>0
则Sum(a, i, j)=sum[j]-sum[i-1], j!=i,i!=0
Sum(a, 0, i)=sum[
*/

#define MAXN 100005

int S[MAXN];

/*
注意，i的下标从1开始。
*/ 
int Get(int i, int j) {
	return S[j]-S[i-1];
}

/*
i=left, 从left到right二分找j，Sum(i,j)=M。
*/ 
int Search(int left, int right, int M) {
	int i=left;
	int mid;
	int sum;
	while (left <= right) {
		mid=(left+right)/2;
		sum=Get(i, mid);
		if (sum == M) {
			return mid;
		} else if (sum > M) {
			right=mid-1;
		} else {
			left=mid+1;
		}
	}
	return -1;
}

/*
i=left，从left到right二分找j，M的上界。
*/ 
int Search2(int left, int right, int M) {
	int i=left;
	int mid;
	int sum;
	while (left < right) {
		mid=(left+right)/2;
		sum=Get(i, mid);
//		printf("left %d right %d mid %d sum %d\n", left, right, mid, sum);
		
		if (sum >= M) {
			right=mid;
		} else {
			left=mid+1;
		}
	}
	return left;
}

const int inf=1e8 + 1;

/*
先找有解情况，在解决无解情况。
*/ 
void Solve1(int N, int M) {
	int has;
	int min;
	int i;
	
	/*
	如果有[i,j]，满足S(i,j)==M，则输出所有解，
	否则就找上界，输出所有上界。
	*/
	has=0; // 无解 
	for (i=1;i<=N;++i) {
		// 在合法范围找j。 
		int j=Search(i, N, M);
		if (j != -1) {
			printf("%d-%d\n", i, j);
			has=1;
		}
	}
	
//	printf("has %d\n", has);
	
	if (has) return 0; // 有解。
	
	min=inf;
	for (i=1;i<=N;++i) {
		int j=Search2(i, N+1, M);
//		printf("i %d j %d\n", i, j);
		
		if (j != N+1) {
			int sum=Get(i, j);
			if (sum < min) {
				min=sum; // 先求出上界。 
			}
//			printf("%d-%d\n", i, j);
		}
	}
	// 再把上界找出来。 
	for (i=1;i<=N;++i) {
		// 在合法范围找j。 
		int j=Search(i, N, min);
		if (j != -1) {
			printf("%d-%d\n", i, j);
		}
	}	
}

/*
有解和无解情况合为一体。
先求S，满足：
S=M，如果有解；
S=upper-bound(M)，即满足题目中要求的这样一个和。

然后再次搜索，找出所有满足等于S的i，j。
*/ 
void Solve2(int N, int M) {
	int S=inf;
	int i;
	for (i=1;i<=N;++i) {
		int j=Search2(i, N+1, M);
		if (M == Get(i, j-1)) {
			S=M;
			break; // 有解情况。 
		}
		if (j != N+1) {
			// 上界位于S数组内。
			int sum=Get(i, j);
			if (sum < S) {
				// 找到了更小的上界。
				// 因为i不同的各个序列所得的上界不同，还要取最小值。
				S=sum; 
			} 
		}
	}
	// 现在S就是输出的子序列的和，只要用binarySearch或者upper-bound再搜索一次即可。
	for (i=1;i<=N;++i) {
		int j=Search(i, N, S);
		if (j != -1) {
			printf("%d-%d\n", i, j);
		}
	} 
}

int main(int argc, char *argv[]) {
	int N;
	int M;
	int i;
	int sum=0;

	freopen("./in.txt","r",stdin);
	
	scanf("%d%d", &N, &M);
	for (i=0;i<N;++i) {
		int x;
		
		S[i]=sum;
		scanf("%d", &x);
		sum += x;
	}
	/*
	注意，这里是关键，因为S的元素为N+1，而上面的循环N次。
	*/ 
	S[N]=sum;
	
	Solve2(N, M);

	return 0;
}
