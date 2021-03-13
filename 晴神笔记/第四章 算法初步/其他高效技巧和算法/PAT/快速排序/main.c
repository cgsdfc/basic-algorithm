#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
对每个元素X，作为主元，对原序列进行划分，如果X满足条件，
则划分后的序列与原序列相同；否则必然不同。这个复杂度为平方。 

如果一个元素X满足条件，则在排好序的序列里，X的位置不会改变。
所以对序列进行排序，如果原序列的元素X与有序序列的元素X，都在相同的位置，
则X满足条件。时间复杂度为nlogn。这个不是充要条件，而是必要条件。
这个算法错误。 

先预处理，求出每个元素的左边所有元素的最大值，放在一个数组里，
再求出每个元素右边所有元素的最小值，放在另一个数组里。
这个预处理是线性的。 
然后对每一个元素，如果它大于左边所有元素的最大值，小于右边所有元素的最小值，
就是满足条件的。复杂度为线性。 这是正解。 

结论：如果要判断x小于一些数，等价条件为x小于它们的最小值。
如果x大于一些数，等价为x大于它们的最大值。
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
	
	// 求左边元素的最大值。 
	for (i=0;i<N;++i) {
		Max[i]=i>0?Max[i-1]:a[i];
		if (a[i] > Max[i]) {
			Max[i]=a[i];
		}
	}
	// 求右边元素的最小值。
	for (i=N-1;i>=0;--i) {
		Min[i]=i==N-1?a[i]:Min[i+1];
		if (a[i] < Min[i]) {
			Min[i]=a[i];
		}
	} 

	// 取所有满足条件的元素。 
	for (i=0;i<N;++i) {
		if (Max[i]<=a[i]&&a[i]<=Min[i]) {
			ans[num++]=a[i];
		}
	}
//	assert(num);
	
	// 要按照递增顺序输出，故排序。
	// 后面的主元一定比前面的主元大，所有不用排序。 
//	qsort(ans, num, sizeof(ans[0]), CMP);
	 
	printf("%d\n", num);
	/*
	当num=0时，如果没有换行，会有格式错误。
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
