#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ע�⣬radix�ɲ���2-36����Ŀֻ��˵��36����������ʾ36����λ��
��radix����Զ����36������˵16���ƿ���ʹ��0-9����������16��10��

���ԣ�
1. ��radix��ö�ٱ����ö��֣�����radix����ǳ��󣬱ض���ʱ��
2. radix���½�����ȷ�ϣ������Ͻ���ô�졣
3. radix��ô��LLҲ���������ô�Ƚ���������N1��N2.

�Ͻ����⣺
�Ͻ��ѡȡ��Ҫ��֤һ�������⣬Ҳ�������޴󣬷���ᳬʱ��
��ô��x���������£�ʲôʱ��r����أ���������ȡ10��ʱ��
��Ϊ����Խ����ÿλԽ����rԽС����ֻ��1λ��ʱ������������ֻ��35��
��������36�����ţ�������r-1�������Ժ�r�޹ء���r�й�����r�������ִ���10��
��ʱ����ֵΪr������r���ȡ��x��
ͬʱ�Ͻ粻С���½磬����r���Ͻ����r���½磬
������r���Ͻ�=max(x, r���½�)+1����1��Ϊ�˱�֤r���Ͻ������r�Ľ⡣
*/

typedef long long LL;

int Dig(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  if ('a' <= c && c <= 'z')
    return c - 'a' + 10;
  return -1;
}

#define MAXS 15

/*
������ת��ʮ����ʱ�ж������
��Ϊ����һ������ˣ��ᵼ�º����������
*/
LL To(char str[], int len, LL radix) {
  LL ans = 0;
  int i;
  for (i = 0; i < len; ++i) {
    int d = Dig(str[i]);
    if (ans < 0) {
      return -1; // �����
    }
    ans = ans * radix + d;
  }
  return ans;
}

/*
ע�⣬��ͬ��һ�����֣��ڲ�ͬ��radix�£��ó���10����ֵ���Բ���ͬ��
����һ��������ȫ�㡣 �����������rʹ��str��r�µ���x�������x==0��
����r��Ψһ�ġ� ����ֻ��Ҫ��ͨ�Ķ��ֲ��Ҽ��ɣ����ø��½硣
*/
LL Search(char str[], int len, LL left, LL right, LL x) {
  LL mid;
  LL y;
  while (left <= right) {
    mid = (left + right) / 2;
    y = To(str, len, mid);

    //		printf("mid %d y %lld\n", mid, y);

    if (y == x)
      return mid;
    if (y < 0 || y > x) { // y���
      // ��Сradix
      right = mid - 1;
    } else {
      // ����radix
      left = mid + 1;
    }
  }
  return -1;
}

int IsZero(char str[], int len) {
  int i;
  for (i = 0; i < len; ++i) {
    if (str[i] != '0')
      return 0;
  }
  return 1;
}

// ������λ��ʾ��С���ܵ�radix��
int MinRadix(char str[], int len) {
  int max = -1;
  int i;
  for (i = 0; i < len; ++i) {
    int d = Dig(str[i]);
    if (d > max) {
      max = d;
    }
  }
  return max + 1;
}

#define Max(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[]) {
  char s1[MAXS];
  char s2[MAXS];
  char *str;
  int len1, len2, len;
  int tag;
  int radix;
  LL x;
  LL ans;
  LL left, right;

  freopen("./in.txt", "r", stdin);

  scanf("%s%s%d%d", s1, s2, &tag, &radix);
  len1 = strlen(s1);
  len2 = strlen(s2);

  if (strcmp(s1, s2) == 0) {
    // ������ͬ
    printf("%d\n", radix);
    return 0;
  }
  if (IsZero(s1, len1) || IsZero(s2, len2)) {
    // ������ͬ������һ����0�����޽⡣
    puts("Impossible");
    return 0;
  }

  if (tag == 1) {
    x = To(s1, len1, radix);
    str = s2;
    len = len2;
  } else {
    x = To(s2, len2, radix);
    str = s1;
    len = len1;
  }

  assert(x != -1); // ��һ������Ӧ�������
  left = MinRadix(str, len);
  right = Max(left, x) + 1; // ���е�r�ó���y����xС��

  //	printf("s1 %s s2 %s tag %d x %lld str %s left %d right %d\n",
  //	s1, s2, tag, x, str, left, right);

  ans = Search(str, len, left, right, x);
  if (ans != -1) {
    printf("%lld\n", ans);
  } else {
    puts("Impossible");
  }

  return 0;
}
