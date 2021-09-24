#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�Ȼ��ڵ�ǰ�Թ��������������ڵ�ǰ�Թ��ﰲȫ�Ķ�����
Ȼ���Թ��е���һ��״̬��
*/

#define MAXN 10
const int N = 8;     // �̶���С���Թ���
char A[MAXN][MAXN];  // �Թ���
int inq[MAXN][MAXN]; // ����߹���·��
bool ans;

struct Point {
  int x;
  int y;
  bool operator==(Point p) { return x == p.x && y == p.y; }
};

const Point in = {7, 0};  // ���½ǡ�
const Point out = {0, 7}; // ���Ͻǡ�

// 9 ��������
const Point Dir[9] = {{0, 1},   {0, -1}, {1, 0}, {-1, 0}, {-1, 1},
                      {-1, -1}, {1, -1}, {1, 1}, {0, 0}};

void Print(void) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%c", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

bool HasStone(void) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i][j] == 'S')
        return true;
    }
  }
  return false;
}

void DFS(Point now) {
  if (A[now.x][now.y] == 'S') {
    // �ߵ�һ���ط���Ȼ��ʯͷ��������
    return;
  }
  if (now == out) {
    // �ߵ��˳��ڣ�����û��ʯͷ��
    ans = true;
    return;
  }
  /*
  ���ʯͷȫ����ʧ�ˣ���ô�ض����Ե��
  */
  if (!HasStone()) {
    ans = true;
    return;
  }

  /*
  ���ڵ�ǰ�Թ��ҵ���ȫ������
  Ȼ��ˢ���Թ������ݵ�temp����
  */
  Point points[10];
  int len = 0;
  for (int i = 0; i < 9; ++i) {
    Point v = {now.x + Dir[i].x, now.y + Dir[i].y};
    if (0 <= v.x && v.x < N && 0 <= v.y && v.y < N && A[v.x][v.y] != 'S' &&
        (!inq[v.x][v.y] || (!Dir[i].x && !Dir[i].y))) {
      points[len++] = v;
    }
  }
  /*
  ԭ�ز������ǰ�ȫ�ģ����Աض���һ��������
  */
  assert(len);

  /*
  ��ʯͷ���䡣������ǰһ�и��ǵ�ǰ�У���0��ȫ��Ϊƽ�ء�
  ����յ�ı�ǲ���Ҫ��
  */
  char temp[MAXN][MAXN];
  for (int i = N - 1; i >= 0; --i) {
    if (i == 0) {
      for (int j = 0; j < N; ++j) {
        A[i][j] = '.';
      }
    } else {
      for (int j = 0; j < N; ++j) {
        A[i][j] = A[i - 1][j];
      }
    }
  }

  memcpy(temp, A, sizeof(temp));
  for (int i = 0; i < len; ++i) {
    Point p = points[i];
    inq[p.x][p.y] = 1;
    DFS(p);
    memcpy(A, temp, sizeof(temp));
    inq[p.x][p.y] = 0;
  }
}

int main(int argc, char **argv) {
  int T;

#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  scanf("%d", &T);

  for (int k = 1; k <= T; ++k) {
    for (int i = 0; i < N; ++i) {
      getchar();
      for (int j = 0; j < N; ++j) {
        A[i][j] = getchar();
      }
    }
    getchar();
    //		continue;

    ans = false;
    memset(inq, 0, sizeof(inq));
    DFS(in);
    /*
    Case #1: Yes
    Case #2: No
    */
    printf("Case #%d: %s\n", k, ans ? "Yes" : "No");
  }
  return 0;
}
