#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
typedef struct Location {
  int x, y; // ��ǰλ�õ��У��С�
} Location;

int N, M;          // �Թ���������������
int A[MAXN][MAXN]; // �Թ���0��ʾ�����0������ͨ��1��ʾͨ����û�߹���2��ʾ�߹���
Location in, out;  // ��ڣ����ڡ�
int has;           // �Ƿ��н⡣

/*
һ����·����󳤶ȣ��Ǹ������Թ������е㡣
*/
#define MAXP 400

struct {
  Location data[MAXP];
  int len;
} path;

// ˳���������¡�
const Location Dir[] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int Min(int a, int b) { return a < b ? a : b; }
int Max(int a, int b) { return a > b ? a : b; }

void DFS(Location now) {
  int i;
  int j;
  Location a, b;

  if (now.x == out.x && now.y == out.y) {
    // �ﵽ���ڣ����·����
    for (i = 0; i < path.len; ++i) {
      printf("(%d,%d)%s", path.data[i].x, path.data[i].y,
             i == path.len - 1 ? "\n" : "->");
    }
    has = 1;
    return;
  }

  /*
  ��֦�߼���
  ��鵱ǰλ��now���յ�out֮��ľ�����Ƿ����һ�л�һ�в�ͨ��
  �����ж�û��1������У���϶����ܴ�now�ﵽout��
  */
#if 0	 
	a.x=Min(now.x, out.x);
	a.y=Min(now.y, out.y);
	b.x=Max(now.x, out.y);
	b.y=Max(now.y, out.y);
	
	for (i=a.x;i<=b.x;++i) {
		int ok=0;
		for (j=a.y;j<=b.y;++j) {
			if (A[i][j] == 1) {
				ok=1;
				break;
			}
		}
		if (!ok) {
			// ��һ��ǽ����һ�ж���ͨ��
			return; 
		}
	}
	for (j=a.y;j<=b.y;++j) {
		int ok=0;
		for (i=a.x;i<=b.x;++i) {
			if (A[i][j] == 1) {
				ok=1;
				break;
			}
		}
		if (!ok) {
			// ��һ�в�ͨ��
			return; 
		}
	}
#endif

  for (i = 0; i < 4; ++i) {
    Location next = {now.x + Dir[i].x, now.y + Dir[i].y};
    // ���next�Ƿ���ߡ�
    if (1 <= next.x && next.x <= N && 1 <= next.y && next.y <= M &&
        A[next.x][next.y] == 1) {
      A[next.x][next.y] = 2; // �߹���
      path.data[path.len++] = next;
      DFS(next);
      --path.len;
      A[next.x][next.y] = 1; // ���ߡ�
    }
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  while (scanf("%d%d", &N, &M) != EOF) {
    int i;
    for (i = 1; i <= N; ++i) {
      int j;
      for (j = 1; j <= M; ++j) {
        scanf("%d", &A[i][j]);
      }
    }
    scanf("%d%d", &in.x, &in.y);
    scanf("%d%d", &out.x, &out.y);
    has = 0;
    path.len = 1;
    path.data[0] = in;
    A[in.x][in.y] = 2;
    DFS(in);
    if (!has) {
      puts("-1");
    }
  }
  return 0;
}
