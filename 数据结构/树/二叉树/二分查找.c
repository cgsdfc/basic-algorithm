/*
������������ж��ֲ��ҡ�
*/

/*
����x��a���±꣬a�ĳ�����n������Ҳ���������-1.
ע��ʵ�ֶ��ֲ���ʱ���ñ�����ȽϷ��㡣 
*/ 
int BinarySearch(int x, int a[], int n) {
	int left,mid,right;
	
	left=0;
	right=n-1;
	while (left <= right) {
		mid=(left+right)/2;
		if (x < a[mid]) {
			// �������������ҡ�
			right=mid-1; 
		} else if (x > a[mid]) {
			// ���ұ���������ҡ�
			left=mid+1; 
		} else {
			// �ҵ���
			return mid;
		}
	}
	// left > right��������С��0��Ԫ�أ������ʧ�ܡ� 
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

