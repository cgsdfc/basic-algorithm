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

// 优先级由低到高。
int Order(char op) {
  switch (op) {
  case '+':
  case '-':
    return 0;
  case '*':
  case '/':
    return 1;
  case '(':
    // 栈内左括号的优先级最低，栈外左括号的优先级最高。
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
      // 如果是运算数，直接输出。
      out[j++] = cur;
    } else if (cur == '(') {
      // 左括号直接入栈。
      Push(&s, cur);
    } else if (cur == ')') {
      // 右括号， 一直出栈直到遇到左括号。
      while ((top = Pop(&s)) != '(') {
        // 当top是左括号时，退出循环，左括号抛弃。
        out[j++] = top;
      }
    } else if (IsOp(cur)) {
      // 一定是一个运算符了。如果cur的优先级小于等于栈顶优先级，则一直pop，
      // 直到栈顶优先级大于cur的优先级。否则Push cur。

      // 注意当第一个操作符出现时，栈为空，不存在栈顶元素。
      if (IsEmpty(&s) || IsHigher(cur, Top(&s))) {
        Push(&s, cur);
      } else {
        // 栈不空，而且栈内有优先级大于cur的。
        while (!IsEmpty(&s) && !IsHigher(cur, top = Top(&s))) {
          out[j++] = top;
          Pop(&s);
        }
        Push(&s, cur);
      }
    }
    // 其他东西，比如空格，跳过。
  }

  while (!IsEmpty(&s)) {
    out[j++] = Pop(&s);
  }
  // 最后别忘了字符串结束符。
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
