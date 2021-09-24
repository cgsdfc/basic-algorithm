#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��һ���ַ�����ɨ������������
��־������ѡ�ĵȺţ���ѡ�����֣�ʮ��������������Ϊ��������
*/
// ����ĳ���
#define MAXL (1000000 + 5)
// һ����ĳ���
#define MAXT (1000 + 5)

char line[MAXL], term[MAXT];

bool IsBegin(char c) { return c == '_' || isalpha(c); }
bool IsMid(char c) { return c == '_' || isalnum(c); }
bool IsNumBegin(char c) { return c == '-' || c == '+' || isdigit(c); }

void Solve(char str[], int len) {
  int i = 0;
  int tlen = 0;
  int value = 0;

  // ���������������档������ȥ����enum�����֡�
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
    // �ռ���־����
    tlen = 0;
    while (i < len && IsMid(str[i])) {
      term[tlen++] = str[i++];
    }
    term[tlen] = 0;
    printf("%s ", term);

    // ȷ��value��ֵ��
    while (i < len && isspace(str[i])) {
      ++i; // �Ⱥ�֮ǰ�����пո�
    }
    // ��־������϶��������ַ��������ܵ��������
    if (str[i] != '=') {
      now = value;
      ++value;
    } else {
      ++i;
      tlen = 0;
      // ���ܺ�������֡�
      while (i < len && isspace(str[i])) {
        ++i;
      }
      assert(IsNumBegin(str[i]));
      // ��֤���ֺϷ���
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
