#include <iostream>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int M,N,L,T;

#define MAXM 1300
#define MAXN 130
#define MAXL 65

int A[MAXL][MAXM][MAXN];
int inq[MAXL][MAXM][MAXN]; // 标记坐标是否在队列中。 

int ans; // 总体积。

const int X[]={0,0,1,-1,0,0};
const int Y[]={1,-1,0,0,0,0};
const int Z[]={0,0,0,0,1,-1};

// 1286 by 128); L (≤60) is the number of slices o

struct Point {
	int x,y,z;
};

// 是否需要将p入队。 
int Judge(Point p) {
	if (!(0<=p.z&&p.z<L)) return 0;
	if (!(0<=p.x&&p.x<M)) return 0;
	if (!(0<=p.y&&p.y<N)) return 0;
	if (inq[p.z][p.x][p.y]) return 0;
	if (!A[p.z][p.x][p.y]) return 0;
	return 1;
}

int BFS(Point v) {
	int tot=1; // 本次遍历的块的体积。 
	queue<Point> q;
	q.push(v);
	inq[v.z][v.x][v.y]=1;
	
	while (!q.empty()) {
		int i;
		Point p=q.front();
		q.pop();
		for (i=0;i<6;++i) {
			Point k={p.x+X[i], p.y+Y[i], p.z+Z[i]};
			if (Judge(k)) {
				inq[k.z][k.x][k.y]=1;
				q.push(k);
				++tot;
			}
		}
	}
	return tot;
}

int main(int argc, char *argv[]) {
	int i,j,k;
	
	freopen("./in.txt","r",stdin);
	
	scanf("%d%d%d%d",&M,&N,&L,&T);
	for (k=0;k<L;++k) {
		// 输入L层。每层是M*N矩阵。 
		for (i=0;i<M;++i) {
			for (j=0;j<N;++j) {
				scanf("%d", &A[k][i][j]);
			}
		} 
	}
	
	for (k=0;k<L;++k) {
		for (i=0;i<M;++i) {
			for (j=0;j<N;++j) {
				if (A[k][i][j] == 1 && inq[k][i][j] == 0) {
					Point p={i,j,k};
					int V=BFS(p);
					if (V >= T) {
						ans += V;
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
