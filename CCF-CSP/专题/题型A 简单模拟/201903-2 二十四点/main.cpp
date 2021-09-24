#include <cstdio>
#include <stack>
using namespace std;

int N;

const int Len = 7;

int Ord(char c) {
  switch (c) {
  case '-':
  case '+':
    return 1;
  case 'x':
  case '/':
    return 2;
  default:
    return 0;
  }
}

int Compute2(stack<int> &data, char op) {
  int b = data.top();
  data.pop();
  int a = data.top();
  data.pop();
  switch (op) {
  case '+':
    a += b;
    break;
  case '-':
    a -= b;
    break;
  case 'x':
    a *= b;
    break;
  case '/':
    a /= b;
    break;
  }
  data.push(a);
}

/*
���㲻�����ţ������ַ�����׺���ʽ��
1. ��Ҫ����ջ�����룩��
2. �漰switch��䣬ע��break��Ҫ©�ˡ�
*/
int Compute(char str[], int len) {
  stack<char> s;
  stack<int> data;

  for (int i = 0; i < len; ++i) {
    char c = str[i];
    if (!Ord(c)) {
      // ��������
      data.push(c - '0');
    } else {
      while (!s.empty() && Ord(s.top()) >= Ord(c)) {
        char op = s.top();
        s.pop();
        Compute2(data, op);
      }
      s.push(c);
    }
  }
  while (!s.empty()) {
    char op = s.top();
    s.pop();
    Compute2(data, op);
  }
  return data.top();
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  scanf("%d", &N);
  while (N--) {
    char str[10];
    scanf("%s", str);
    int ans = Compute(str, Len);
    puts(ans == 24 ? "Yes" : "No");
  }
  return 0;
}
