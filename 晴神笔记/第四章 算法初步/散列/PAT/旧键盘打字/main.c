#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
可用的字符包括字母 [a-z, A-Z]、数字 0-9、以及下划线 _（代表空格）、,、.、-、+（代表上档键）。
*/

#define MAXS 100005

#define MAXN (5+10+26+2)

int hashtable[MAXN];
/*
可以直接开256的数组，不用写这个散列函数。
*/ 
int Hash(char c) {
	switch (c) {
		case '_':return 0;
		case ',':return 1;
		case '.':return 2;
		case '-':return 3;
		case '+':return 4;
		default:
			if (isdigit(c)) {
				return c-'0'+5;
			}
			if (islower(c)) {
				return c-'a'+15;
			}
			assert(isupper(c));
			return c-'A'+15;
	}
}

// 坏字符最多只有这么多。 
char bad[MAXN];
char input[MAXS];

int main(int argc, char *argv[]) {
	int i,len;
	int shif; // 上档键好的。
	
	gets(bad);
	gets(input);
	for (i=0,len=strlen(bad);i<len;++i) {
		int h=Hash(bad[i]);
		hashtable[h]=1;
	}
	shif=(hashtable[Hash('+')]==0);
	for (i=0,len=strlen(input);i<len;++i) {
		char ch=input[i];
		int h=Hash(ch);
		if (hashtable[h]==0 && (!isupper(ch) || shif)) {
			putchar(ch);
		}
	}
	putchar('\n');
	return 0;
}
