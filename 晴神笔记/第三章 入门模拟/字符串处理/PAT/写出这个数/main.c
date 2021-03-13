#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char Map[10][5]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};

#define MAXN 110

int main(int argc, char *argv[]) {
	int sum=0;
	int i;
	int len;
	char num[MAXN];
	
	gets(num);
	len=strlen(num);
	while (len--) {
		sum+=num[len]-'0';
	}
	sprintf(num, "%d", sum);
	len=strlen(num);
	for (i=0;i<len;++i) {
		int x=num[i]-'0';
		printf("%s", Map[x]);
		printf("%s", i==len-1?"\n":" ");
	}
	return 0;
}
