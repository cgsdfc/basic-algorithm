#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char Msg[]="There are %d accounts and no account is modified\n";
const char MsgOne[]="There is 1 account and no account is modified\n";

void PrintMsg(int n) {
	if (n == 1) printf(MsgOne);
	else printf(Msg, n);
}

const char Repl[][4]={"1@","0%","lL","Oo"};

int Modify(char str[], int len) {
	int i;
	int res=0;
	int j;
	
	for (i=0;i<len;++i) {
		for (j=0;j<4;++j) {
			if (str[i]==Repl[j][0]) {
				res=1;
				str[i]=Repl[j][1];
				break;
			}
		}
	}
	return res;
}

typedef struct Acc {
	char name[15];
	char pass[15];
} Acc;

#define MAXN 1005

Acc Changed[MAXN];

int main(int argc, char *argv[]) {
	int k=0;
	int n;
	int i;
	
	scanf("%d",&n);
	for (i=0;i<n;++i) {
		Acc a;
		scanf("%s%s", a.name, a.pass);
		if (Modify(a.pass, strlen(a.pass))) {
			Changed[k++]=a;
		}
	}
	if (k) {
		printf("%d\n", k);
		for (i=0;i<k;++i) {
			printf("%s %s\n", Changed[i].name, Changed[i].pass);
		}
	} else {
		PrintMsg(n);
	}
	return 0;
}
