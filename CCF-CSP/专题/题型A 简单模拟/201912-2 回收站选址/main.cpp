#include <cstdio>
#include <set> // 查询坐标是否存在。
using namespace std;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 每种得分的选址数。 
int ans[10];

typedef pair<int,int> Point;

const Point Dir1[]={{0,1},{1,0},{0,-1},{-1,0}};
const Point Dir2[]={{-1,-1},{-1,1},{1,-1},{1,1}};

set<Point> ps;
typedef set<Point>::iterator It;

bool Judge(Point& a) {
	// 判定a是否有资格。
	for (int i=0;i<4;++i) {
		Point b=a;
		b.first+=Dir1[i].first;
		b.second+=Dir1[i].second;
		if (!ps.count(b)) return false;
	}
	return true;
}

void Count(Point& a) {
	int score=0;
	for (int i=0;i<4;++i) {
		Point b=a;
		b.first+=Dir2[i].first;
		b.second+=Dir2[i].second;
		if (ps.count(b)) {
			++score;
		}
	}
	ans[score]++;
}

/*
本题N较小，故NlogN即可。
x y坐标接近int极限，用map，散列不行。 
*/ 
int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	while (N--) {
		Point p;
		scanf("%d%d", &p.first, &p.second);
		ps.insert(p);
	}
	for (It it=ps.begin();it!=ps.end();++it) {
		Point p=*it;
		if (Judge(p)) {
			Count(p);
		}
	}
	for (int i=0;i<5;++i) {
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
