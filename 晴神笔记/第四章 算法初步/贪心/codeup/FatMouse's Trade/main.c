#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 1005

typedef struct Room {
	int J; // 利润 
	int F; // 代价 
	double JF; // J/F.
} Room;

/*
贪心策略：
计算每个房间用一单位的F，能得到多少J，从小到大排序。
按此顺序考虑所有房间，用剩余的钱尽量买当前房间的J，如果有多余的钱就继续
下一个房间。
*/
 
Room room[MAXN];

int CMP(const void*_a, const void*_b) {
	Room* a=(Room*)_a;
	Room* b=(Room*)_b;
//	return (int)(b->JF - a->JF);
/*
浮点数的CMP函数，不能直接相减然后转为int。要用比较运算符。 
*/ 
	return a->JF==b->JF?0:(a->JF<b->JF?1:-1);
}

double Min(double a, double b) {
	return a<b?a:b;
}

int main(int argc, char *argv[]) {
	int M, N;
	
	freopen("./in.txt", "r", stdin);
	
	while (scanf("%d%d",&M,&N) != EOF && !(M==-1&&N==-1)) {
		int i;
		double ans=0;
		double money=M;
		
		for (i=0;i<N;++i) {
			scanf("%d%d", &room[i].J, &room[i].F);
			room[i].JF = (double)room[i].J / room[i].F;
		}
		qsort(room, N, sizeof(Room), CMP);
		
//		for (i=0;i<N;++i) {
//			printf("J %d F %d J/F %f\n", room[i].J, room[i].F, room[i].JF);
//		}
		
		for (i=0;i<N;++i) {
			if (money > 0) {
				double pay=Min(room[i].F, money);
				ans += pay * room[i].JF;
				money -= pay;
			} else {
				break;
			}
		}
		printf("%.3f\n", ans);
	}
	
	return 0;
}
