#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
��ÿ��Ԫ��X����Ϊ��Ԫ����ԭ���н��л��֣����X����������
�򻮷ֺ��������ԭ������ͬ�������Ȼ��ͬ��������Ӷ�Ϊƽ���� 

���һ��Ԫ��X���������������ź���������X��λ�ò���ı䡣
���Զ����н����������ԭ���е�Ԫ��X���������е�Ԫ��X��������ͬ��λ�ã�
��X����������ʱ�临�Ӷ�Ϊnlogn��������ǳ�Ҫ���������Ǳ�Ҫ������
����㷨���� 

��Ԥ�������ÿ��Ԫ�ص��������Ԫ�ص����ֵ������һ�������
�����ÿ��Ԫ���ұ�����Ԫ�ص���Сֵ��������һ�������
���Ԥ���������Եġ� 
Ȼ���ÿһ��Ԫ�أ�����������������Ԫ�ص����ֵ��С���ұ�����Ԫ�ص���Сֵ��
�������������ġ����Ӷ�Ϊ���ԡ� �������⡣ 

���ۣ����Ҫ�ж�xС��һЩ�����ȼ�����ΪxС�����ǵ���Сֵ��
���x����һЩ�����ȼ�Ϊx�������ǵ����ֵ��
*/

#define MAXN 100005

int a[MAXN];
int Max[MAXN], Min[MAXN];
int ans[MAXN];

int N;

int CMP(const void* a, const void* b) {
	return *(int*)a-*(int*)b;
}

int main(int argc, char *argv[]) {
	int i;
	int num=0;
	int min;
	int max;
	
	scanf("%d", &N);
	for (i=0;i<N;++i) {
		scanf("%d", &a[i]);
	}
	
	// �����Ԫ�ص����ֵ�� 
	for (i=0;i<N;++i) {
		Max[i]=i>0?Max[i-1]:a[i];
		if (a[i] > Max[i]) {
			Max[i]=a[i];
		}
	}
	// ���ұ�Ԫ�ص���Сֵ��
	for (i=N-1;i>=0;--i) {
		Min[i]=i==N-1?a[i]:Min[i+1];
		if (a[i] < Min[i]) {
			Min[i]=a[i];
		}
	} 

	// ȡ��������������Ԫ�ء� 
	for (i=0;i<N;++i) {
		if (Max[i]<=a[i]&&a[i]<=Min[i]) {
			ans[num++]=a[i];
		}
	}
//	assert(num);
	
	// Ҫ���յ���˳�������������
	// �������Ԫһ����ǰ�����Ԫ�����в������� 
//	qsort(ans, num, sizeof(ans[0]), CMP);
	 
	printf("%d\n", num);
	/*
	��num=0ʱ�����û�л��У����и�ʽ����
	*/
	if (!num) {
		putchar('\n');
		return 0;
	}
	for (i=0;i<num;++i) {
		printf("%d%s", ans[i], i==num-1?"\n":" ");
	}
	return 0;
}
