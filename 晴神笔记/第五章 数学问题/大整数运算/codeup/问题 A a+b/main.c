#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005

typedef struct Big {
  int d[MAXN];
  int len;
} Big;

char s1[MAXN], s2[MAXN];

Big a, b;

Big From(char str[]) {
  int i;
  Big c = {};

  c.len = strlen(str);
  for (i = 0; i < c.len; ++i) {
    //		if (str[i]=='-') abort();
    // 没有负数。
    c.d[i] = str[c.len - 1 - i] - '0';
  }
  return c;
}

/*
注意：所有操作都假设高精度在len后面的位是0，
所以任何一个高精度，都必须把d数组先清零。
*/
Big Add(Big a, Big b) {
  Big c = {};
  int i;
  int carry = 0;

  for (i = 0; i < a.len || i < b.len; ++i) {
    int temp = carry + a.d[i] + b.d[i];
    c.d[c.len++] = temp % 10;
    carry = temp / 10;
  }
  if (carry) {
    c.d[c.len++] = carry;
  }
  // 可能有前导零？
  //	while (c.len-1>=1&&c.d[c.len-1]==0) {
  //		--c.len;
  //	}
  return c;
}

void Print(Big c) {
  int i;
  for (i = c.len - 1; i >= 0; --i) {
    printf("%d", c.d[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  //	abort();
  while (scanf("%s%s", s1, s2) != EOF) {
    a = From(s1);
    b = From(s2);
    //		printf("a ");
    //		Print(a);
    //		printf("b ");
    //		Print(b);

    a = Add(a, b);
    Print(a);
  }
  return 0;
}
