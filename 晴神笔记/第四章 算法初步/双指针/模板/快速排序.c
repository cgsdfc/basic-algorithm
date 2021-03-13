#include <stdio.h>
#include <stdlib.h>

/*
�������������»�����ɲ��֣�
1. Partition ��������һ��[left, right]�����Ϊ�����֣�
	1. ��ߵ�Ԫ��С�ڵ���A[p]�� 
	2. �м���Ԫ��A[p] ��
	3. �ұߵ�Ԫ�ش���A[p]��
	�����м�Ԫ�ص��±�p��
	 
2. ���������� QuickSort���ݹ���� Partition���ѵ�ǰ���з�Ϊ�����֣�
	��ÿ���ֵݹ���� QuickSort�����������о���������ˡ� 

������ţ�
���ƣ����ѡ����Ԫ�������κ��������ݣ����Ӷȶ������ΪO(n^2)��
1. ����[left, right]�����е���������ĺ�����Rand������ϵͳ����
srand �� rand ʵ�֣���ӳ��Ϊ[0,1]�����ϵ�ʵ������ӳ�䵽[left, right]����������roundȡ������
2. �޸� Partition ����Ϊ RandPartition���Ķ�Ϊ��
	1. ����p��Ϊ[left, right]�ϵ��������
	2. ����p��leftԪ�ء�
	3. ʣ�µ�һ���վɡ�

ע�⣺
1. ����һ���õݹ�ʵ�֡�
2. ��ͨ���ţ������������ţ����������ݱ�����Ϊƽ�����Ӷȣ�
��������е����ݱ��ֽϺã�ƽ�����Ӷ���nlogn��
3. ������ŵ����Ӷ���Ȼ��ƽ�������ǲ�������������������ʹ�ø��Ӷ���ƽ����
�������˼���������������ƽ��������ʵ��������nlogn��
 
*/

static
int Partition(int A[], int left, int right) {
	int temp;
	// �Ȱ���Ԫ���������� 
	temp=A[left];
	// left right ����ʱ�㷨������
	while (left < right) {
		// ��ָ�룬���ھ����ơ� 
		while (left < right && A[right] > temp) right--;
		// Ԫ���ӵ����ȥ��
		A[left]=A[right];
		// ��ָ�룬С�ڵ��ھ����ơ� 
		while (left < right && A[left] <= temp) left++;
		// Ԫ���ӵ��ұ�ȥ�� 
		A[right]=A[left];
		// ˫ָ�룬���м�ƽ��� 
	}
	// ��Ԫ���С� 
	A[left]=temp;
	return left;
}

static 
void QuickSort(int A[], int left, int right) {
	if (left < right) {
		// ��ǰ���䳤�ȴ���1������Ҫ�ݹ�����
		int mid=Partition(A, left, right);
		QuickSort(A, left, mid-1);
		QuickSort(A, mid+1, right); 
	}
}
 
