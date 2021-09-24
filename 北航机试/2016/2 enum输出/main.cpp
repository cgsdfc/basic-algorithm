#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
在一个字符串内扫描三个东西：
标志符，可选的等号，可选的数字（十进制整数，可能为负数）。
*/
// 输入的长度
#define MAXL (1000000 + 5)
// 一个项的长度
#define MAXT (1000 + 5)

char line[MAXL], term[MAXT];

bool IsBegin(char c) { return c == '_' || isalpha(c); }
bool IsMid(char c) { return c == '_' || isalnum(c); }
bool IsNumBegin(char c) { return c == '-' || c == '+' || isdigit(c); }

void Solve(char str[], int len) {
  int i = 0;
  int tlen = 0;
  int value = 0;

  // 先跳到大括号里面。这样就去掉了enum和名字。
  while (i < len && str[i] != '{') {
    ++i;
  }

  while (i < len) {
    int now;
    while (i < len && !IsBegin(str[i])) {
      ++i;
    }
    if (i >= len) {
      break;
    }
    // 收集标志符。
    tlen = 0;
    while (i < len && IsMid(str[i])) {
      term[tlen++] = str[i++];
    }
    term[tlen] = 0;
    printf("%s ", term);

    // 确定value的值。
    while (i < len && isspace(str[i])) {
      ++i; // 等号之前可能有空格。
    }
    // 标志符后面肯定有其他字符，不可能到达结束。
    if (str[i] != '=') {
      now = value;
      ++value;
    } else {
      ++i;
      tlen = 0;
      // 接受后面的数字。
      while (i < len && isspace(str[i])) {
        ++i;
      }
      assert(IsNumBegin(str[i]));
      // 保证数字合法。
      while (i < len && IsNumBegin(str[i])) {
        term[tlen++] = str[i++];
      }
      term[tlen] = 0;
      now = atoi(term);
      value = now + 1;
    }
    printf("%d\n", now);
  }
}

int main(int argc, char **argv) {
  gets(line);
  Solve(line, strlen(line));

  return 0;
}
