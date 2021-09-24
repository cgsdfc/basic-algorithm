#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;
#define MAXN 105
int origin[MAXN]; // ԭʼδ�������С�
int temp[MAXN];   // origin�Ŀ�����
int now[MAXN];    // �����������������С�

/*
ֱ��ģ����������
*/
void DownAdjust(int A[], int low, int high) {
  int i = low;
  int j = i * 2;
  while (j <= high) {
    if (j + 1 <= high && A[j + 1] > A[j]) {
      // �Һ��Ӹ���
      j = j + 1;
    }
    if (A[j] > A[i]) {
      // ���ӱȸ��ڵ��
      swap(A[i], A[j]);
      i = j;
      j = 2 * i;
    } else {
      break; // ����������
    }
  }
}

void CreateHeap(int A[], int N) {
  for (int i = N / 2; i >= 1; --i) {
    // ���򣬷�Ҷ�ӽڵ㽨�ѡ�
    DownAdjust(A, i, N);
  }
}

void Print(int A[], int N) {
  for (int i = 1; i <= N; ++i) {
    printf("%d%s", A[i], i == N ? "\n" : " ");
  }
}

// ע���������±��1��N��
// Ϊ��һ���ԣ�ȫ���±궼��1��N��

void HeapSort(int A[], int N) {
  CreateHeap(A, N);
  bool flag = false;

  // �ѵĴ�С��N��С��1.
  for (int i = N; i > 1; i--) {
    swap(A[1], A[i]);
    DownAdjust(A, 1, i - 1); // ��ʣ�µ�Ԫ�ؽ���Down��
    if (flag) {
      puts("Heap Sort");
      Print(A, N);
      return;
    }
    if (!memcmp(A + 1, now + 1, sizeof(int) * N)) {
      flag = true; // �ҵ�Ŀ�����С�
    }
  }
}

/*
���ڶ�����ʹ��1--N�±꣬ע��memcpy��memcmp���������Ӧ������
*/

void InsertSort(int A[], int N) {
  bool flag = false;

  // ��2--N Ԫ�ز����������У���ʼΪ1�š�
  for (int i = 2; i <= N; ++i) {
    int temp = A[i]; // ȡ��������Ԫ�أ��ڳ��ռ䡣
    int j = i;
    // ��һ���������������Ԫ��temp���ؼ��ǴӺ���ǰ��
    // �ҵ�һ����һ��λ��j��ʹ��j-1��Ԫ��С�ڵ��� temp
    // ����j���ǵ�һ��λ�á�
    while (j > 1 && A[j - 1] > temp) {
      A[j] = A[j - 1];
      j--;
    }
    A[j] = temp; // �ҵ�����λ�á�
    if (flag) {
      puts("Insertion Sort");
      Print(A, N);
      return;
    }
    if (!memcmp(A + 1, now + 1, sizeof(int) * N)) {
      flag = true;
    }
  }
}

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &origin[i]); // ����ԭʼ���С�
  }
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &now[i]); // ���벿�����������С�
  }
  memcpy(temp + 1, origin + 1, sizeof(int) * N);
  HeapSort(temp, N);
  memcpy(temp + 1, origin + 1, sizeof(int) * N);
  InsertSort(temp, N);

  return 0;
}
