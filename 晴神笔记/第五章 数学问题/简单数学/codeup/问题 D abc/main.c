#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// abc+bcc=532
int main(int argc, char *argv[]) {
	int a,b,c;
	for (a=1;a<=9;++a) {
		for (b=1;b<=9;++b) {
			for (c=0;c<=9;++c) {
				int A=a*100+b*10+c;
				int B=b*100+c*10+c;
				if (A+B==532) {
					printf("%d %d %d\n",a,b,c);
				}
			}
		}
	}
	return 0;
}
