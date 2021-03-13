#include <stdio.h>
#include <stdlib.h>
#include <math.h> // sqrt
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����ģ��
1. �����ж� sqrt(n)
2. ����������
	1. ���������ж� n*sqrt(n) 
	2. ɸ�� nloglogn
*/

int IsPrime(int n) {
	int i;
	int up;
	
	if (n<=1) return 0;
	// ��2��floor(sqrt(n))
	up=(int)sqrt(n);
	for (i=2;i<=up;++i) {
		// ��������� 
		if (n % i == 0) return 0;
	}
	return 1;
} 

/*
������Ĵ�С��
�������ʾ����i�Ƿ�Ϊ���������ڹ�ϣ�����ʵġ�
�������ޱ����Ҫ�ж�������1. ��Ϊ��СΪSize�ı�
�±���õ�ֻ��Size-1. ���Ҫ��1--100����������������Ĵ�С
����Ϊ101. 

����ɸ����˵���������Ǳ���ģ���Ϊ�����ǵ�ǰ��֪��������
����ɹ������ĺ�����
���������ж�������һ��Ҫ���������� 
*/
 
#define MAXN 101

/*
������p[i]Ϊ0����ʾ����������0��1���⣩��
Ϊ1��ʾ���Ǻ�����
���⻹��Ҫprime���飬�����ı��������� 
*/
int p[MAXN];
int prime[MAXN];
int pNum; // prime��Size�� 

/*
ɸ����������
�������棬�ҳ�1--MAXN-1��ȫ����������¼��p��prime�����
�������£�
1. ��ǰN�������������������ۼƴﵽNʱ�����㷨��
2. ��1--N�е�ȫ����������ɸ�����Ͻ��MAXN��ΪN+1���ɡ�
���ߣ���Ҫ���㷨�����ǰ�MAXN����ΪN���Ͻ磬���ȫ������ 
ע�ⲻҪԽ�硣
*/ 
void FindPrime(void) {
	int i;
	/*
	Ϊ�˷�ֹ����Խ�磬��MAXN������ѭ����
	��ѭ���ڲ�����pNum��n��������ǰ�˳�ѭ����
	������ʹn��С��Խ���ˣ�Ҳ��������Խ�硣
	ע������д���� 
	*/ 
	// ��2��ʼ��2�ǵ�һ��������1���ǡ� 
	for (i=2;i<MAXN;++i) {
		int j;
		if (p[i] == 0) {
			// �ҵ�һ��������
			prime[pNum++]=i;
			// ɸ������ĺ�����
			for (j=i+i;j<MAXN;j+=i) {
				/*
				ע�����ѭ����д������ɸ��i�Ժ�MAXN֮ǰ��ȫ��i�ı�����
				��˾���2i��3i��4i���ȵȡ�ע��i�ǲ���ɸ���ģ����Դ�2i��ʼ��
				*/
				p[j]=1; 
			} 
		}
	}
}

/*
�����ж���������
ע��p[i]=true��ʾi��������
*/ 
void FindPrime2(void) {
	int i;
	for (i=1; i<MAXN; ++i) {
		if (IsPrime(i)) {
			p[i]=1;
			prime[pNum++]=i;
		}
	}
}

int main(int argc, char *argv[]) {
	int i;
	FindPrime();
	for (i=0;i<pNum;++i) {
		printf("%d ", prime[i]);
	}
	
	return 0;
}
