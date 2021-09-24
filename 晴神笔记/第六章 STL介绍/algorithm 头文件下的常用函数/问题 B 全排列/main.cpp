#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ע�⣺
1. permutation ��ƴд��������������뷨��

2. �̶�ģ�壺
        1. str �Ѿ��ǵ�һ�����У����ֵ����С������������С�
        2. �� do-while��ѭ���������� next_permutation��
        3. ��do-while�����str����Ч���ǰ��ֵ����С�������strԪ�ص�ȫ�����С�

3. ��������ķ���ֵ��
        1.
����true������������д�����һ�����У�������������б�ԭ���޸�Ϊ��һ�����С�
        2.
����false������������������һ�����У������������һ�����У������������б�
        ԭ���޸�Ϊ��һ�����У����ص�ԭ�㡣
*/

int main(int argc, char **argv) {
  string str;
  while (cin >> str) {
    do {
      printf("%s\n", str.c_str());
    } while (next_permutation(str.begin(), str.end()));
    printf("\n");
  }
  return 0;
}
