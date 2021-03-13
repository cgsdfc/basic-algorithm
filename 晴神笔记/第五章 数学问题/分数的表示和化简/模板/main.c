#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
�����ı�ʾ����������������
*/

// ���ӷ�ĸһ����long long����Ϊ�˷��������ܳ���int 
typedef long long LL;

/*
�����Ķ��壬Ҫ��������������
1. down�ǷǸ������������Ϊ��������upΪ����
2. �������Ϊ0�������Ϊ0����ĸΪ1.
3. ���ӷ�ĸû�г���1����Ĺ�Լ���������ʣ��ֳ�Լ�֡�

��дReduce
����ʹ�÷����������������� 
*/

typedef struct Fraction Fraction;
struct Fraction {
	LL up,down;
};

/*
gcd�Ƿ���������ز����ٵġ�
*/
LL gcd(LL a, LL b) {
	return !b?a:gcd(b, a%b);
}

/*
llabs��C99�ģ����û�У�����ʵ��һ��ABS�꣬�ܼ򵥵ġ�
*/
#define ABS(x) ((x)<0?(-x):(x))
 
Fraction Reduce(Fraction f) {
	if (f.down < 0) { // ��ĸΪ������Ҫ��֤��ĸ�Ǹ��� 
		f.up = -f.up;
		f.down = -f.down;
	}
	if (f.up == 0) { // ����Ϊ0��Ҫ��֤��ĸΪ1. 
		f.down=1;
	} else { // ��֤���ӷ�ĸ���ʡ�
		// ע�⣬gcdҪ�Ծ���ֵ���С� 
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
��ӡʱ��ͨ����Ŀ������������ٷ����������в�ͬ���Ҫ���磺
1. ����������ӡ�
2. �ٷ������ɴ����������
3. �����ֱ�������
*/ 
void Print(Fraction f) {
	if (f.down == 1) {
		// ������
		printf("%lld", f.up); 
	} else if (ABS(f.up) > ABS(f.down)) {
		// �ٷ�����
		LL x=f.up/f.down; // �������֡�
		LL up=ABS(f.up) % f.down; // ���ŷ����������֣��ʾ���ֵ�� 
		LL down=f.down; // ��ĸ�Ǹ��� 
		printf("%d %d/%d", x, up, down); 
	} else {
		// �������
		printf("%d/%d", f.up, f.down);
	}
}


int main(int argc, char *argv[]) {
	return 0;
}
