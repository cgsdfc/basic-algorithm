#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
区间贪心，找出N个区间中，不相交的最大区间数。
*/

typedef struct Interval Interval;
struct Interval {
	int start, end;
};

#define MAXN 105

Interval ints[MAXN];

/*
排序逻辑：
满足先选左端点最大的，如果左端点相同，则选右端点最小的。
左端点越大，则区间离开原点越远，在此基础上，右端点越小，则区间越小。
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
		第一个区间是优先级最高的，必选。然后按优先顺序从高到低扫描，
		遇到与前一个区间不相交的，则选取，并且更新当前区间。
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
