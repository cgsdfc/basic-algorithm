#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXS 1005

// 只用统计英文字母的出现频率，并且不区分大小写。 
// 虽然只有26个字母，但是数组开大一些比较好。 
int hashtable[30];
char str[MAXS];

int main(int argc, char *argv[]) {
	int i,len;
	int max,pos;
	
	gets(str);
//	puts(str);
	
	for (i=0,len=strlen(str);i<len;++i) {
		if (isalpha(str[i])) {
			hashtable[tolower(str[i])-'a']++;
		}
	}
	
//	for (i=0;i<26;++i) {
//		printf("%c %d\n", 'a'+i, hashtable[i]);
//	}
	
	max=-1;
	pos=0;
	for (i=0;i<26;++i) {
		/*
		只有比当前值大才更新，并且按字典序从小到大枚举，
		保证了多个频数相等的字母，输出字典序最小的那个。
		*/ 
		if (hashtable[i] > max) {
			max=hashtable[i];
			pos=i;
		}
	}
	assert(max != -1);
	printf("%c %d\n", pos+'a', max);
	return 0;
}
