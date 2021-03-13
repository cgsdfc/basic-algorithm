#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
分数的表示，四则运算和输出。
*/

// 分子分母一般用long long，因为乘法除法可能超过int 
typedef long long LL;

/*
分数的定义，要满足三个条件：
1. down是非负数，如果分数为负数，则up为负。
2. 如果分数为0，则分子为0，分母为1.
3. 分子分母没有除了1以外的公约数，即互质，又称约分。

编写Reduce
函数使得分数满足上述条件。 
*/

typedef struct Fraction Fraction;
struct Fraction {
	LL up,down;
};

/*
gcd是分数运算里必不可少的。
*/
LL gcd(LL a, LL b) {
	return !b?a:gcd(b, a%b);
}

/*
llabs是C99的，如果没有，可以实现一个ABS宏，很简单的。
*/
#define ABS(x) ((x)<0?(-x):(x))
 
Fraction Reduce(Fraction f) {
	if (f.down < 0) { // 分母为负数，要保证分母非负。 
		f.up = -f.up;
		f.down = -f.down;
	}
	if (f.up == 0) { // 分子为0，要保证分母为1. 
		f.down=1;
	} else { // 保证分子分母互质。
		// 注意，gcd要对绝对值进行。 
		LL d=gcd(ABS(f.up), ABS(f.down));
		f.up /= d;
		f.down /= d;
	}
	return f;
}

// f1+f2
Fraction Add(Fraction f1, Fraction f2) {
	Fraction res;
	res.up=f1.up*f2.down+f2.up*f1.down;
	res.down=f1.down*f2.down;
	return Reduce(res);
}

// f1-f2
Fraction Sub(Fraction f1, Fraction f2) {
	Fraction res;
	res.up=f1.up*f2.down-f2.up*f1.down;
	res.down=f1.down*f2.down;
	return Reduce(res);
}

// f1*f2
Fraction Mul(Fraction f1, Fraction f2) {
	Fraction res;
	res.up=f1.up*f2.up;
	res.down=f1.down*f2.down;
	return Reduce(res);
}

// f1/f2
Fraction Div(Fraction f1, Fraction f2) {
	Fraction res;
	if (f2.up == 0) {
		printf("DivideZeroError");
		return res; // undefined.
	}
	res.up=f1.up*f2.down;
	res.down=f1.down*f2.up;
	return Reduce(res);
}

/*
打印时，通常题目根据真分数，假分数，整数有不同输出要求，如：
1. 整数输出分子。
2. 假分数化成带分数输出。
3. 真分数直接输出。
*/ 
void Print(Fraction f) {
	if (f.down == 1) {
		// 整数。
		printf("%lld", f.up); 
	} else if (ABS(f.up) > ABS(f.down)) {
		// 假分数。
		LL x=f.up/f.down; // 整数部分。
		LL up=ABS(f.up) % f.down; // 符号放在整数部分，故绝对值。 
		LL down=f.down; // 分母非负。 
		printf("%d %d/%d", x, up, down); 
	} else {
		// 真分数。
		printf("%d/%d", f.up, f.down);
	}
}


int main(int argc, char *argv[]) {
	return 0;
}
