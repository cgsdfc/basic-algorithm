#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��ѧ�������ǿ�ѧ��������ʾ�ܴ���С�����ֵ�һ�ַ���ķ�����������������ʽ
[+-][1-9].[0-9]+E[+-][0-9]+�� �����ֵ���������ֻ�� 1 λ��С������������ 1
λ�������ּ���ָ�����ֵ������ż�ʹ������Ҳ�ض���ȷ������

���Կ�ѧ�������ĸ�ʽ����ʵ�� A�����д������ͨ���ֱ�ʾ�����
A������֤������Чλ����������

�����ʽ��
ÿ��������� 1 ��������������һ���Կ�ѧ��������ʾ��ʵ��
A�������ֵĴ洢���Ȳ����� 9999 �ֽڣ� ����ָ���ľ���ֵ������ 9999��

�����ʽ��
��ÿ��������������һ���а���ͨ���ֱ�ʾ�����
A������֤������Чλ��������������ĩβ�� 0��

�������� 1��
+1.23400E-03
������� 1��
0.00123400

�������� 2��
-1.2E+10
������� 2��
-12000000000

*/

#define MAXN 10000

typedef struct Num {
  char sign; // �������������ţ�ֻ�и���Ҫ�����
  char fra[MAXN];
  int len; // fra�ĳ��ȡ�
  int exp;
} Num;

void Print(Num n) { printf("%c %s %d\n", n.sign, n.fra, n.exp); }

Num Parse(char str[], int len) {
  int i;
  Num num;
  int n = 0;
  char exp[10];

  num.sign = str[0];
  num.fra[n++] = str[1];

  // i=2 �� .
  for (i = 3; str[i] != 'E'; ++i) {
    num.fra[n++] = str[i];
  }
  num.fra[n] = 0;
  num.len = n;
  n = 0;
  for (i++; i < len; ++i) {
    exp[n++] = str[i];
  }
  exp[n] = 0;
  // atoi ���Դ��������š�
  num.exp = atoi(exp);
  return num;
}

void Print2(Num n) {
  if (n.sign == '-')
    printf("%c", n.sign);
  if (n.exp < 0) {
    // ��С���������ʽΪ0.000xxxx��������0��Ȼ����fra��
    int i;
    printf("0.");
    // 1.2e-3 0.0012
    for (i = 0; i < -n.exp - 1; ++i) {
      putchar('0');
    }
    printf("%s", n.fra);
  } else {
    /*
    �������ַ���ļ�С����
    ������������֣�Ȼ����С���㣬Ȼ����ʣ���β����
    �����ּ��������
    1. β��λ���ܶ࣬��ض���С�����ʣ���β����
    2. ָ���ܴ��򲻻���С���㣬���ҿ�����0 ��
    ���������β���ĵ�һλ��Ȼ��һ�߼������β����һ�߼������˶���ָ����
    ��β���������ָ������ʱ���������ֽ���������������β���Ƿ������ָ���Ƿ����꣬
    ����С�����ʣ�µ�β�������߲���ָ����0 ��
    */
    int i;
    int j;
    putchar(n.fra[0]);
    /*
    β����Ϊ�������������һ�����β����һ�߲��ܳ���exp���ַ���
    */
    for (i = 1, j = 0; i < n.len && j < n.exp; ++i, ++j)
      putchar(n.fra[i]);
    if (i < n.len) {
      // β����û�ꡣ
      putchar('.');
      for (; i < n.len; ++i) {
        putchar(n.fra[i]);
      }
    } else {
      // ָ���ϴ���Ҫ���㡣
      for (; j < n.exp; ++j) {
        putchar('0');
      }
    }
  }
  putchar('\n');
}

int main(int argc, char *argv[]) {
  char str[MAXN];
  Num num;

  scanf("%s", str);
  num = Parse(str, strlen(str));
  Print2(num);

  return 0;
}
