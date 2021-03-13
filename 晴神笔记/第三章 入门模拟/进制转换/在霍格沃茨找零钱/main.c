#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Money {
	int g,s,k;
} Money;

void Read(Money* m) {
	scanf("%d.%d.%d", &m->g, &m->s, &m->k);
}

int ToK(Money m) {
	return m.g*17*29+m.s*29+m.k;
}

Money FromK(int k) {
	Money m;
	m.k=k%29;
	m.s=k/29%17;
	m.g=k/29/17;
	return m;
}

void Minus(Money a, Money b) {
	int ak=ToK(a);
	int bk=ToK(b);
	int res=ak-bk;
	Money m=FromK(abs(res));
	
	printf("%s%d.%d.%d\n", res<0?"-":"", m.g, m.s, m.k);
}

int main(int argc, char *argv[]) {
	Money p, a;
	
	Read(&p);
	Read(&a);
	Minus(a, p);
	
	return 0;
}
