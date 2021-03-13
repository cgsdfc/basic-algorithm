#include <stdio.h>
#include <stdlib.h>
#include <math.h> // sqrt
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
素数模板
1. 素数判定 sqrt(n)
2. 素数表生成
	1. 利用素数判定 n*sqrt(n) 
	2. 筛法 nloglogn
*/

int IsPrime(int n) {
	int i;
	int up;
	
	if (n<=1) return 0;
	// 从2到floor(sqrt(n))
	up=(int)sqrt(n);
	for (i=2;i<=up;++i) {
		// 整除则合数 
		if (n % i == 0) return 0;
	}
	return 1;
} 

/*
素数表的大小，
素数表表示数字i是否为素数。属于哈希表性质的。
所以上限必须比要判定的数大1. 因为大小为Size的表，
下标可用的只有Size-1. 如果要找1--100的素数，则素数表的大小
至少为101. 

对于筛法来说，素数表是必须的，因为必须标记当前已知的素数，
才能晒掉后面的合数。
对于素数判定法，则不一定要保存素数表。 
*/
 
#define MAXN 101

/*
素数表p[i]为0，表示它是素数（0，1除外）；
为1表示它是合数。
另外还需要prime数组，递增的保存素数。 
*/
int p[MAXN];
int prime[MAXN];
int pNum; // prime的Size。 

/*
筛法打素数表。
这是最简版，找出1--MAXN-1的全部素数，记录在p和prime数组里。
变体如下：
1. 找前N个素数，即素数个数累计达到N时结束算法。
2. 找1--N中的全部素数，把筛法的上界从MAXN改为N+1即可。
或者，不要改算法，而是把MAXN设置为N的上界，算出全部来。 
注意不要越界。
*/ 
void FindPrime(void) {
	int i;
	/*
	为了防止数组越界，用MAXN来控制循环，
	在循环内部，用pNum和n来控制提前退出循环。
	这样即使n不小心越界了，也不会数组越界。
	注意这种写法。 
	*/ 
	// 从2开始，2是第一个素数，1不是。 
	for (i=2;i<MAXN;++i) {
		int j;
		if (p[i] == 0) {
			// 找到一个素数。
			prime[pNum++]=i;
			// 筛掉后面的合数。
			for (j=i+i;j<MAXN;j+=i) {
				/*
				注意这个循环的写法，是筛掉i以后，MAXN之前的全部i的倍数。
				因此就是2i，3i，4i，等等。注意i是不能筛掉的，所以从2i开始。
				*/
				p[j]=1; 
			} 
		}
	}
}

/*
素数判定打素数表。
注意p[i]=true表示i是素数。
*/ 
void FindPrime2(void) {
	int i;
	for (i=1; i<MAXN; ++i) {
		if (IsPrime(i)) {
			p[i]=1;
			prime[pNum++]=i;
		}
	}
}

int main(int argc, char *argv[]) {
	int i;
	FindPrime();
	for (i=0;i<pNum;++i) {
		printf("%d ", prime[i]);
	}
	
	return 0;
}
