/*
����map�Ľⷨ��
���ͬ������������������ʣ�µĿ϶���ռ�������ϵ�����
*/

void main2() {
	int M,N;
	int count=0;
	int ans;
	
	scanf("%d%d",&M,&N);
	for (int i=0;i<N;++i) {
		for (int j=0;j<M;++j) {
			int x;
			scanf("%d", &x);
			if (count == 0) {
				count = 1;
				ans = x;
			} else {
				if (ans == x) {
					++count;
				} else {
					--count;
				}
			}
		}
	}
	printf("%d\n", ans);
}

