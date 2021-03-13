#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
��������������[i,j]֮���ۼӺ͵ķ�����
��O(n)ʱ�䣬����sum���飬���У�
sum[0]=0
sum[1]=a[1]
sum[i]=sum[i-1]+a[i], i>0
��Sum(a, i, j)=sum[j]-sum[i-1], j!=i,i!=0
Sum(a, 0, i)=sum[
*/

#define MAXN 100005

int S[MAXN];

/*
ע�⣬i���±��1��ʼ��
*/ 
int Get(int i, int j) {
	return S[j]-S[i-1];
}

/*
i=left, ��left��right������j��Sum(i,j)=M��
*/ 
int Search(int left, int right, int M) {
	int i=left;
	int mid;
	int sum;
	while (left <= right) {
		mid=(left+right)/2;
		sum=Get(i, mid);
		if (sum == M) {
			return mid;
		} else if (sum > M) {
			right=mid-1;
		} else {
			left=mid+1;
		}
	}
	return -1;
}

/*
i=left����left��right������j��M���Ͻ硣
*/ 
int Search2(int left, int right, int M) {
	int i=left;
	int mid;
	int sum;
	while (left < right) {
		mid=(left+right)/2;
		sum=Get(i, mid);
//		printf("left %d right %d mid %d sum %d\n", left, right, mid, sum);
		
		if (sum >= M) {
			right=mid;
		} else {
			left=mid+1;
		}
	}
	return left;
}

const int inf=1e8 + 1;

/*
�����н�������ڽ���޽������
*/ 
void Solve1(int N, int M) {
	int has;
	int min;
	int i;
	
	/*
	�����[i,j]������S(i,j)==M����������н⣬
	��������Ͻ磬��������Ͻ硣
	*/
	has=0; // �޽� 
	for (i=1;i<=N;++i) {
		// �ںϷ���Χ��j�� 
		int j=Search(i, N, M);
		if (j != -1) {
			printf("%d-%d\n", i, j);
			has=1;
		}
	}
	
//	printf("has %d\n", has);
	
	if (has) return 0; // �н⡣
	
	min=inf;
	for (i=1;i<=N;++i) {
		int j=Search2(i, N+1, M);
//		printf("i %d j %d\n", i, j);
		
		if (j != N+1) {
			int sum=Get(i, j);
			if (sum < min) {
				min=sum; // ������Ͻ硣 
			}
//			printf("%d-%d\n", i, j);
		}
	}
	// �ٰ��Ͻ��ҳ����� 
	for (i=1;i<=N;++i) {
		// �ںϷ���Χ��j�� 
		int j=Search(i, N, min);
		if (j != -1) {
			printf("%d-%d\n", i, j);
		}
	}	
}

/*
�н���޽������Ϊһ�塣
����S�����㣺
S=M������н⣻
S=upper-bound(M)����������Ŀ��Ҫ�������һ���͡�

Ȼ���ٴ��������ҳ������������S��i��j��
*/ 
void Solve2(int N, int M) {
	int S=inf;
	int i;
	for (i=1;i<=N;++i) {
		int j=Search2(i, N+1, M);
		if (M == Get(i, j-1)) {
			S=M;
			break; // �н������ 
		}
		if (j != N+1) {
			// �Ͻ�λ��S�����ڡ�
			int sum=Get(i, j);
			if (sum < S) {
				// �ҵ��˸�С���Ͻ硣
				// ��Ϊi��ͬ�ĸ����������õ��Ͻ粻ͬ����Ҫȡ��Сֵ��
				S=sum; 
			} 
		}
	}
	// ����S��������������еĺͣ�ֻҪ��binarySearch����upper-bound������һ�μ��ɡ�
	for (i=1;i<=N;++i) {
		int j=Search(i, N, S);
		if (j != -1) {
			printf("%d-%d\n", i, j);
		}
	} 
}

int main(int argc, char *argv[]) {
	int N;
	int M;
	int i;
	int sum=0;

	freopen("./in.txt","r",stdin);
	
	scanf("%d%d", &N, &M);
	for (i=0;i<N;++i) {
		int x;
		
		S[i]=sum;
		scanf("%d", &x);
		sum += x;
	}
	/*
	ע�⣬�����ǹؼ�����ΪS��Ԫ��ΪN+1���������ѭ��N�Ρ�
	*/ 
	S[N]=sum;
	
	Solve2(N, M);

	return 0;
}
