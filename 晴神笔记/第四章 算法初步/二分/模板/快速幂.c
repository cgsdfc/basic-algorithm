/*
计算幂：a^b mod m.
Naive方法复杂度是O(b)，当b较大时超时。
二分方法，复杂度时O(logb)，性能极好。

递推公式：
a^b = a * a^(b-1) if a is odd.
a^b = a^(b/2) * a^(b/2) if a is even.

快速幂有两种实现，效率相差不大：
1. 递归实现，基于递推公式。 
2. 迭代实现，基于将b看作二进制，并且迭代的计算
a^1, a^2, a^4, a^8,  ....
*/

typedef long long LL;

/*
递归写法，计算 pow(a, b) % m.
*/ 
LL binaryPow(LL a, LL b, LL m) {
	if (m == 1) return 0; // 任何整数对1取余，都是0. 
	
	if (b == 0) return 1;
	if (b & 1) {
		return a * binaryPow(a, b-1, m) % m;
		// 奇数，b-1 
	} else {
		// 偶数，先算b/2.
		LL mul = binaryPow(a, b/2, m);
		return mul * mul % m; 
	}
} 

/*
迭代写法。
*/
LL IterPow(LL a, LL b, LL m) {
	LL ans=1;
	while (b > 0) {
		if (b & 1) {
			// 逢奇便取。 
			ans = ans * a % m;
		}
		// 底数自乘。 
		a = a * a % m;
		// 指数右移。 
		b >>= 1;
	}
	return ans;
} 

