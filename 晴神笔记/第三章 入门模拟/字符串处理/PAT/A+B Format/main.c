#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20

// -1000000 9

/*
��������һ���ö��ŷָ����val��

��-1000
-1,000
��200
200 
*/ 

/* �ڶ��ַ��� 
�Ӹ�λ����λ�������ǰ׺����ÿ����һ��������ź����֡�
ǰ׺��ѡȡʹ�ú�׺���ȱض���3�ı����� 
*/ 
void Method2(int val) {
	int n;
	int i;
	
	// ���ڻ�ȡval�ĸ�λ���֡� 
	char buf[MAXN];
	int len;
	
	if (val < 0) {
		putchar('-');
		val=-val;
	}
	do {
		buf[len++]='0'+val%10;
		val/=10;
	} while (val);
	
	// n�ǵ�һ�����֣����ܲ�������������˵�һ���ʣ�µ�ÿ�����ֵ�
	// ������й��ɣ�������������ţ������һ�顣 
	n=len%3;
	if (!n) n=3;
	// �����ǰn����λ���֡� 
	for (i=0;i<n;++i) {
		putchar(buf[len-i-1]);
	}
	// ʣ�µ����֣�ÿ����һ�飬ÿ��ǰ��������š� 
	for (i=n;i<len;++i) {
		if ((i-n) % 3 == 0) putchar(',');
		putchar(buf[len-i-1]);
	}

}

/*
��һ�ַ���
�ڵõ���λ���ֵ�ͬʱ��ÿ��λ����һ�����š�
��Ϊ�Ǵӵ�λ����λ���붺�ţ����Ϸ����ԭ�򣬹�Ȼ��ȷ�� 
��ɺ󣬼������β��������һ�����ţ���ɾ������Ϊ���λǰ�治Ӧ�ж��š�
*/ 
void Method1(int sum) {
	char buf[MAXN];
	int len=0;
	int i=0;
	
	if (sum < 0) {
		putchar('-');
		sum = -sum;
	}
	i=1;
	do {
		// ת�����ַ��� 
		buf[len++]=sum % 10 + '0';
		// ÿ���������֣����һ�����ţ�����������һ���ַ��Ƕ�����ɾ֮�� 
		if (i % 3 == 0) {
			buf[len++]=',';
		}
		++i;
		sum/=10;
	} while (sum);
	if (buf[len-1] == ',') {
		--len;
	}
	for (i=len-1;i>=0;--i) {
		putchar(buf[i]);
	}
}

int main(int argc, char *argv[]) {
	int a,b,sum;

	scanf("%d%d",&a,&b);
	sum=a+b;
	
	Method2(sum);
	putchar('\n');
	
	return 0;
}
