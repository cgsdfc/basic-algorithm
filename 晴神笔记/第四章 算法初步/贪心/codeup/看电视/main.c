#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����̰�ģ��ҳ�N�������У����ཻ�������������
*/

typedef struct Interval Interval;
struct Interval {
	int start, end;
};

#define MAXN 105

Interval ints[MAXN];

/*
�����߼���
������ѡ��˵����ģ������˵���ͬ����ѡ�Ҷ˵���С�ġ�
��˵�Խ���������뿪ԭ��ԽԶ���ڴ˻����ϣ��Ҷ˵�ԽС��������ԽС��
*/ 
int CMP(const void*_a, const void*_b) {
	Interval* a=(Interval*)_a;
	Interval* b=(Interval*)_b;
	if (a->start != b->start) {
		return b->start-a->start;
	}
	return a->end-b->end;
}

int main(int argc, char *argv[]) {
	int N;
	int i;
	int ans;
	int lastx;
		
	while (scanf("%d", &N), (N!=0)) {
		for (i=0;i<N;++i) {
			scanf("%d%d", &ints[i].start, &ints[i].end);
		}
		qsort(ints, N, sizeof(Interval), CMP);
		/*
		��һ�����������ȼ���ߵģ���ѡ��Ȼ������˳��Ӹߵ���ɨ�裬
		������ǰһ�����䲻�ཻ�ģ���ѡȡ�����Ҹ��µ�ǰ���䡣
		*/ 
		ans=1;
		lastx=ints[0].start;
		for (i=1;i<N;++i) {
			if (ints[i].end <= lastx) {
				++ans;
				lastx=ints[i].start;
			}
		}
		printf("%d\n", ans);
	}
		
	return 0;
}
