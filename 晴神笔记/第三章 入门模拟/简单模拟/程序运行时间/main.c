#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

//���� a/b��������������롣
int RoundDiv(int a, int b) {
  if (a % b * 2 >= b) {
    // �������ڰ��b ��
    return a / b + 1;
  }
  return a / b;
}

int main(int argc, char *argv[]) {
  int c1, c2;
  int dur;

  scanf("%d%d", &c1, &c2);
  dur = c2 - c1;

  // �ֶ���dur�������롣
  if (dur % 100 >= 50) {
    // �ڰ�dur��tickΪ��λת��ΪsΪ��λʱ��
    //		���Ա��⸡�����㣬�����ڽ��г���֮ǰ�ж������Ƿ���ڵ��ڳ�����һ�롣
    //��Ҳ�����������һ��ԭ�� ����ʵ����ʵ���˶� dur/100
    //������������Ĳ������� round(dur/100.0)��
    dur = dur / 100 + 1;
  } else {
    dur = dur / 100;
  }

  printf("%02d:%02d:%02d\n", dur / 3600, (dur % 3600) / 60, dur % 60);

  return 0;
}
