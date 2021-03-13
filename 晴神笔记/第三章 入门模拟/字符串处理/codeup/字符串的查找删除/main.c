#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
这是北航真题。 
*/

typedef struct Str {
	char* s;
	int len;
} Str;

void Process(Str str, Str tar) {
	int i;
	for (i=0;i<str.len;) {
		int res;
		int j;
		
//		printf("#%d\n", i);
		
		if (str.s[i] == ' ') {
			++i;
			continue;
		}

		// 朴素字符串查找。 
		if (str.len-i < tar.len) {
			res=0;
		} else {		
			res=1;
			for (j=0; j<tar.len; ++j) {
				// 不区分大小写。 
				if (tolower(str.s[i+j]) != tolower(tar.s[j])) {
					res=0;
					break;
				}
			}
		}
		if (res) {
			// 找到了匹配 i-j
			i+=tar.len; 
		} else {
			putchar(str.s[i]);
			++i;
		}
	}
}

// 题目没有告诉数组大小。 
char target[200];
char line[1000];

int main(int argc, char *argv[]) {
	gets(target);
	while (gets(line)) {
		Str str={line, strlen(line)};
		Str tar={target, strlen(target)};
		Process(str, tar);
		putchar('\n');
	}
	return 0;
}
