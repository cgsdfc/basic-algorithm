#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
关于d进制的数最长是多少。
当d==2时，同一个数的位数最多，（因为一个位能表示的信息最少）。
所以以d==2来估计即可得到上限。

输入样例：
123 456 8
输出样例：
1103
*/

#define MAXN 35
 
int main(int argc, char *argv[]) {
	int a,b,d;
	int c;
	int ans[MAXN];
	int k;
	
	scanf("%d%d%d", &a, &b, &d);
	c=a+b;
	k=0;
	do {
		ans[k++]=c % d;
		c /= d;
	} while (c);
	
	while (k--) {
		printf("%d", ans[k]);
	}
	putchar('\n');
	return 0;
}
