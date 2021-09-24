/*
�鲢������ȷʵ��

1. Merge����
2. ������������
        1. �ݹ�ʵ��
        2. �ǵݹ�ʵ�֡�

ע��
1. ����Ҫ���������ÿһ��ʱ���硶Intert or Merge������
��Ҫ�÷ǵݹ�Ĺ鲢����ֻ�ǱȽ��Ѽ��䡣
2. �����Ӷ�����ʱ��������sort�⺯������Merge����Ϊ�������������У������ģ�
�鲢����Ч�����ǰ�������������
*/

// �����������󳤶ȣ�����������ʱ���顣
#define MAXN 100

// Merge��Ҫ�������������䣬��[L1,R1]��[L2,R2]����R1=L2-1��
static void Merge(int A[], int L1, int R1, int L2, int R2) {
  int temp[MAXN];
  int i, j, k; // �����±�ֱ�ָʾ�����䣬�����䣬��ʱ���顣

  i = L1, j = L2, k = 0;
  while (i <= R1 && j <= R2) {
    if (A[i] < A[j]) {
      temp[k++] = A[i++];
    } else {
      temp[k++] = A[j++];
    }
  }
  while (i <= R1)
    temp[k++] = A[i++];
  while (j <= R2)
    temp[k++] = A[j++];
  // ���Ҫ��temp�����ݿ�����ȥ��
  for (i = 0; i < k; ++i) {
    A[L1 + i] = temp[i];
  }
}

// ��qsort����Merge��
int CMP(const void *_a, const void *_b) { return 0; }

/*
�ݹ�ʵ�֡���ΪҪ�ݹ飬���Բ�����left��right��
*/
static void MergeSort(int A[], int left, int right) {
  /*
  L=R����ʾֻ��1��Ԫ�أ�L<R��������������Ԫ�ء�
  */
  if (left < right) {
    int mid = (left + right) / 2;
    // ע���QuickSort��ͬ���ǣ�midҪ����ȥ��
    MergeSort(A, left, mid);
    MergeSort(A, mid + 1, right);
    if (1)
      Merge(A, left, mid, mid + 1, right);
    else // ����Ҫʵ��Merge��������������ʱ��
      qsort(A + left, right - left + 1, sizeof(A[0]), CMP);
  }
}

/*
����ʵ�֡���Ϊ���õݹ飬����ֻ����A�Ĵ�С���ɡ�
�±��0��ʼ��
*/
int Min(int a, int b) { return a < b ? a : b; }

static void MergeSort2(int A[], int n) {
  int step;
  // ÿ���Ĳ���Ϊ2���ݴΡ�
  for (step = 2; step / 2 < n; step *= 2) {
    int i;
    for (i = 0; i < n; i += step) {
      int mid = i + step / 2 - 1;
      if (mid + 1 < n) { // ������������Ԫ�ء�
                         // ��Ϊmid+1��������ĵ�һ��Ԫ�ء�
                         // ���mid+1<n����������������һ��Ԫ�ء�
        Merge(A, i, mid, mid + 1, Min(n - 1, i + step - 1))
      }
    }
  }
}
