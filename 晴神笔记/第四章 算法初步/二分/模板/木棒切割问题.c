#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
ľ���и�����
����N��ľ�������Ⱦ���֪���и��������õ�����K�γ�����ȵ�ľ����
���ȱ���������������Щ������ȵ�ľ������ж೤��
ע���и�ʱ����������һЩ���Ȳ����ľ����

����ȵĳ���ΪL���и���ľ��ΪK�Ρ�ע�⵽��LԽ��K�ض�ԽС��
���Ǳ������������k�����K������L������L��С������������
����k���ڵ���K�����һ��L��ת��ΪkС��K�ĵ�һ��L������һ�����������ˡ�
����L�����Լ����k��L����СֵΪ1�����ֵΪ����ľ�����ȵ����ֵ�� 
*/

#define MAXN 100

int a[MAXN]; // ľ��ԭʼ���ȡ�

// ����L����K�� 
int GetK(int n, int L) {
	int ans=0;
	int i;
	for (i=0;i<n;++i) {
		ans += a[i] / L;
	}
	return ans;
}

// �ҳ���һ��ʹ��kС��K��L�� 
int BSearch(int left, int right, int N, int K) {
	int mid;
	while (left < right) {
		mid=(left+right)/2;
		int k=GetK(N, mid);
		if (k < K) {
			// ����������������ҪʹL���٣���Ϊ�ǵ�һ��L������ȥ������䡣 
			right=mid;
		} else {
			// ��������������Ҫʹ��L����ȥ�ұ����䡣 
			left=mid+1;
		}
	}
}

void CutRodMain(void) {
	int N;
	int K;
	int i;
	int max=0;
	int ans;
//	int left,right;
	
	scanf("%d%d", &N, &K);
	for (i=0;i<N;++i) {
		scanf("%d",&a[i]);
		if (a[i] > max) {
			max=a[i];
		}
	}
	ans=BSearch(1, max, N, K);
	printf("%d\n", ans-1);
}

