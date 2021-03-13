#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
注意，题目这种相加的方式，并不是简单的100个10e10的数相加，
设第一个数是x，则第二个数接近2*x，第三是4*x，所以第100个数，
是2^99 x，是非常大的。2^99约等于10e30，所以最大的数可以达到10e40. 
考虑到2*x是保守估计，数组开到100比较好。 

表面上看，这道题好像long long都可以了，但是题目的计算方式是随K指数增大的，
而且K是比较大的数（1000），所以必须用高精度才能做。 
*/ 
#define MAXN 100 

typedef struct Big {
	int d[MAXN];
	int len;
} Big;

/*
a和a的逆序数相加。
*/ 
Big Add(Big a) {
	int i;
	Big c={};
	int carry=0;
	
	for (i=0;i<a.len;++i) {
		int temp=a.d[i]+a.d[a.len-1-i]+carry;
		c.d[c.len++]=temp%10;
		carry=temp/10;
	}
	if (carry) {
		c.d[c.len++]=carry;
	}
	return c;
}

// 判定a是否是回文数。 
int Judge(Big a) {
	int i;
	for (i=0;i<a.len/2;++i) {
		if (a.d[i] != a.d[a.len-1-i]) {
			return 0;
		}
	}
	return 1;
}

Big From(char str[], int len) {
	int i;
	Big c={};
	
	c.len=len;
	for (i=0;i<len;++i) {
		c.d[i]=str[len-1-i]-'0';
	}
	return c;
}

void Print(Big a) {
	int i;
	for (i=a.len-1;i>=0;--i) {
		printf("%d", a.d[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char str[MAXN];
	Big a;
	int K;
	int i;
	
	scanf("%s%d", str, &K);
	a=From(str, strlen(str));
	if (Judge(a)) {
		// 特判：输入就是回文数。
		Print(a);
		printf("0\n");
		return 0;
	}
	for (i=0;i<K&&!Judge(a);++i) {
//		Print(a);
		a=Add(a);
	}
	Print(a);
	printf("%d\n", i);
	
	return 0;
}
