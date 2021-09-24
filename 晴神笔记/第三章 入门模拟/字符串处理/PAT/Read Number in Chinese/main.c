#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 15

const char Dig[][5] = {"ling", "yi",  "er", "san", "si",
                       "wu",   "liu", "qi", "ba",  "jiu"};

// ��ͬ��ʹ�õĺ�׺��
const char Suffix[][5] = {"", "Wan", "Yi"};

// һ����ʹ�õĺ�׺ ��
const char Pow[][5] = {"", "Shi", "Bai", "Qian"};

/*
�ӵ�λ����λ�ָ����λһ�飬ÿ�����һ��ʮ�������֣��������ڵ�����0��
��ϲ���һ��0.
ÿ���Ȱ��������λ�Ľз��ó�һ������Ȼ����ÿ���λ�ü���һ����׺��
�����һ��û�к�׺���ڶ���ĺ�׺���򣬵�����ĺ�׺���ڡ�
���һ������0����ּ��������
����Ӹߵ��ͣ�0����û���������ˣ������������һ�ڣ�������һ���㡣
������滹������������ling����Ϊ�ָ�����

ע�⣬����0�������У���Ȼ���0��������ġ�
*/

/*
Sample Input 1:
-123456789
Sample Output 1:
Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu
Sample Input 2:
100800
Sample Output 2:
yi Shi Wan ling ba Bai
*/

// ��Ϊ�ո������Ƚ����жϣ����ԾͰ������ַ����ȴ�������Ȼ��Ϳ��Դ�������ո��ˡ�
const char *Res[MAXN];
int N;

void Add(const char val[]) { Res[N++] = val; }

// ��ӡһ�����ַ����顣
void PrintTerm(char str[], int n) {
  int i;

  for (i = 0; i < n; ++i) {
    int val = str[i] - '0';
    int power = n - i - 1;

    if (val) {
      Add(Dig[val]);
      if (power) {
        // ��λû������
        Add(Pow[power]);
      }
    } else {
      if (i != n - 1 && str[i + 1] != '0') {
        Add(Dig[0]);
      }
    }
  }
}

// ��Ϊ��Ҫ�ж���һ������ɵ�4λ���Ƿ�Ϊ0��������Ҫ����ĳ�������ֵ��
// str����������ǴӸߵ��͵ġ�
int Atoi(char str[], int n) {
  int p = 1;
  int sum = 0;
  // �������str��
  while (n--) {
    sum += p * (str[n] - '0');
    p *= p;
  }
  return sum;
}

// �ж��Ƿ�Ϊ0
int NonZero(char str[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (str[i] != '0')
      return 1;
  }
  return 0;
}

void Print(char str[], int n) {
  int r;
  int q;
  int i;
  int ngrp;

  if (str[0] == '0' && n == 1) {
    Add(Dig[0]);
    return;
  }
  if (str[0] == '-') {
    --n;
    ++str;
    Add("Fu");
  }

  q = n / 4;
  r = n % 4;
  ngrp = q + (r ? 1 : 0);

  for (i = 0; i < ngrp; ++i) {
    int len = (i == 0 && r) ? r : 4;
    if (NonZero(str, len)) {
      int power = ngrp - i - 1;
      PrintTerm(str, len);
      if (power) {
        Add(Suffix[power]);
      }
    } else if (i != ngrp - 1) {
      /*
      ������0������ֻ���ں���Ԫ�ط���ʱ�������
      Ҳ����˵������������֮���������㱻ѹ����һ����
      ��û�з��������ŵ��㣬ֱ�Ӳ������
      */
      if (NonZero(str + len, 4)) { // ���׸���ĳ��ȱض�Ϊ4.
        Add(Dig[0]);
      }
    }
    str += len;
  }
}

int main(int argc, char *argv[]) {
  char str[10];
  int n;
  int i;

  scanf("%s", str);
  n = strlen(str);
  Print(str, n);
  for (i = 0; i < N; ++i) {
    printf("%s%s", Res[i], i == N - 1 ? "\n" : " ");
  }
  return 0;
}
