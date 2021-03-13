#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
加满一次油后，假设有前面有N个加油站可以到达。
办法一：
去单价最低的加油站加满。
如果有单价相同的，则去最远那个。 

方法二：
去最远那个加油站加油，如果有相同远的，则去最便宜的那个。

方法三：
维护当前的公里数和花的钱数。
查找当前能到达的加油站，或者目的地。
如果无法达到任何地方，则输出无法到达。
否则，计算 开销/距离，其中开销是到达该加油站后，加满油所需的开销，
距离是当前位置到加油站的位置。 
选取最小值，去那个加油站。
这就保证了，这样使得开销尽量小，而距离尽量大。便于找到距离当前最远而开销最小的加油站。
*/ 

typedef struct Current {
	double oil; // 当前还剩多少油
	double dis; // 当前走了多远
	double cost; // 当前花了多少钱 
} Current;

typedef struct Station {
	double price;
	double dis;
} Station;

#define MAXN 505

/*
注意，hangzhou是出发地。
*/ 
Station stations[MAXN];

int CMP(const void*_a, const void*_b) {
	Station* a=_a,*b=_b;
	return a->dis==b->dis? 0 : (a->dis < b->dis ? -1 : 1);
}

/*
	最优加油策略：
	设当前加油站是now。在当前的油量可达范围，按距离从小到大内有若干加油站A。
	1. 若 A 为空，说明无法前进，输出max travel distance。
	2. 在A中查找距离最近且油价比now低的油站x，若找到，则在now加足够到 x的油，
		（若当前油量足够则不用加）。
		若x不存在，则找到A中油价最低的站y，并在now加满，然后前往y。
	当到达终点时算法结束，输出总价钱。
	
	解析：
	1. 每次加油不必加满，因为当前的油不一定最便宜，如果总是加满，则错过了前往
	前面更便宜的加油站，加更便宜的油的机会。
	2. 贪心体现在：每次寻找加油站时，选择的原则是寻找更低的油价，而不在乎是否要
	一次性行驶更长的距离。因为并不是加油的次数越少越好，相反，如果油站的分布是越到后面 
	越便宜，则应该频繁加油，使得当前的油的单位价格更低。
	3. 每次寻找油站，都在当前油量可达的范围内寻找，这一点我也是明白的，关键是在这些可达
	油站中选择的策略。
	4. 从贪心原则2出发，如果可达油站存在油价低于当前油站的，则会使后续路段的成本下降，因此优先
	选择。并且由于当前油价比后续贵，在不加满原则1下，在当前油站加的油不应该太多，保证到达下一站即可。
	可见在now加的油量，是由搜索的结果决定的。
	5. 如果4所说的油站不存在，即可达油站的油价都比now贵（或者等于now），
	则now的油比后续的便宜，所以应该在now尽量多加油，所以要加满。在可达油站中，仍要选择最便宜（或不变）的油站。
	6. 若4的情况下油多个油站比当前油站便宜，则应该去最近那个，因为去更远的油站，意味着要在当前油站（贵）多加，
	不符合贪心追求局部最优原则。 
	7. 若5的情况，有多个最小值，怎么办？ 暂时想不出来，先假设这样的情况不出现，如果出现了，则选取距离最近的。 
	8. 注意，可达油站的搜索范围是满油状态下，因为出发前是要在now加油的，最多可以加满（并且最优策略也有加满
	的情况），因此不是当前油量作为搜索范围。 
	*/
	
int main(int argc, char *argv[]) {
	Current cur={0,0,0};
	double Cmax, D, Davg;
	int N;
	int i;
	int now;
	
	freopen("./in2.txt","r",stdin);
	
	scanf("%lf%lf%lf%d",&Cmax,&D, &Davg, &N);
//	
//	printf("Davg %f\n", Davg);
//	
//	printf("D %f\n", D);
	
	for (i=0;i<N;++i) {
		Station s;
		scanf("%lf%lf", &s.price, &s.dis);
		stations[i]=s; 
	}
	/*
	把终点当作一个特殊的加油站，使其价格为0，
	则可以在其他距离等于D的真正加油站中被最优策略选出。
	*/
	stations[N].dis=D;
	stations[N].price=0; 
	qsort(stations, N+1, sizeof(Station), CMP);
	
	// 先检查是否存在0号加油站，因为初始油缸没有油。
	if (stations[0].dis) {
		// 但并不加油，因为加多少油和下一站的油价有关系。
		printf("The maximum travel distance = 0.00\n");
		return 0; 
	}
	
	now=0;
	// 到达最后一站，就说明能够到达终点。 
	while (now < N) {
		double minprice;
		int maxdis=Davg*Cmax; // 满油能去的范围。 
		int next=-1; // 下一站。 
		// 查找下一站，按照最优策略。
		int j;
		double oil; // 从当前站到下一站，要多少油。 
		
		// 注意，加入了终点特殊加油站后，总数变为N+1，最后一个站是N. 
		for (j=now+1;j<=N&&stations[j].dis-stations[now].dis <= maxdis;++j) {
			double price=stations[j].price;
			// 情况1：找距离最近的，最小价格的油站。 
			if (j==now+1 || price < minprice) {
				next=j;
				minprice=price;
				// 情况2：找距离最近的，比现在便宜的油站。 
				if (minprice < stations[now].price) {
					/*
					注：若情况2存在，则情况2不一定是最小价格，因为更小的可能在后面。
					如果情况2不存在，则找到的一定是最小的，并且大于等于now的油价。
					*/ 
					break;
				}
			}
		}
		
//		printf("now %d next %d\n", now, next);
		
		if (next == -1) {
			/*
			在满油状态找不到加油站，则最多能再开一个满油距离。
			*/ 
			printf("The maximum travel distance = %.2f\n", cur.dis + maxdis);
			return 0;
		}
		
		oil= (stations[next].dis - stations[now].dis) / Davg;
//		printf("dis %f price %f oil %f\n", stations[next].dis-stations[now].dis,
//		stations[now].price, oil);
//		
		if (minprice < stations[now].price) {
			// 情况1，加够到next的油。
			if (cur.oil < oil) {
				// 要加油。
				cur.cost += stations[now].price * (oil - cur.oil); // 补足oil。 
				cur.oil=0; 
			} else {
				// 不加油。
				cur.oil -= oil; 
			}
		} else {
			// 加满
			cur.cost += stations[now].price * (Cmax - cur.oil);
			cur.oil = Cmax - oil; 
		}
//		printf("cost %f\n", cur.cost);
		now=next;
	}
	
	printf("%.2f\n", cur.cost); 
	return 0;
}
