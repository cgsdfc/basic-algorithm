#include <cstdio>

/*
��һ��bool�����¼��Щ�㱻Ϳɫ���ɡ�
�õ���ɢ�е�˼�롣
*/

// �����ǷǸ����������100.
#define MAXN 105

bool A[MAXN][MAXN];

struct Point {
  int X, Y;
};

struct Retangle {
  Point up, down;

  void Draw() {
    // ע�⣬һ����λ�����������½ǵĵ������ʾ��
    for (int i = down.X; i < up.X; ++i) {
      for (int j = down.Y; j < up.Y; ++j) {
        A[i][j] = true;
      }
    }
  }
};

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;

int main(int argc, char **argv) {
  scanf("%d", &N);
  while (N--) {
    Retangle r;
    scanf("%d%d%d%d", &r.down.X, &r.down.Y, &r.up.X, &r.up.Y);
    r.Draw();
  }
  int ans = 0;
  for (int i = 0; i < MAXN; ++i) {
    for (int j = 0; j < MAXN; ++j) {
      if (A[i][j]) {
        ++ans;
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
