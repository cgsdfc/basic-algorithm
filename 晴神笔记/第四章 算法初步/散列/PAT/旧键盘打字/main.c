#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
���õ��ַ�������ĸ [a-z, A-Z]������ 0-9���Լ��»��� _������ո񣩡�,��.��-��+�������ϵ�������
*/

#define MAXS 100005

#define MAXN (5+10+26+2)

int hashtable[MAXN];
/*
����ֱ�ӿ�256�����飬����д���ɢ�к�����
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

// ���ַ����ֻ����ô�ࡣ 
char bad[MAXN];
char input[MAXS];

int main(int argc, char *argv[]) {
	int i,len;
	int shif; // �ϵ����õġ�
	
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
