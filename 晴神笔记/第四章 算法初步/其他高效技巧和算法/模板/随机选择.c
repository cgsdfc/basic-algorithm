#include <stdio.h>
#include <stdlib.h>

/*
�ڿ�������ĺ����ӳ��� RandPartition �Ļ����ϵ����� RandSelect ������
�����������K���Ԫ��X�����Ұ�����ԭ�ط�Ϊ�����֣����С�ڵ���X���ұߴ���X��
Ч�ʽϸߣ�ƽ��O(n)��

ע��
��K���Ԫ��X����ʾ��ͬX��Xǰ���Ԫ�أ�һ����K��Ԫ�ء�
Ҳ������õ������У���K��Ԫ�أ�1-base���� 

����˼�룺
�����ѡ����Ԫp���� RandPartition �����л��֡�
������Ԫ�ڻ��ֺ�������ǵڼ��󣬼�ΪM��
1. ���M=K���򻮷���ϣ�p��������Ԫ�ء�
2. ���M<K����X���ұ����У����ұ�ɵ�M-K�󣬵ݹ���С�
3. ���M>K����X��������У������ǵ�K�󣬵ݹ���С�
4. �������ֻ��һ��Ԫ�أ������Ψһ��Ԫ�ؾ���X������K�Ƕ��١� 
*/

int RandPartition(int A[], int left, int right) {
	int p;
	int temp;
	
	/*
	ע����Ԫ�������������ѡ���һ�����������Ƚ������������������䡣
	��󷵻صĲ�������Ԫ�����ѡȡ���±꣬������ɻ��ֺ���Ԫ���ڵ�λ�á�
	*/ 
	p=round(rand()*1.0/RAND_MAX*(right-left)+left);
	temp=A[p];
	A[p]=A[left];
	A[left]=temp;
	
	while (left < right) {
		while (left < right && A[right] > temp) --right;
		A[left]=A[right];
		while (left < right && A[left] <= temp) ++left;
		A[right]=A[left];
	}
	A[left]=temp;
	return left;
}

/*
���a�е�K�������KӦ��ȡ1--N�����K<1���򷵻���С������� K>N���򷵻��������
*/ 
int RandSelect(int A[], int left, int right, int K) {
	int p;
	int M;
	
	if (left == right) {
		return A[left];
	}
	p=RandPartition(A, left, right);
	M=p-left+1;
	if (K == M) {
		return A[p];
	}
	if (K < M) {
		return RandSelect(A, left, p-1, K);
	} else {
		return RandSelect(A, p+1, right, K-M);
	}
}

void TestRandSelect(void) {
	const int A[]={5,12,7,2,9,3};
	const int len=sizeof(A)/sizeof(A[0]);
	int i;
	int ans;
	
	for (i=0;i<len;++i) {
		int K=i+1;
		ans=RandSelect(A, 0, len-1, K);
		printf("K %d ans %d\n", K, ans);
	}
	
	ans=RandSelect(A, 0, len-1, 0);
	printf("ans %d\n", ans);
	ans=RandSelect(A, 0, len-1, len+1);
	printf("ans %d\n", ans);
	
}

