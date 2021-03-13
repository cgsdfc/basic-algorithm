#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void Println(char c, int space, int sym) {
	int i;
	for (i=0;i<space;++i) putchar(' ');
	for (i=0;i<sym;++i) putchar(c);
	// 注意,符号后不应该输出任何空格. 
//	for (i=0;i<space;++i) putchar(' ');
	putchar('\n');
}

// 打印一个N阶沙漏. 
void Print(char c, int n) {
	int col=2*n-1;
	int row=col;
	int i;
	
	for (i=0; i<row; ++i) {
		int space;
		int sym;
		if (i <= n-1) {
			space=i;
		} else {
			space=row-1-i;
		}
		sym=col-2*space;
		Println(c, space, sym);
	}
}

int GetN(int m) {
	return (int)floor(sqrt((m+1)/2.0));
}

int main(int argc, char *argv[]) {
	int m;
	int n;
	char c;
	int used;
	
	scanf("%d %c", &m, &c);
	n=(int)floor(sqrt((m+1)/2.0));
	used=2*n*n-1;
	Print(c, n);
	printf("%d\n", m-used);

	return 0;
}
