#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef long long ll;
typedef struct Fraction {
	ll up,down;
} Fraction;

ll gcd(ll a, ll b) {
	return !b?a:gcd(b, a%b);
}

/*
注意：全部数据都要用long long。自带的abs是int的，不行。
gcd的返回值要用ll接受，否则gcd用了ll也没用。参考代码也有这个问题。 
*/ 
ll Abs(ll x) {
	return x<0?-x:x;
}

Fraction Reduce(Fraction f) {
	if (f.down < 0) {
		f.up=-f.up;
		f.down=-f.down;
	}
	if (f.up == 0) {
		f.down=1;
	} else {
		ll d=gcd(Abs(f.up), f.down);
		f.up/=d;
		f.down/=d;
	}
	return f;
}

Fraction Read(void) {
	Fraction f;
	scanf("%lld/%lld", &f.up, &f.down);
	return Reduce(f);
}

void Print(Fraction f) {
	if (f.up < 0) {
		putchar('(');
	}
	if (f.down == 1) {
		printf("%lld", f.up);
	} else if (Abs(f.up) > f.down) {
		printf("%lld %lld/%lld", f.up/f.down, Abs(f.up)%f.down, f.down);
	} else {
		printf("%lld/%lld", f.up, f.down);
	}
	if (f.up < 0) {
		putchar(')');
	}
}

void Arithmetic(Fraction f1, Fraction f2, char op) {
	Fraction res;
	int inf=0;
	
	switch (op) {
		case '+':
			res.up=f1.up*f2.down+f2.up*f1.down;
			res.down=f1.down*f2.down;
			break;
		case '-':
			res.up=f1.up*f2.down-f2.up*f1.down;
			res.down=f1.down*f2.down;
			break;
		case '*':
			res.up=f1.up*f2.up;
			res.down=f1.down*f2.down;
			break;
		case '/':
			if (f2.up == 0) {
				inf=1;
			} else {
				res.up=f1.up*f2.down;
				res.down=f1.down*f2.up;
			}
			break;
		default:
			assert(0);
	}
	
	Print(f1);
	printf(" %c ", op);
	Print(f2);
	printf(" = ");
	if (inf) {
		printf("Inf");
	} else {
		res=Reduce(res);
		Print(res);
	}
	printf("\n");
}

const char OPS[]="+-*/";

int main(int argc, char *argv[]) {
	Fraction a,b;
	int i;
#ifndef ONLINE_JUDGE
	freopen("./in.txt","r",stdin);
#endif

//	printf("%llx\n", INF);
//	return 0;

	a=Read();
	b=Read();
	Arithmetic(a, b, '+');
	Arithmetic(a, b, '-');
	Arithmetic(a, b, '*');
	Arithmetic(a, b, '/');
	
//	for (i=0;i<4;++i) {
//		Arithmetic(a, b, OPS[i]);
//	}
	
	return 0;
}
