#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
��Ŀ����
���������ַ������Ƚ����ַ����ĳ��ȴ�С��ϵ��

����
�����һ�б�ʾ���������ĸ���m��������m��ÿ�������ַ���A��B���ַ������Ȳ�����50��

���
���m�С������ַ���������������A is equal long to B����A��B���������A is longer than B���������A is shorter than B��

�������� Copy
2
abc xy
bbb ccc
������� Copy
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

