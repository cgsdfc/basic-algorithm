#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
���Լ��ģ�� gcd 
ע��㣺 
1. a��b����Ȼ���������� gcd ��֪����ʲô��
2. a��b�Ĵ�С��ϵ��Ҫ����gcd �������Զ�������������
3. ��a��b�����Ӽ��ϣ����ؼ��ϣ��Ľ�����ɡ� 
*/

int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
} 

int gcd2(int a, int b) {
	if (b == 0) return a;
	return gcd2(b, a % b);
}

/*
��С������ lcm
ע��㣺
1. ������gcd�Ļ����ϡ�
2. ��a��b�����Ӽ��ϵĲ�����ɣ���ˣ���
3. lcm(a,b)=a/d*b; d=gcd(a,b) 
4. Ϊ�˷�ֹ�����һ���ȳ��ٳˡ� 
*/

int lcm(int a, int b) {
	return a/gcd(a,b)*b;
}

 
int main(int argc, char *argv[]) {
	return 0;
}
