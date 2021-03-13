#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
题目描述
输入两个字符串，比较两字符串的长度大小关系。

输入
输入第一行表示测试用例的个数m，接下来m行每行两个字符串A和B，字符串长度不超过50。

输出
输出m行。若两字符串长度相等则输出A is equal long to B；若A比B长，则输出A is longer than B；否则输出A is shorter than B。

样例输入 Copy
2
abc xy
bbb ccc
样例输出 Copy
abc is longer than xy
bbb is equal long to ccc
*/

#define MAXN 60

int main(int argc, char *argv[]) {
	int m;
	scanf("%d",&m);
	while (m--) {
		char a[MAXN], b[MAXN];
		int cmp;
		
		scanf("%s%s",a,b);
		cmp=strlen(a)-strlen(b);
		if (cmp == 0) {
			printf("%s is equal long to %s\n",a,b);
		} else if (cmp > 0) {
			printf("%s is longer than %s\n", a,b);
		} else {
			printf("%s is shorter than %s\n",a,b);
		}
	}
	return 0;
}

