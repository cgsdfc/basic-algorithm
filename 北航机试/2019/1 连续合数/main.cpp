#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
˫ָ�뷨ö�����������ĺ������У�����ĺ������С�
����ж������У������һ�����ɡ�

����������԰Ѹ��ӶȽ���O(N)����������ж����������Ӷ��� O(N * sqrtN)
*/

const int MAXN = 1e6 + 5;
bool p[MAXN];

void FindPrime() {
  // ɸ����
  for (int i = 2; i < MAXN; ++i) {
    if (!p[i]) {
      // i��������������ı�����
      for (int j = i * 2; j < MAXN; j += i) {
        p[j] = true;
      }
    }
  }
}

int N; // 1--N��

int main(int argc, char **argv) {
  scanf("%d", &N);
  FindPrime();

  int maxLen = 0;
  int start;
  int i = 4; // 1��2��3 �����Ǻ�����
  while (i <= N) {
    while (i <= N && !p[i]) {
      ++i; // p=true�Ǻ�����
    }
    int j = i;
    while (j <= N && p[j]) {
      ++j;
    }
    int len = j - i;
    //		for (int k=i;k<j;++k) {
    //			printf("%d%s", k,k==j-1?"\n":" ");
    //		}

    if (len > maxLen) {
      maxLen = len;
      start = i;
    }
    i = j;
  }
  for (int i = start, n = start + maxLen; i < n; ++i) {
    printf("%d%s", i, i == n - 1 ? "\n" : " ");
  }
  return 0;
}
