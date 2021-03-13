#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20

// -1000000 9

/*
三个数字一组用逗号分隔输出val。

如-1000
-1,000
如200
200 
*/ 

/* 第二种方法 
从高位到低位，先输出前缀，再每三个一组输出逗号和数字。
前缀的选取使得后缀长度必定是3的倍数。 
*/ 
void Method2(int val) {
	int n;
	int i;
	
	// 用于获取val的各位数字。 
	char buf[MAXN];
	int len;
	
	if (val < 0) {
		putchar('-');
		val=-val;
	}
	do {
		buf[len++]='0'+val%10;
		val/=10;
	} while (val);
	
	// n是第一组数字，可能不满三个，输出了第一组后，剩下的每组数字的
	// 输出更有规律，就是先输出逗号，再输出一组。 
	n=len%3;
	if (!n) n=3;
	// 先输出前n个高位数字。 
	for (i=0;i<n;++i) {
		putchar(buf[len-i-1]);
	}
	// 剩下的数字，每三个一组，每组前面输出逗号。 
	for (i=n;i<len;++i) {
		if ((i-n) % 3 == 0) putchar(',');
		putchar(buf[len-i-1]);
	}

}

/*
第一种方法
在得到各位数字的同时，每三位插入一个逗号。
因为是从低位到高位插入逗号，符合分组的原则，固然正确。 
完成后，检查数组尾部，若是一个逗号，则删除，因为最高位前面不应有逗号。
*/ 
void Method1(int sum) {
	char buf[MAXN];
	int len=0;
	int i=0;
	
	if (sum < 0) {
		putchar('-');
		sum = -sum;
	}
	i=1;
	do {
		// 转换成字符。 
		buf[len++]=sum % 10 + '0';
		// 每隔三个数字，输出一个逗号，若最后发现最后一个字符是逗号则删之。 
		if (i % 3 == 0) {
			buf[len++]=',';
		}
		++i;
		sum/=10;
	} while (sum);
	if (buf[len-1] == ',') {
		--len;
	}
	for (i=len-1;i>=0;--i) {
		putchar(buf[i]);
	}
}

int main(int argc, char *argv[]) {
	int a,b,sum;

	scanf("%d%d",&a,&b);
	sum=a+b;
	
	Method2(sum);
	putchar('\n');
	
	return 0;
}
