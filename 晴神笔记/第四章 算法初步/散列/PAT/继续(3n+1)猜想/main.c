#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 105
// ����������x=27ʱ�����ɵ�4616.
/*
ע�⵽�������е�Ԫ����100Ϊ���ޣ���˼�����̳��ִ���100������
��ȫ���Ժ��ԣ����Һ���Ĳ�ѯҲ������ʵ�����100������
*/ 
#define MAXM (4616 + 1)

int hashtable[MAXN];
int a[MAXN];

// ���ݹ����Ƶ����ܱ�x���ǵ�������¼��hashtable�С� 
int Fill(int x) {
	// �Ѿ�����ˡ� 
	if (hashtable[x]) return;
	while (x != 1) {
		if (x % 2) {
			x = (3*x+1) / 2;
		} else {
			x /= 2;
		}
		/*
		hashtable��¼1-100�����Ƿ��б������������Ԫ�ظ��ǵģ�
		�����������ܸ���100���ϵ��������ǲ����ġ�
		*/ 
		if (x <= 100) {
			hashtable[x]=1;
		}
	}
}

// �ؼ����Ӵ�С���С� 
int CMP(const void*_a, const void*_b) {
	return *(int*)_b - *(int*)_a;
}

int main(int argc, char *argv[]) {
	int N;
	int i;
	int num;
	
	scanf("%d",&N);
	for (i=0;i<N;++i) {
		scanf("%d",&a[i]);
		Fill(a[i]);
	}
	num=0;
	for (i=0;i<N;++i) {
		if (!hashtable[a[i]]) {
			a[num++]=a[i];
		}
	}
	qsort(a, num, sizeof(int), CMP);
	for (i=0;i<num;++i) {
		printf("%d%s", a[i], i==num-1?"\n":" ");
	}
	
	return 0;
}
