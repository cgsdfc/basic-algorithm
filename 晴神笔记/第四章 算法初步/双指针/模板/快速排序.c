#include <stdio.h>
#include <stdlib.h>

/*
快速排序由以下基础组成部分：
1. Partition 函数，把一个[left, right]区间分为三部分：
	1. 左边的元素小于等于A[p]。 
	2. 中间是元素A[p] 。
	3. 右边的元素大于A[p]。
	返回中间元素的下标p。
	 
2. 排序主函数 QuickSort，递归调用 Partition，把当前序列分为两部分，
	对每部分递归调用 QuickSort，则整个序列就是有序的了。 

随机快排：
优势：随机选择主元，对于任何输入数据，复杂度都不会恶化为O(n^2)。
1. 生成[left, right]区间中的随机整数的函数，Rand，利用系统函数
srand 和 rand 实现，先映射为[0,1]区间上的实数，再映射到[left, right]的整数（用round取整）。
2. 修改 Partition 函数为 RandPartition，改动为：
	1. 生成p，为[left, right]上的随机数。
	2. 交换p和left元素。
	3. 剩下的一切照旧。

注意：
1. 快排一般用递归实现。
2. 普通快排（相对于随机快排）对有序数据表现最差，为平方复杂度，
对随机排列的数据表现较好，平均复杂度是nlogn。
3. 随机快排的最差复杂度仍然是平方，但是不存在这样的输入数据使得复杂度是平方。
（大概意思就是理论上最差是平方，但是实际上总是nlogn。
 
*/

static
int Partition(int A[], int left, int right) {
	int temp;
	// 先把主元保存起来。 
	temp=A[left];
	// left right 相遇时算法结束。
	while (left < right) {
		// 右指针，大于就左移。 
		while (left < right && A[right] > temp) right--;
		// 元素扔到左边去。
		A[left]=A[right];
		// 左指针，小于等于就右移。 
		while (left < right && A[left] <= temp) left++;
		// 元素扔到右边去。 
		A[right]=A[left];
		// 双指针，向中间逼近。 
	}
	// 主元归中。 
	A[left]=temp;
	return left;
}

static 
void QuickSort(int A[], int left, int right) {
	if (left < right) {
		// 当前区间长度大于1，则需要递归排序。
		int mid=Partition(A, left, right);
		QuickSort(A, left, mid-1);
		QuickSort(A, mid+1, right); 
	}
}
 
