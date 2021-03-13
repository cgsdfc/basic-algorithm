#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 105
// 经过打表，算得x=27时，最大可到4616.
/*
注意到输入数列的元素以100为上限，因此计算过程出现大于100的数，
完全可以忽略，并且后面的查询也不会访问到超过100的数。
*/ 
#define MAXM (4616 + 1)

int hashtable[MAXN];
int a[MAXN];

// 根据规则推导出能被x覆盖的数，记录在hashtable中。 
int Fill(int x) {
	// 已经算过了。 
	if (hashtable[x]) return;
	while (x != 1) {
		if (x % 2) {
			x = (3*x+1) / 2;
		} else {
			x /= 2;
		}
		/*
		hashtable记录1-100的数是否有被输入序列里的元素覆盖的，
		如果输入的数能覆盖100以上的数，我们不关心。
		*/ 
		if (x <= 100) {
			hashtable[x]=1;
		}
	}
}

// 关键数从大到小排列。 
int CMP(const void*_a, const void*_b) {
	return *(int*)_b - *(int*)_a;
}

int main(int argc, char *argv[]) {
	int N;
	int i;
	int num;
	
	scanf("%d",&N);
	for (i=0;i<N;++i) {
		scanf("%d",&a[i]);
		Fill(a[i]);
	}
	num=0;
	for (i=0;i<N;++i) {
		if (!hashtable[a[i]]) {
			a[num++]=a[i];
		}
	}
	qsort(a, num, sizeof(int), CMP);
	for (i=0;i<num;++i) {
		printf("%d%s", a[i], i==num-1?"\n":" ");
	}
	
	return 0;
}
