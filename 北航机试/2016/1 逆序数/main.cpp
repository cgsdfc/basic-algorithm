#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
���ַ����������֣�Ȼ��������ֵ��������ַ��������������ֵ��
*/

// 10e6 �����֣��ַ�����20���ˡ�
#define MAXN 20

char s1[MAXN];
char s2[MAXN];

int main(int argc, char **argv) {
  scanf("%s", s1);
  int len1 = strlen(s1);
  int N = 0, M = 0; // ����������������
  int len2 = 0;
  /*
  ע��N=0����M=0, 0��0�Ķ��ٱ���
  ��û�����塣��Ϊ����˵��1,2,3������
  */

  for (int i = 0; i < len1; ++i) {
    char d = s1[i];
    char d2 = s1[len1 - i - 1];
    s2[len2++] = d2;
    N = N * 10 + d - '0';
    M = M * 10 + d2 - '0';
  }
  s2[len2] = 0;
  if (M % N == 0) {
    int k = M / N;
    printf("%d*%d=%d\n", N, k, M);
  } else {
    printf("%s %s\n", s1, s2);
  }
  return 0;
}
