#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
注意，radix可不是2-36，题目只是说用36个符号来表示36个数位，
但radix可以远大于36，比如说16进制可以使用0-9，但是明显16比10大。

所以：
1. 对radix的枚举必须用二分，否则radix如果非常大，必定超时。
2. radix的下界容易确认，但是上界怎么办。
3. radix这么大，LL也会溢出，怎么比较两个大数N1，N2.

上界问题：
上界的选取，要保证一定包括解，也不能无限大，否则会超时。
那么在x不变的情况下，什么时候r最大呢？就是数字取10的时候，
因为数字越长，每位越大，则r越小，而只有1位的时候，这个数字最大只有35，
（受限于36个符号，而不是r-1），所以和r无关。与r有关且令r最大的数字串是10，
此时它的值为r，所以r最大取到x。
同时上界不小于下界，所以r的上界大于r的下界，
于是令r的上界=max(x, r的下界)+1，加1是为了保证r的上界包含了r的解。
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
必须在转换十进制时判断溢出，
因为其中一步溢出了，会导致后续结果错误。
*/
LL To(char str[], int len, LL radix) {
  LL ans = 0;
  int i;
  for (i = 0; i < len; ++i) {
    int d = Dig(str[i]);
    if (ans < 0) {
      return -1; // 溢出。
    }
    ans = ans * radix + d;
  }
  return ans;
}

/*
注意，相同的一串数字，在不同的radix下，得出的10进制值绝对不相同。
除非一串数字是全零。 于是如果存在r使得str在r下等于x，则除非x==0，
否则r是唯一的。 所以只需要普通的二分查找即可，不用搞下界。
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
    if (y < 0 || y > x) { // y溢出
      // 减小radix
      right = mid - 1;
    } else {
      // 增大radix
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

// 最大的数位表示最小可能的radix。
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
    // 两数相同
    printf("%d\n", radix);
    return 0;
  }
  if (IsZero(s1, len1) || IsZero(s2, len2)) {
    // 两数不同，其中一个是0，则无解。
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

  assert(x != -1); // 第一个数不应该溢出。
  left = MinRadix(str, len);
  right = Max(left, x) + 1; // 所有的r得出的y都比x小。

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
