#include <iostream>
#include <math.h>
#include <time.h> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void PrintN(int N) {
	if (N) {
		PrintN(N - 1);
		printf("%d\n", N);
	}
}

double f1(int n, double a[], double x) {
	double p=a[0];
	int i;
	for (i=1;i<=n;++i) {
		p+=a[i] * pow(x, i);
	}
	return p;
}

double f2(int n, double a[], double x) {
	double p=a[n];
	int i;
	for (i=n;i>=1;--i) {
		p = a[i-1] + p*x;
	}
	return p;
}

#define MAXN 10
#define MAXK 1e7

int main(int argc, char** argv) {

	int i;
	double dur;
	clock_t start,stop,tick;
	double a[MAXN];
	double x=1.1;
	
	for (i=0;i<MAXN;++i) {
		a[i]=i;
	}
	
	start=clock();
	for (i=0;i<MAXK;++i) {
		f1(MAXN-1, a, x);
	}
	stop=clock();
	tick=stop-start;
	printf("tick=%f\n", (double)tick/ MAXK);
	printf("dur=%f\n", (double)tick / CLK_TCK / MAXK);
	
	start=clock();
	for (i=0;i<MAXK;++i) {
		f2(MAXN-1, a, x);
	}
	stop=clock();
	tick=stop-start;
	printf("tick=%f\n", (double)tick/ MAXK);
	printf("dur=%f\n", (double)tick / CLK_TCK/ MAXK);
	
}
