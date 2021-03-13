/*
在有序数组进行二分查找。
*/

/*
查找x在a的下标，a的长度是n，如果找不到，返回-1.
注意实现二分查找时，用闭区间比较方便。 
*/ 
int BinarySearch(int x, int a[], int n) {
	int left,mid,right;
	
	left=0;
	right=n-1;
	while (left <= right) {
		mid=(left+right)/2;
		if (x < a[mid]) {
			// 在左边区间继续找。
			right=mid-1; 
		} else if (x > a[mid]) {
			// 在右边区间继续找。
			left=mid+1; 
		} else {
			// 找到了
			return mid;
		}
	}
	// left > right，区间缩小到0个元素，则查找失败。 
	return -1;
} 

void TestBSearch(void) {
	int a[10];
	int n=10;
	int i;
	
	for (i=1;i<=10;++i) {
		a[i-1]=i;
	}
	
	for (i=0;i<=11;++i) {
		int x=i;
		int pos=BinarySearch(x, a, n);
		printf("find %d => %d\n", x, pos);
	}
}

