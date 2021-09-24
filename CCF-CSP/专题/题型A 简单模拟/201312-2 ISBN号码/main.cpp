#include <cctype>
#include <cstdio>
#include <cstring>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  int p = 1;
  int ans = 0;
  int i = 0;
  char ch;
  char code;
  char str[20];
  int len = 0;

  gets(str);
  len = strlen(str);
  code = str[len - 1];
  for (int i = 0; i < len; ++i) {
    ch = str[i];
    if (isdigit(ch)) {
      if (p <= 9) {
        ans += p * (ch - '0');
        ++p;
      }
    }
  }

  ans %= 11;
  char code2 = ans == 10 ? 'X' : '0' + ans;

  if (code2 == code) {
    puts("Right");
  } else {
    str[len - 1] = code2;
    puts(str);
  }

  return 0;
}
