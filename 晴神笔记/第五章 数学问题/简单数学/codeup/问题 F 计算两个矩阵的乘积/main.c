#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 4
typedef int Mat[MAXN][MAXN];

int Read(int row, int col, Mat ans) {
	int i;
	int j;
	for (i=0;i<row;++i) {
		for (j=0;j<col;++j) {
			if (scanf("%d", &ans[i][j]) == EOF) {
				return EOF;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	Mat a, b;
	int i,j;
	
	while (Read(2, 3, a), Read(3, 2, b) != EOF) {
		for (i=0;i<2;++i) {
			for (j=0;j<2;++j) {
				int ans=0;
				int k;
				for (k=0;k<3;++k) {
					ans+=a[i][k]*b[k][j];
				}
				printf("%d%s", ans, j==1?"\n":" ");
			}
		}
	}
	return 0;
}
