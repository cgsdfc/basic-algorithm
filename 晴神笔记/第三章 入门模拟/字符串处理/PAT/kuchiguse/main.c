#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXM 260
#define MAXN 110

char lines[MAXN][MAXM];
int lens[MAXN];

int PreFind(int n) {
  /*
  若有空字符串和非空字符串，则必为nai。
  若全部是空字符串，则也是nai。
  即，若有空字符串则必是nai。
  */
  int i;
  for (i = 0; i < n; ++i) {
    if (!lens[i])
      return 1;
  }
  return 0;
}

int Find(int n) {
  int i;
  for (i = 0;; ++i) {
    char c = lines[0][lens[0] - i - 1];
    int j;
    int res = 1;

    for (j = 1; j < n; ++j) {
      /*
      应该先求所有line的最短长度minLen，再此范围内枚举，
      则不存在越界的问题。
      */
      if (lens[j] - i - 1 < 0 || lines[j][lens[j] - i - 1] != c) {
        res = 0;
        break;
      }
    }
    if (!res)
      break;
  }
  return i;
}

int Find2(int n, int minlen) {
  int ans = 0;
  int i;
  for (i = 0; i < minlen; ++i) {
    int ok = 1;
    int j;
    /*
    从后向前枚举比较麻烦，需要知道每个line的长度，
    反转后则方便得多。
    */
    char c = lines[0][lens[0] - 1 - i];
    for (j = 1; j < n; ++j) {
      if (lines[j][lens[j] - 1 - i] != c) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      ++ans;
    } else {
      break;
    }
  }
  return ans;
}

/*
Sample Input 1:
3
Itai nyan~
Ninjin wa iyadanyan~
uhhh nyan~
Sample Output 1:
nyan~
Sample Input 2:
3
Itai!
Ninjinnwaiyada T_T
T_T
Sample Output 2:
nai
*/

int main(int argc, char *argv[]) {
  int n;
  int i;
  int len;
  int minlen = MAXM;

  // 注意读入整数后再读入一行，则整数后的换行必须先去掉，否则紧接着的
  // 一行就是空字符串了。
  scanf("%d", &n);
  getchar();
  for (i = 0; i < n; ++i) {
    gets(lines[i]);
    lens[i] = strlen(lines[i]);
    if (lens[i] < minlen) {
      minlen = lens[i];
    }
  }

  if (PreFind(n)) {
    // 有空字符串
    puts("nai");
    return 0;
  }

  len = Find(n);
  if (!len) {
    puts("nai");
  } else {
    for (i = lens[0] - len; i < lens[0]; ++i) {
      putchar(lines[0][i]);
    }
    putchar('\n');
  }
  return 0;
}
