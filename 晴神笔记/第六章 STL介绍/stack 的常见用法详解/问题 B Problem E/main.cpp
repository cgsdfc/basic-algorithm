#include <iostream>
#include <stack>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

char Match(char x) {
  switch (x) {
  case '}':
    return '{';
  case ']':
    return '[';
  case ')':
    return '(';
  default:
    return 0;
  }
}

bool Judge(string &str) {
  stack<char> s;
  for (int i = 0; i < str.size(); ++i) {
    char x = str[i];
    switch (x) {
    case '{':
    case '[':
    case '(':
      s.push(x);
      break;
    case '}':
    case ']':
    case ')':
      if (!s.empty() && s.top() == Match(x)) {
        s.pop();
      } else {
        return false;
      }
      break;
    }
  }
  return s.empty();
}

/*
注意点：
1. 对栈进行top，pop之前必须判定empty。
2. 读取整数后要getline，必须先getchar。
*/

int main(int argc, char **argv) {
  int N;
  while (scanf("%d", &N) != EOF) {
    getchar();
    while (N--) {
      string str;
      getline(cin, str);
      bool ans = Judge(str);
      printf("%s\n", ans ? "yes" : "no");
    }
  }
  return 0;
}
