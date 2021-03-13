#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
最大公约数模板 gcd 
注意点： 
1. a，b是自然数。负数的 gcd 不知道是什么。
2. a和b的大小关系不要紧，gcd 函数会自动交换两个数。
3. 由a，b的因子集合（多重集合）的交集组成。 
*/

int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
} 

int gcd2(int a, int b) {
	if (b == 0) return a;
	return gcd2(b, a % b);
}

/*
最小公倍数 lcm
注意点：
1. 建立在gcd的基础上。
2. 由a，b的因子集合的并集组成（相乘）。
3. lcm(a,b)=a/d*b; d=gcd(a,b) 
4. 为了防止溢出，一般先除再乘。 
*/

int lcm(int a, int b) {
	return a/gcd(a,b)*b;
}

 
int main(int argc, char *argv[]) {
	return 0;
}
