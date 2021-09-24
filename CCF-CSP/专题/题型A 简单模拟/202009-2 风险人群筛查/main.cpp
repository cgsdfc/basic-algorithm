#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��������С��ֱ��ģ�⣬O(NK)��
*/

#define MAXT 1005
int T; // ���еĳ��ȡ�
int K; // �ж�Ϊ������������ֵ��
int N; // N���ˡ�

struct Point {
  int X, Y;
};

Point where[MAXT]; // һ������Ĺ켣��
Point up, down;    // ���յ����ľ�������

// �ж�p�Ƿ񾭹��������������ھ����ڣ������߽硣
bool In(Point &p) {
  // ע��up��ȫ�����궼�����ģ�down����С��
  return down.X <= p.X && p.X <= up.X && down.Y <= p.Y && p.Y <= up.Y;
}

int MaxLen() {
  // ����һ�������ڷ�����������������г��ȡ�
  int i = 0;
  int ans = -1;

  while (i < T) {
    while (i < T && !In(where[i])) {
      i++;
    }
    int j = i;
    while (j < T && In(where[j])) {
      j++;
    }
    int len = j - i;
    if (len > ans) {
      ans = len;
    }
    i = j;
  }
  return ans;
}

int in;   // ������
int stay; // ������

int main(int argc, char **argv) {
  scanf("%d%d%d", &N, &K, &T);
  scanf("%d%d%d%d", &down.X, &down.Y, &up.X, &up.Y);

  while (N--) {
    // N���˵Ĺ켣��
    for (int i = 0; i < T; ++i) {
      scanf("%d%d", &where[i].X, &where[i].Y);
    }
    int len = MaxLen();
    if (len > 0) {
      ++in;
    }
    if (len >= K) {
      ++stay;
    }
  }
  printf("%d\n", in);
  printf("%d\n", stay);

  return 0;
}
