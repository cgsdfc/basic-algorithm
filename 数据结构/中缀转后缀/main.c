#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100

typedef struct Stack {
  char data[MAXN];
  int top;
} Stack;

void Init(Stack *s) { s->top = -1; }

int IsEmpty(Stack *s) { return s->top == -1; }

void Push(Stack *s, char item) {
  assert(s->top != MAXN - 1);
  s->data[++s->top] = item;
}

char Pop(Stack *s) {
  assert(!IsEmpty(s));
  return s->data[s->top--];
}

char Top(Stack *s) { return s->data[s->top]; }

void Print(Stack *s) {
  int i;
  for (i = 0; i <= s->top; ++i) {
    printf("%c ", s->data[i]);
  }
  puts("");
}

int IsNbr(char c) { return isdigit(c); }

// ���ȼ��ɵ͵��ߡ�
int Order(char op) {
  switch (op) {
  case '+':
  case '-':
    return 0;
  case '*':
  case '/':
    return 1;
  case '(':
    // ջ�������ŵ����ȼ���ͣ�ջ�������ŵ����ȼ���ߡ�
    return -1;
  default:
    return 999;
  }
}

int IsHigher(char a, char b) {
  if (a == b)
    return 0;
  return Order(a) > Order(b);
}

int IsOp(char op) { return Order(op) != 999; }

void InfixToPostfix(char in[], int n, char out[]) {
  int i, j = 0;
  char cur;
  char top;
  Stack s;

  Init(&s);
  for (i = 0; i < n; ++i) {
    cur = in[i];
    //		Print(&s);
    if (IsNbr(cur)) {
      // �������������ֱ�������
      out[j++] = cur;
    } else if (cur == '(') {
      // ������ֱ����ջ��
      Push(&s, cur);
    } else if (cur == ')') {
      // �����ţ� һֱ��ջֱ�����������š�
      while ((top = Pop(&s)) != '(') {
        // ��top��������ʱ���˳�ѭ����������������
        out[j++] = top;
      }
    } else if (IsOp(cur)) {
      // һ����һ��������ˡ����cur�����ȼ�С�ڵ���ջ�����ȼ�����һֱpop��
      // ֱ��ջ�����ȼ�����cur�����ȼ�������Push cur��

      // ע�⵱��һ������������ʱ��ջΪ�գ�������ջ��Ԫ�ء�
      if (IsEmpty(&s) || IsHigher(cur, Top(&s))) {
        Push(&s, cur);
      } else {
        // ջ���գ�����ջ�������ȼ�����cur�ġ�
        while (!IsEmpty(&s) && !IsHigher(cur, top = Top(&s))) {
          out[j++] = top;
          Pop(&s);
        }
        Push(&s, cur);
      }
    }
    // ��������������ո�������
  }

  while (!IsEmpty(&s)) {
    out[j++] = Pop(&s);
  }
  // ���������ַ�����������
  out[j++] = '\0';
}

int main(int argc, char *argv[]) {
  char in[MAXN], out[MAXN];
  int i;
  memset(out, 0, sizeof(out));

  freopen("./in.txt", "r", stdin);
  freopen("./out.txt", "w", stdout);

  gets(in);
  //	puts(in);

  InfixToPostfix(in, strlen(in), out);
  for (i = 0; i < strlen(out); ++i) {
    printf("%c ", out[i]);
  }
  return 0;
}
