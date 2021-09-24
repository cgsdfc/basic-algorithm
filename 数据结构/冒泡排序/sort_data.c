/*
�����������ݡ�
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// �����������ݣ���󲻳��� maxsize�� ���������С��
int ReadArray(FILE *f, int a[], int maxsize) {
  int n;
  int i;

  scanf("%d", &n);
  assert(n <= maxsize);
  for (i = 0; i < n; ++i) {
    fscanf(f, "%d", &a[i]);
  }
  return n;
}

// ���ļ��������顣
int ReadArrayFile(const char *file, int a[], int maxsize) {
  FILE *f;
  int n;

  f = fopen(file, "r");
  assert(f);
  n = ReadArray(f, a, maxsize);
  fclose(f);
  return n;
}

//����������ݣ����ض���ʽ��
void WriteArray(FILE *f, int a[], int n) {
  int i;

  printf("%d\n", n);
  for (i = 0; i < n; ++i) {
    fprintf(f, "%d ", a[i]);
  }
  // ע�⣺fputs������ӻ��У���puts�ᣡ��
  fprintf(f, "\n");
}

// ������鵽�ļ���
void WriteArrayFile(const char *file, int a[], int n) {
  FILE *f;

  f = fopen(file, "w");
  assert(f);
  WriteArray(f, a, n);
  fclose(f);
}

// ��������������ݡ�
void RandArray(int a[], int n) {
  int i;

  assert(n > 0);
  for (i = 0; i < n; ++i) {
    a[i] = rand() % n;
  }
}

int ArrayEqual(int a[], int b[], int n) {
  return 0 == memcmp(a, b, sizeof(int) * n);
}

static int Cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

void SortArray(int a[], int n) { qsort(a, n, sizeof(n), Cmp); }
