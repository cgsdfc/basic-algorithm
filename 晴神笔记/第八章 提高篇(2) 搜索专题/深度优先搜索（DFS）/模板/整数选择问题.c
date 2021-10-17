#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
����N������������ѡ��K������ʹ����K����֮��ǡ�õ���һ������������ X��
����ж��ַ�����ѡ��������Ԫ��ƽ��������һ����

����ı�����ö��һ����N��Ԫ�ص�ȫ����KԪ�Ӽ���
�����������Ӽ��Ĵ�С�����Բ�����ö�������Ӽ������Ӷ���C(N,K)��
����N��Ԫ��ѡ��K�����ķ����������������

DFS�ķ�������ö���Ӽ��Ļ��������Ӷ���ö��Ԫ�ظ��������ơ�
*/

int N;            // ȫ���Ĵ�С��
int K;            // ��ö�ٵ��Ӽ��Ĵ�С��K<=N
int X;            // ���ƣ��Ӽ�Ԫ�صĺ͵���X��
int MaxSum = -1;  // ���ƽ���͡�

#define MAXN 100
// ȫ����Ԫ�ء�
int A[MAXN];

// �������ŷ������Ӽ���
struct {
    int data[MAXN];
    int len;
} ans, temp;

/*
���Ӽ�ö������ͬ�Ŀ�ܣ����ǰ�ö�ٵ��Ӽ���С������K��
����ֻ����K���Ӽ���

index����ǰҪ���ǵ�Ԫ���±ꡣ
nowK����ǰ�������Ӽ���С����Ӧ temp.len����
nowX����ǰ�Ӽ���Ԫ�غ͡�
nowS����ǰ�Ӽ�Ԫ�ص�ƽ���͡�
*/
static void DFS(int index, int nowK, int nowX, int nowS) {
    int x;
    /*
    ���У���ǰ״̬�н⣬Ӧ�ø������ֵ��
    */
    if (nowK == K && nowX == X) {
        if (nowS > MaxSum) {
            MaxSum = nowS;
            ans = temp;
        }
        return;
    }
    /*
    ���У���ǰ״̬�޽⡣
    */
    if (index == N || nowK > K || nowX > X) { return; }
    /*
    ���ǵ�ǰ������Ȼ�������
    */
    x = A[index];
    temp.data[temp.len++] = x;
    DFS(index + 1, nowK + 1, nowX + x, nowS + x * x);
    --temp.len;

    // ��ѡ��ǰ����
    DFS(index + 1, nowK, nowX, nowS);
}

/*
����ı�ʽ

Ԫ�ؿ��ظ���K���Ӽ���
����ÿ��ȫ����Ԫ��X�����������Ӽ��г���0����Ρ�
ע���������Ӽ��������������޵ģ���Ϊ�������Ӽ��Ĵ�СΪK��
����������ƣ����������Ӽ����������޵ġ�

����ͱ����ö��Ԫ�ؿ��ظ���K���Ӽ���
����ڱ�ɣ�
1. ��ѡ��ǰԪ�أ�������һ��Ԫ�ء�
2. ѡ��ǰԪ�أ����Ҽ������ǵ�ǰԪ�ء�

����ͬ��Ȼ�ǣ�
1. ��K��Ԫ�ء�
2. N��Ԫ�ؿ����ꡣ
*/
static void DFS2(int index, int nowK, int nowX, int nowS) {
    int x;
    /*
    ���У���ǰ״̬�н⣬Ӧ�ø������ֵ��
    */
    if (nowK == K && nowX == X) {
        if (nowS > MaxSum) {
            MaxSum = nowS;
            ans = temp;
        }
        return;
    }
    /*
    ���У���ǰ״̬�޽⡣
    */
    if (index == N || nowK > K || nowX > X) { return; }
    /*
    ���ǵ�ǰ������Ȼ�������
    */
    x = A[index];
    temp.data[temp.len++] = x;
    /*
    Ԫ�ؿ��ظ����޸ģ�
    ȡindex�󣬼�������index��ֱ������߽磬�ͻ�ͨ������Ĵ���
    ��������Ԫ�ء��� index �������index+1 ��Ϊ index��
    */
    DFS2(index, nowK + 1, nowX + x, nowS + x * x);
    --temp.len;

    // ��ѡ��ǰ����
    DFS2(index + 1, nowK, nowX, nowS);
}
