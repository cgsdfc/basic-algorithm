#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
��һ��������K�����С�

һ��������һ������ָ����������a[i]Ԫ�ر�ʾ��ԭ����iԪ�طŵ�a[i]-1����
��a��Ԫ���±��1��ʼ��
�����������Ϊ�˿��ơ� 
*/

#define MAXN 54

char Color(int i) {
	char color[]="SHCDJ";
	int k=i/13;
	
	assert(0<=k&&k<strlen(color));
	return color[k];	
}

int main(int argc, char *argv[]) {
	int k;
	int a[MAXN];
	int b[MAXN];
	int ord[MAXN];
	int i;
	
	for (i=0;i<MAXN;++i) {
		a[i]=i;
	}
	
	scanf("%d",&k);
	for (i=0;i<MAXN;++i) {
		scanf("%d", &ord[i]);
	}
	while (k--) {
		for (i=0; i<MAXN; ++i) {
			b[ord[i]-1]=a[i];
		}
		memcpy(a, b, sizeof(a));
	}
	for (i=0; i< MAXN; ++i) {
		int x=a[i];
		printf("%c%d", Color(x), (x % 13)+1);
		printf("%s", i==MAXN-1 ? "\n": " ");
	}
	return 0;
}

