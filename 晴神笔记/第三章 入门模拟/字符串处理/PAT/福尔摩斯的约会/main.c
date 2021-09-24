#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char W[7][5] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

#define MAXN 65

int GetTime(char i) {
  if (isdigit(i)) {
    return i - '0';
  }
  return i - 'A' + 10;
}

/*
����Ĺؼ���������⣬����Ŀ����ת��ΪҪ��ʲô��
*/

int main(int argc, char *argv[]) {
  int i;
  char str[4][MAXN];
  int len[4];
  int res[3];

  //	freopen("./in.txt", "r", stdin);

  for (i = 0; i < 4; ++i) {
    scanf("%s", str[i]);
    len[i] = strlen(str[i]);
  }

  for (i = 0; i < len[0] && i < len[1]; ++i) {
    char c = str[0][i];
    /*
    ע�⣬һ������ֻ��7�죬��˲���ҪA-Z��A-G���ɡ�
    */
    if (c == str[1][i] && ('A' <= c && c <= 'G')) {
      res[0] = c;
      break;
    }
  }
  for (++i; i < len[0] && i < len[1]; ++i) {
    char c = str[0][i];
    if (c == str[1][i] && (isdigit(c) || ('A' <= c && c <= 'N'))) {
      res[1] = c;
      break;
    }
  }
  for (i = 0; i < len[2] && i < len[3]; ++i) {
    char c = str[2][i];
    if (c == str[3][i] && isalpha(c)) {
      res[2] = i;
      break;
    }
  }

  //	printf("%c %c %d\n", res[0], res[1], res[2]);

  printf("%s %02d:%02d\n", W[res[0] - 'A'], GetTime(res[1]), res[2]);

  return 0;
}
