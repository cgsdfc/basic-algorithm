#include <math.h>  // round
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void Init(void) {
    srand((unsigned int) time(NULL));
}

/*
����һ������[left, right]�ϵ��������
Ҫ�壺
1. rand() ���� RAND_MAX ���õ�0-1�����������
2. ���� right-left �������䳤�ȣ��õ� [0, right-left] �����������
3. ����left���õ� [left, right] �����������
4 round()һ�£��õ� [left, right] ���������
*/
static int Rand(int left, int right) {
    return round(rand() / (double) RAND_MAX * (right - left) + left);
}

// �������������Ԫ�ء�
static void Swap(int A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

static int RandPartition(int A[], int left, int right) {
    int p;  // �����Ԫ�±ꡣ
    int temp;

    // ����
    p = Rand(left, right);
    Swap(A, left, p);

    // һ��ͬ��ͨPartition��
    temp = A[left];
    while (left < right) {
        while (left < right && A[right] > temp)
            --right;
        A[left] = A[right];
        while (left < right && A[left] <= temp)
            ++left;
        A[right] = A[left];
    }
    A[left] = temp;
    return left;
}

static void QuickSort(int A[], int left, int right) {
    if (left < right) {
        int mid = RandPartition(A, left, right);
        QuickSort(A, left, mid - 1);
        QuickSort(A, mid + 1, right);
    }
}
