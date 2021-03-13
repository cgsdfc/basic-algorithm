#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // 点的个数。
int M; // 查询个数。

struct Point {
	int X, Y;
	char type;
};

#define MAXN 1005

Point p[MAXN];

int the[3]; // 直线的三个参数。

// 点坐标代入直线方程。 
int Eval(Point& a) {
	return the[0]+the[1]*a.X+the[2]*a.Y;
}

/*
对于每一个点，要么大于零，要么小于零，
要么是A，要么是B。
现在断言大于零的是A，小于零的是B，如果不成立，则必定
是相反的情况，即大于零的是B，小于零的是A成立。
对于全部点，断言要么全部成立，要么全部不成立，这样就是正确的分类器。
*/ 
bool Check(Point& a) {
	int v=Eval(a);
	return ('A'==a.type && v>0) || ('B'==a.type && v<0);
}

// 判定当前直线是否能完美分割两类点。 
bool Judge() {
	bool flag=Check(p[0]);
	for (int i=1;i<N;++i) {
		if (Check(p[i]) != flag) {
			// 分类不一致。 
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	scanf("%d%d",&N,&M);
	for (int i=0;i<N;++i) {
		// 输入N个点。
		char str[5];
		scanf("%d%d%s", &p[i].X, &p[i].Y, str);
		p[i].type=str[0];
	}
	for (int i=0;i<M;++i) {
		// 输入M条直线。
		for (int j=0;j<3;++j) {
			scanf("%d", &the[j]);
		}
		bool ans=Judge();
		puts(ans?"Yes":"No");
	}
	
	return 0;
}
