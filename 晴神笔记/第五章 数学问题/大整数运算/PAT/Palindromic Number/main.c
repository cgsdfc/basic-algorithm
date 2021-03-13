#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
ע�⣬��Ŀ������ӵķ�ʽ�������Ǽ򵥵�100��10e10������ӣ�
���һ������x����ڶ������ӽ�2*x��������4*x�����Ե�100������
��2^99 x���Ƿǳ���ġ�2^99Լ����10e30���������������Դﵽ10e40. 
���ǵ�2*x�Ǳ��ع��ƣ����鿪��100�ȽϺá� 

�����Ͽ�����������long long�������ˣ�������Ŀ�ļ��㷽ʽ����Kָ������ģ�
����K�ǱȽϴ������1000�������Ա����ø߾��Ȳ������� 
*/ 
#define MAXN 100 

typedef struct Big {
	int d[MAXN];
	int len;
} Big;

/*
a��a����������ӡ�
*/ 
Big Add(Big a) {
	int i;
	Big c={};
	int carry=0;
	
	for (i=0;i<a.len;++i) {
		int temp=a.d[i]+a.d[a.len-1-i]+carry;
		c.d[c.len++]=temp%10;
		carry=temp/10;
	}
	if (carry) {
		c.d[c.len++]=carry;
	}
	return c;
}

// �ж�a�Ƿ��ǻ������� 
int Judge(Big a) {
	int i;
	for (i=0;i<a.len/2;++i) {
		if (a.d[i] != a.d[a.len-1-i]) {
			return 0;
		}
	}
	return 1;
}

Big From(char str[], int len) {
	int i;
	Big c={};
	
	c.len=len;
	for (i=0;i<len;++i) {
		c.d[i]=str[len-1-i]-'0';
	}
	return c;
}

void Print(Big a) {
	int i;
	for (i=a.len-1;i>=0;--i) {
		printf("%d", a.d[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char str[MAXN];
	Big a;
	int K;
	int i;
	
	scanf("%s%d", str, &K);
	a=From(str, strlen(str));
	if (Judge(a)) {
		// ���У�������ǻ�������
		Print(a);
		printf("0\n");
		return 0;
	}
	for (i=0;i<K&&!Judge(a);++i) {
//		Print(a);
		a=Add(a);
	}
	Print(a);
	printf("%d\n", i);
	
	return 0;
}
