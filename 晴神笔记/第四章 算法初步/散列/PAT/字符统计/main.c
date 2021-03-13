#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXS 1005

// ֻ��ͳ��Ӣ����ĸ�ĳ���Ƶ�ʣ����Ҳ����ִ�Сд�� 
// ��Ȼֻ��26����ĸ���������鿪��һЩ�ȽϺá� 
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
		ֻ�бȵ�ǰֵ��Ÿ��£����Ұ��ֵ����С����ö�٣�
		��֤�˶��Ƶ����ȵ���ĸ������ֵ�����С���Ǹ���
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
