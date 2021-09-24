#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
������Ȼ����С��ֵ�ض�������������֮�������
ʱ�临�Ӷ� NlogN.
*/

int N;
#define MAXN 1005

int a[MAXN];
// ���ֵ���趨�Ǹ�������ÿ��Ԫ��x�����ֵ��
const int INF = 100000;

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + N);
  int ans = INF;
  for (int i = 0; i < N - 1; ++i) {
    int diff = a[i + 1] - a[i];
    if (diff < ans) {
      ans = diff;
    }
    if (ans == 0) {
      break; // ����ֵ����С��0.
    }
  }
  printf("%d\n", ans);

  return 0;
}
