#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100010

// �ӽڵ�1���ڵ�1����������N��˳ʱ����롣
//����������飬�Ϳ��Եó���������֮���˳ʱ����롣
//ע�⣬����Ҫ2x2����MAXN����ܴ����Ա����ʡʱ��ռ䡣
//���ⷨ�ռ�O(n)������ʱ��ΪO(n)��һ����ѯ��ʱ��O(1)��
//����������֮��ľ������Сֵ������˳ʱ��������ʱ��������С�ߡ�
//������Ӽ��ܾ���ͣ��ʼ���˳ʱ����뼴�ɡ�
int dis[MAXN];

int main(int argc, char *argv[]) {
  int n;
  int sum = 0;
  int i;
  int m; // ��ѯ��Ŀ��

  scanf("%d", &n); // �ڵ�����
  for (i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    dis[i] = sum;
    sum += x;
  }

  scanf("%d", &m);
  for (i = 0; i < m; ++i) {
    int u, v;
    int d1, d2;
    int res;

    scanf("%d%d", &u, &v);
    if (u > v) {
      // ��֤uС��v��
      int tmp = u;
      u = v;
      v = tmp;
    }
    assert(u <= v);
    u--;
    v--;
    d1 = dis[v] - dis[u];
    d2 = sum - d1;
    res = d1 < d2 ? d1 : d2;
    printf("%d\n", res);
  }

  return 0;
}
