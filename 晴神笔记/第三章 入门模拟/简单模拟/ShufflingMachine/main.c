#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
把一个数组做K次排列。

一个排列由一个数组指出，该数组a[i]元素表示把原数组i元素放到a[i]-1处。
即a的元素下标从1开始。
最后把数组输出为扑克牌。 
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

