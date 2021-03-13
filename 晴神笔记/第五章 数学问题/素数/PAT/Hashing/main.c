#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int IsPrime(int n) {
	int i,up;
	
	if (n<=1) return 0;
	up=sqrt(n);
	for (i=2;i<=up;++i) {
		if (n%i==0) return 0;
	}
	return 1;
}

int NextPrime(int n) {
	while (!IsPrime(n)) {
		++n;
	}
	return n;
}

void Test(void) {
	int n;
	scanf("%d",&n);
	printf("%d %d", n, NextPrime(n));
}

#define MAXN (10000+10)

int a[MAXN]; // 模拟哈希表 

/*
插入元素x，返回插入后的下标，如果无法插入，返回-1.
*/ 
int Insert(int x, int size) {
	int key=x%size;
	int i;
	for (i=0;i<size;++i) {
		int pos=(key+i*i)%size;
		if (!a[pos]) {
			a[pos]=1;
			return pos;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
//	while (1) Test();
	int Size, N;
	
	scanf("%d%d",&Size,&N);
	Size=NextPrime(Size);
	while (N--) {
		int x;
		int ans;
		
		scanf("%d",&x);
		ans=Insert(x, Size);
		if (ans != -1) {
			printf("%d", ans);
		} else {
			printf("-");
		}
		printf("%s", N==0?"\n":" ");
	}
	
	return 0;
}
