#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����d���Ƶ�����Ƕ��١�
��d==2ʱ��ͬһ������λ����࣬����Ϊһ��λ�ܱ�ʾ����Ϣ���٣���
������d==2�����Ƽ��ɵõ����ޡ�

����������
123 456 8
���������
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
