#include <cassert>
#include <cstdio>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����һ������ͼ�������ټ��ϼ�������ʹ���Ϊ��ͨͼ��
��ÿ����ͨ��������һ���㣬Ȼ��ʹ������ͨ����С��������
��֯��һ��������V-1��V����ͨ�����ĸ�����
�ò��鼯ͳ����ͨ�����������ɡ�
*/

#define MAXN 1005

int father[MAXN];
int N;
int M;

int Find(int x) {
  int a = x;
  while (x != father[x]) {
    x = father[x];
  }
  // ·��ѹ����
  while (a != father[a]) {
    int temp = father[a];
    father[a] = x;
    a = temp;
  }
  return x;
}

void Union(int a, int b) {
  int faA = Find(a);
  int faB = Find(b);
  if (faA != faB) {
    father[faA] = faB;
  }
}

int main(int argc, char **argv) {
  while (scanf("%d", &N), N) {
    for (int i = 1; i <= N; ++i) {
      // ��ʼ�����鼯��
      father[i] = i;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
      int a, b;
      // ����һ���ߡ�
      // ע��һ���ߣ�ʵ���ϸ�������������ab����ͨ�ģ�
      // ��ͬ��һ�����ϣ�ֻҪ���ղ��鼯��Union�������ɣ�
      // ��ͨ��ϵ�����Ƕ���ģ���Ϊ��֮ǰ�Ĺ�ϵ�����Ѿ�֪��
      // abͬ��һ�����ϡ�
      scanf("%d%d", &a, &b);
      Union(a, b);
    }
    // ͳ����ͨ��������������ͳ�Ƽ����������ڵ�������
    int num = 0;
    for (int i = 1; i <= N; ++i) {
      if (father[i] == i) {
        ++num;
      }
    }
    assert(num >= 1);
    printf("%d\n", num - 1);
  }
  return 0;
}
