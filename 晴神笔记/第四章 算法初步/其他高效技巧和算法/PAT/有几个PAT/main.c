#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAXN 100005
#define MOD 1000000007

char str[MAXN];
int left[MAXN]; // 左边多少个P 
int right[MAXN]; // 右边多少个T 
 
int main(int argc, char *argv[]) {
	int i;
	int len;
	int ans=0;
	
	gets(str);
	len=strlen(str);
	
	for (i=1;i<len;++i) {
		left[i]=left[i-1];
		if (str[i-1] == 'P') {
			++left[i];
		}
	}
	for (i=len-2;i>=0;--i) {
		right[i]=right[i+1];
		if (str[i+1] == 'T') {
			++right[i];
		}
	}
	for (i=0;i<len;++i) {
		if (str[i]=='A') {
			ans = (ans + left[i]*right[i]) % MOD;
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
