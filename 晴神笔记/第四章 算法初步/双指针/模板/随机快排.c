#include <math.h>  // round
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void Init(void) {
    srand((unsigned int) time(NULL));
}

/*
生成一个区间[left, right]上的随机数。
要义：
1. rand() 除以 RAND_MAX ，得到0-1随机浮点数。
2. 乘以 right-left ，即区间长度，得到 [0, right-left] 随机浮点数。
3. 加上left，得到 [left, right] 随机浮点数。
4 round()一下，得到 [left, right] 随机整数。
*/
static int Rand(int left, int right) {
    return round(rand() / (double) RAND_MAX * (right - left) + left);
}

// 交换数组的两个元素。
static void Swap(int A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

static int RandPartition(int A[], int left, int right) {
    int p;  // 随机主元下标。
    int temp;

    // 交换
    p = Rand(left, right);
    Swap(A, left, p);

    // 一切同普通Partition。
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
