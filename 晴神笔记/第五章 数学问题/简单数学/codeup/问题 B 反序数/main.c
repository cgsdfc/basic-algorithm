#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
本题有唯一解：1089
*/ 
int main(int argc, char *argv[]) {
	int N;
	int a,b,c,d;
	for (a=1;a<=9;++a) {
		for (b=0;b<=9;++b) {
			for (c=0;c<=9;++c) {
				for (d=1;d<=9;++d) {
					int A=a*1000+b*100+c*10+d;
					int B=d*1000+c*100+b*10+a;
					if (9*A==B) {
//						printf("%d\n", -A);
						printf("%d\n", A);
					}
				}
			}
		}
	}
	return 0;
}
