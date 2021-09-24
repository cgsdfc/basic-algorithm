#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ֻҪͨ��ϵͳ��һ���������������ж˵㣬������������
��Ϊ��Ŀ������������������ͨ���޻������һ��ͼ������������ϵ��
�����ض�������

����ò��鼯�ж������������Ƿ������
1. ��ͨ�� ����Ԫ�صĸ�����ͬ��
2. �޻�����ͨ���� E=V-1��
*/

int N, M; // N���ڵ㣬M����·��

#define MAXN 1005

/*
BUG�㣺
1. ��һ�Σ��𰸴���0������ѭ�������⣬NMͬʱΪ0�Ž�����
2. �ڶ��㣬��ʱ0��FindҪ·��ѹ������Ϊÿ�β������N��M�ξ���MN��
����M=N^2��������N^3�ĸ��Ӷȡ�N��1000��N�����η�����10e9�����ȳ�ʱ��
�Ż����Ӷ���M������Nƽ������10e6��
*/

int father[MAXN];

int Find(int x) {
  int a = x;
  while (x != father[x]) {
    x = father[x];
  }
  // ��ʱ�ˣ�����ѹ����
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
  // ע�⣬NM��Ϊ0ʱ�����������ֻҪ����һ����Ϊ���Ҫ����
  while (scanf("%d%d", &N, &M), (N || M)) {
    bool flag = M == N - 1;
    for (int i = 1; i <= N; ++i) {
      father[i] = i;
    }
    /*
    ���ò��鼯�ж���ͨ�ԣ�
    ���鼯����Ե��ɻ��ıߣ����ó�ɭ�֡�
    ������Ƿ�ֻ��һ�����ϼ��ɡ�
    */
    while (M--) {
      int a, b;
      // ���رߣ����Ի���
      scanf("%d%d", &a, &b);
      Union(a, b);
    }
    int num = 0; // ���ٸ����ϡ�
    for (int i = 1; i <= N; ++i) {
      if (father[i] == i) {
        ++num; // һ�����ڵ����һ�����ϡ�
      }
    }
    puts(flag && num == 1 ? "Yes" : "No");
  }

  return 0;
}
