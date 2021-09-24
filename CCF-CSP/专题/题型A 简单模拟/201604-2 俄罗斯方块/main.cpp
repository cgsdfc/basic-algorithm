#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����һ�������ʾͼ�ε�ÿһ�����صĵ�ǰ�У�
ÿ�μ��1���ص���һ���Ƿ��ڱ�������1���أ���������ֹ��
*/

const int Row = 15, Col = 10;
const int N = 4;

int bg[20][20];
int a[10][10];

int row, col; // a�����Ͻǵ����ꡣ
int low;

void Solve() {
  /*
  ע�⣬ֻҪ�����������һ���������ײ����Ϳ��Լ������䡣
  */
  while (low < Row) {
    bool ok = true;
    for (int i = row; i < row + N; ++i) {
      for (int j = col; j < col + N; ++j) {
        if (!a[i - row + 1][j - col + 1])
          continue;
        if (i < Row && bg[i + 1][j]) {
          ok = false;
          break; // �����±�Ե��
        }
      }
    }
    if (ok) {
      ++row;
      ++low;
    } else {
      break;
    }
  }
  //	printf("row %d col %d low %d \n",row,col, low);

  // ��aֱ��д��bg��Ȼ�������
  for (int i = row; i < row + N; ++i) {
    for (int j = col; j < col + N; ++j) {
      int x = a[i - row + 1][j - col + 1];
      if (x) {
        // 1ֵ����low���ϣ���low��Row���ϣ��������ﲻ��Խ�硣
        bg[i][j] = x;
      }
    }
  }
  for (int i = 1; i <= Row; ++i) {
    for (int j = 1; j <= Col; ++j) {
      printf("%d%s", bg[i][j], j == Col ? "\n" : " ");
    }
  }
}

int FindLow() {
  for (int i = N; i >= 1; i--) {
    for (int j = 1; j <= N; ++j) {
      if (a[i][j])
        return i;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  for (int i = 1; i <= Row; ++i) {
    for (int j = 1; j <= Col; ++j) {
      scanf("%d", &bg[i][j]);
    }
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  // ��ʼλ�á�
  row = 1;
  scanf("%d", &col);
  low = FindLow();

  Solve();

  return 0;
}
