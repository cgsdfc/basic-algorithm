#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 105

char str[MAXN];
int N;

/*
计算P之前，P和T之间，T之后的A个数，分别为n1，n2，n3。
是否满足其中之一:
1. n1=n3>=0, n2=1
2. n1=n3=0, n2>=1
3. n1*n2=n3, n1>=1, n2>=1
*/
int Judge(char A[], int len) {
  int numP = 0;
  int numA = 0;
  int numT = 0;
  int i;
  int posP;
  int posT;
  int n1, n2, n3; // 三种位置的A的数量。

  for (i = 0; i < len; ++i) {
    switch (A[i]) {
    case 'P':
      ++numP;
      posP = i;
      break;
    case 'A':
      ++numA;
      break;
    case 'T':
      ++numT;
      posT = i;
      break;
    }
  }

  //	printf("numP %d numA %d numT %d\n", numP, numA, numT);

  // 必须只有PAT三种字符。
  if (numP + numA + numT != len) {
    return 0;
  }
  if (numP != 1 || numT != 1 || numA == 0) {
    // P，T必须各有一个。A不能没有。
    return 0;
  }
  n1 = posP;
  n2 = posT - posP - 1;
  n3 = len - posT - 1;
  assert(n1 + n2 + n3 == numA);

  //	printf("n1 %d n2 %d n3 %d\n", n1,n2,n3);

  // AAPAPAA
  if (n2 == 1 && n1 == n3)
    return 1;
  // PAAAAT
  if (n1 == 0 && n3 == 0 && n2 > 0)
    return 1;
  // AAPAAPAAAA
  if (n1 * n2 == n3 && n3 > 0)
    return 1;
  return 0;
}

int main(int argc, char *argv[]) {
  freopen("./in.txt", "r", stdin);

  scanf("%d", &N);
  getchar(); // 数字后面gets，必须吃掉换行。

  while (N--) {
    int ans;
    gets(str);
    ans = Judge(str, strlen(str));
    puts(ans ? "YES" : "NO");
  }

  return 0;
}
