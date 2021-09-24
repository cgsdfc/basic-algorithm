#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
printf��%.mf�ǽض�ʽ�ģ������������롣
Ҫʵ���������룬�����ֹ�������C++������
*/

/*
��C++��ʵ���������뱣��NλС������Ϊcout�������Ƚ����״������װ�ɺ�����
��stdout���һ��������x���������뱣��nλС����

��n=1ʱ�������������룬��֪��Ϊʲô��
*/
void PrintFloat(double x, int n) {
  cout.flags(ios::fixed);
  cout.precision(n);
  cout << x;
}

/*
����cmathʵ�֡�
Roundʵ���������뱣��nλ���������Ҫ�Լ���printf��
*/
double Round(double x, int n) {
  double p = pow(10, n);
  x = round(x * p) / p;
  return x;
}

int main(int argc, char **argv) {
  double x;
  int n;

  while (cin >> x >> n) {
    PrintFloat(x, n);
    puts("");
  }
  return 0;
}
